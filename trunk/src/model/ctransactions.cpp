#include "ctransactions.h"
#include "ftransactionbuythingedit.h"
#include "ftransactionsellthingedit.h"
#include "titemtagsedit.h"
#include "ttagcontainer.h"
#include "ctransaction.h"
#include "icons.h"
#include "st.h"

namespace hacc
{
namespace model
{

CTransactions::CTransactions()
    : base::CBases(),
      hacc::model::CTagged(HACC_TAG_TABLE_NAME(transaction), HACC_TAG_TABLE_ID_NAME(transaction))
{}

CTransactions::~CTransactions()
{}


QAction * CTransactions::addSellAction(const hacc::TDBID &id, QObject *reciever, const char * method)
{
    return constructAction(base::atTransactionSell, id, reciever, method);
}

hacc::TDBID CTransactions::addOnlyTransactionBase(const hacc::TDBID & poolId, const hacc::TMoney &money)
{
    hacc::TDBID newID = nextID();
    HACC_DB->exec("insert into transactions (id, pool_id, money) values (?,?,?)",
                  QVariantList()
                  << newID
                  << poolId
                  << money);
    return newID;
}

void CTransactions::addThingBuyTransaction(const hacc::TDBID & poolId)
{
    ui::form::FTransactionBuyThingEdit *dialog = new ui::form::FTransactionBuyThingEdit();
    if(dialog->exec() == QDialog::Accepted)
    {
        hacc::TDBID newID = addOnlyTransactionBase(poolId, dialog->money());
        HACC_DB->exec("insert into transactions_things (id, thing_id, amount) values (?,?,?)",
                      QVariantList()
                      << newID
                      << dialog->thingID()
                      << dialog->amount());
        emit created(newID);
    }
    delete dialog;
}

void CTransactions::addThingSellTransaction(const hacc::TDBID & poolId)
{
    ui::form::FTransactionSellThingEdit *dialog = new ui::form::FTransactionSellThingEdit();
    if(dialog->exec() == QDialog::Accepted)
    {
        hacc::TDBID newID = addOnlyTransactionBase(poolId, dialog->money());
        HACC_DB->exec("insert into transactions_valuables (id, valuable_id) values (?,?)",
                      QVariantList()
                      << newID
                      << dialog->valuableID());
        emit created(newID);
    }
    delete dialog;
}

void CTransactions::removeThingTransaction(const hacc::TDBID & id)
{
    if(id > 0)
    {
        QSqlQuery q = HACC_DB->query("select money from transactions where id=?", QVariantList() << id);
        q.next();
        if(QMessageBox::question(
                HACC_WINDOW,
                tr("Transaction remove"),
                tr("You sure you want to delete transaction of %0 money?"
                   "This also remove copies of transaction thing out of the values")
                    .arg(HACC_DB_2_STRG(q, 0)),
                QMessageBox::Yes | QMessageBox::No)
            == QMessageBox::Yes)
        {
            removeTransaction(id);
        }
    }
}
/*! Редактирование транзакции покупки.
  Нужно обращать внимание не только на транзакцию, но и на ценности и их перемещения
  @param transactionID Транзакция покупки, которая обновилась
*/
void CTransactions::editThingBuyTransaction(const hacc::TDBID & transactionID)
{
    if(transactionID > 0)
    {
        ui::form::FTransactionBuyThingEdit *dialog = new ui::form::FTransactionBuyThingEdit(transactionID);
        if(dialog->exec() == QDialog::Accepted)
        {
            HACC_DB->exec("update transactions set money=? where id=?",
                          QVariantList()
                          << dialog->money()
                          << transactionID);
            hacc::TAmount oldAmount = HACC_DB->queryCell("select amount from transactions_things where id=?", 0, QVariantList() << transactionID).toInt();
            HACC_DB->exec("update transactions_things set thing_id=?, amount=? where id=?",
                          QVariantList()
                          << dialog->thingID()
                          << dialog->amount()
                          << transactionID);
            if(dialog->amount() != oldAmount)
            {
                // найти количество ценностей без дополнительных перемещений (допустимо одно, покупка) --- в диалоге, установить минимум
                if(dialog->amount() < oldAmount)
                {
                    hacc::TIDList valuablesList = HACC_VALUABLES->listVithoutMoving("valuables.transaction_id=?", QVariantList() << transactionID)
                                                  .mid(0, oldAmount - dialog->amount());

                     // удалить из ценностей все связанные ценности
                    HACC_VALUABLES->remove(valuablesList);
                    // удалить из перемещений все связанные перемещения
                    HACC_MOVEMENTS->removeValuableMovements(valuablesList);
                }
                else
                {
                    // создать недостающие ценности и переместить их к покупателю
                    QSqlQuery q = HACC_DB->query("select  "
                                          /* 0*/ "src_acc.contractor_id as src_contractor_id, "
                                          /* 1*/ "dst_acc.contractor_id as dst_contractor_id, "
                                          /* 2*/ "transaction_pool.date_time, "
                                          /* 3*/ "transactions_things.thing_id "
                                                 "from transactions "
                                                 "left join transactions_things on transactions_things.id=transactions.id "
                                                 "left join transaction_pool on transaction_pool.id=transactions.pool_id "
                                                 "left join accounts src_acc on src_acc.id=transaction_pool.source_account_id "
                                                 "left join accounts dst_acc on dst_acc.id=transaction_pool.destination_account_id "
                                                 "where transactions.id=?", QVariantList() << transactionID);
                    if(HACC_QUERY_DATA_AVIALABLE(q))
                    {
                        //! \todo Добавить действие, если запрос не вернет данных
                        transactionBuyValuablesAppend(dialog->amount() - oldAmount,
                                                      transactionID,
                                                      HACC_DB_2_DBID(q, 0),
                                                      HACC_DB_2_DBID(q, 1),
                                                      HACC_DB_2_DBID(q, 3),
                                                      HACC_DB_2_DATI(q, 2),
                                                      HACC_TAG_ID_BUYING);
                    }
                }
            }
            emit updated(transactionID);
        }
        delete dialog;
    }
}

/*! Отражает в основных средствах и в перемещениях основных средств указанное количество приобретенных вещей, списывая при необходимости
  @param amount Количество ценностей для добавления.
  @param transactionID Идентификатор транзакции
  @param sourceContractor Контрагент - покупатель
  @param destinationContractor Контрагент - продавец
  @param thingID Идентификатор вещи
  @param datetime Дата-время покупки.
  @param transactionType Тип транзакции (покупка)
*/
void CTransactions::transactionBuyValuablesAppend(const int &amount                  , const hacc::TDBID &transactionID,
                                                  const hacc::TDBID &sourceContractor, const hacc::TDBID &destinationContractor,
                                                  const hacc::TDBID &thingID         , const QDateTime   &datetime,
                                                  const int &transactionType)
{
    hacc::TDBID valuableID;
    for (int i=0; i<amount; i++)
    {
        valuableID = HACC_VALUABLES->addTransactionValuable(transactionID, sourceContractor);
        HACC_MOVEMENTS->moveThing(destinationContractor, sourceContractor, valuableID, datetime, transactionType);
        if(!HACC_THINGS->tagAttached(HACC_TAG_ID_OBJECT, thingID))
        {
            HACC_MOVEMENTS->writeOff(sourceContractor, valuableID, datetime);
        }
    }
}

/*! Подтверждение транзакций при подтверждении нового пула транзакций.
  Плюс к тому, инициирует передвижение вещи, добавление в ценности и наоборот - смотря какого типа транзакция
  @param poolID Идентификатор пула транзакций
  @param sourceContractor Контрагент - покупатель
  @param destinationContractor Контрагент - продавец
  @param datetime Дата-время покупки.
  @param transactionType Тип транзакции (покупка, продажа...)
*/
void CTransactions::commitThingsTransactions(const hacc::TDBID &poolID          , const int         &transactionType,
                                             const hacc::TDBID &sourceContractor, const hacc::TDBID &destinationContractor,
                                             const QDateTime   &datetime)
{
    HACC_DB->exec("update transactions set pool_id=? where pool_id=0", QVariantList() << poolID);
    hacc::TIDList transactions = HACC_DB->listID("transactions", "pool_id=?", QVariantList() << poolID);

    foreach(hacc::TDBID id, transactions)
    {
        attachTag(transactionType, id);
        switch(transactionType)
        {
            case HACC_TAG_ID_BUYING:
            {
                QSqlQuery q = HACC_DB->query("select "
                                      /* 0*/ "transactions_things.amount, "
                                      /* 1*/ "things.enumerated_type_id, "
                                      /* 2*/ "transactions_things.thing_id "
                                             "from transactions_things "
                                             "left join things on things.id=transactions_things.thing_id "
                                             "where transactions_things.id=?", QVariantList() << id);
                if(HACC_QUERY_DATA_AVIALABLE(q))
                {
                    //! \todo Добавить действие, если запрос не вернет данных
                    int amount = HACC_ENUMERATED_THING_TYPES->checkDivisibleEnumeratedType(HACC_DB_2_DBID(q, 1))
                            ? HACC_DB_2_AMNT(q, 0)
                            : 1;
                    transactionBuyValuablesAppend(amount, id, sourceContractor, destinationContractor, HACC_DB_2_DBID(q, 2), datetime, transactionType);
                }
            }
            break;
            case HACC_TAG_ID_SELLING:
            {
                QSqlQuery q = HACC_DB->query("select "
                                          "transactions_valuables.valuable_id "
                                          "from transactions_valuables "
                                          "left join valuables on valuables.id=transactions_valuables.valuable_id "
                                          "where transactions_valuables.id=?", QVariantList() << id);
                if(HACC_QUERY_DATA_AVIALABLE(q))
                {
                    //! \todo Добавить действие, если запрос не вернет данных
                    hacc::TDBID valID = HACC_DB_2_DBID(q, 0);
                    HACC_VALUABLES->changeValuableOwner(valID, sourceContractor);
                    HACC_MOVEMENTS->moveThing(destinationContractor, sourceContractor, valID, datetime, transactionType);
                }
            }
            break;
        }
    }

}
/*! Вычисляет коммиссию и возвращает структуру
  @see hacc::SMoneyCommission
  @param money Деньги
  @param commission Значение коммисии
  @param commisionInPercents Значение коммиссии указано в процентах
  @param commissionInMoney Коммиссия уже включена в сумму
  @param hasCommission Коммиссия вообще есть (значение больше 0 и стоит соотв. галочка)
*/
hacc::SMoneyCommission CTransactions::calculateCommissionValue(const hacc::TMoney &money, const hacc::TMoney &commission,
                                                               const bool &commisionInPercents, const bool &commissionInMoney,
                                                               const bool &hasCommission)
{
    hacc::SMoneyCommission result;
    if(hasCommission)
    {
        if(commissionInMoney)
        {
            if(commisionInPercents)
            {
                hacc::TMoney one = (money/(100+commission));
                result.commission = one*commission;
                result.money = one*100;
            }
            else
            {
                result.commission = commission;
                result.money = money - commission;
            }
        }
        else
        {
            result.money = money;
            if(commisionInPercents) { result.commission = money/100*commission; }
            else { result.commission = commission; }
        }
    }
    else
    {
        result.money = money;
        result.commission = 0;
    }
    return result;
}

void CTransactions::addOnlyCommission(const hacc::TDBID & commisionPoolID, const hacc::TDBID & basePoolID,
                                      const hacc::TDBID &commissionTo, const bool &commisionInPercents,
                                      const bool &commissionInMoney, const hacc::TMoney &commission,
                                      const hacc::TMoney &realCommission)
{
    hacc::TDBID newID = addOnlyTransactionBase(commisionPoolID, realCommission);
    HACC_DB->exec("insert into transactions_commisions "
                  "("
                    "id,"
                    "base_pool_id,"
                    "commission_to_id,"
                    "commission_value_is_percent,"
                    "commission_already_in_money,"
                    "commission_value"
                  ") values (?,?,?,?,?,?)",
                  QVariantList()
                  << newID
                  << basePoolID
                  << commissionTo
                  << commisionInPercents
                  << commissionInMoney
                  << commission);
    attachTag(HACC_TAG_ID_COMMISSION, newID);
    emit created(newID);
}

void CTransactions::addTransferTransaction(const int &transactionType    ,
                                           const hacc::TDBID & basePoolID, const hacc::TDBID & commisionPoolID,
                                           const hacc::TMoney &money     , const bool &hasCommission,
                                           const bool &commissionInMoney , const bool &commisionInPercents,
                                           const hacc::TMoney &commission, const hacc::TDBID &commissionTo)
{
    hacc::SMoneyCommission moneyCommision = calculateCommissionValue(money, commission, commisionInPercents, commissionInMoney, hasCommission);
    hacc::TDBID newID = addOnlyTransactionBase(basePoolID, moneyCommision.money);
    attachTag(transactionType, newID);
    emit created(newID);

    if(hasCommission)
    {
        addOnlyCommission(commisionPoolID, basePoolID, commissionTo, commisionInPercents, commissionInMoney, commission, moneyCommision.commission);
    }

}

void CTransactions::editTransferTransaction(const hacc::TDBID & baseTransactionID, const hacc::TDBID & commisionTransactionID,
                                            const hacc::TDBID & basePoolID       , const hacc::TDBID & commisionPoolID,
                                            const hacc::TMoney &money            , const bool &hasCommission,
                                            const bool &commissionInMoney        , const bool &commisionInPercents,
                                            const hacc::TMoney &commission       , const hacc::TDBID &commissionTo)
{
    hacc::SMoneyCommission moneyCommision = calculateCommissionValue(money, commission, commisionInPercents, commissionInMoney, hasCommission);
    HACC_DB->exec("update transactions set money=? where id=?", QVariantList() << moneyCommision.money << baseTransactionID);
    if(hasCommission)
    {
        if(commisionTransactionID)
        {
            HACC_DB->exec("update transactions set money=? where id=?", QVariantList() << moneyCommision.commission << commisionTransactionID);
            HACC_DB->exec("update transactions_commisions "
                          "set "
                            "base_pool_id=?,"
                            "commission_to_id=?,"
                            "commission_value_is_percent=?,"
                            "commission_already_in_money=?,"
                            "commission_value=? "
                          "where id=?",
                          QVariantList()
                          << basePoolID
                          << commissionTo
                          << commisionInPercents
                          << commissionInMoney
                          << commission
                          << commisionTransactionID);
            emit updated(commisionTransactionID);
        }
        else
        {
            addOnlyCommission(commisionPoolID, basePoolID, commissionTo, commisionInPercents, commissionInMoney, commission, moneyCommision.commission);
        }
    }
    else
    {
        if(commisionTransactionID)
        {
            HACC_DB->exec("delete from transactions where id=?"           , QVariantList() << commisionTransactionID);
            HACC_DB->exec("delete from transactions_commisions where id=?", QVariantList() << commisionTransactionID);
            emit removed(commisionTransactionID);
        }
    }
    emit updated(baseTransactionID);
}

void CTransactions::removeTransaction(const hacc::TDBID & id)
{
    HACC_DB->exec("delete from transactions where id=?"           , QVariantList() << id);
    HACC_DB->exec("delete from transactions_things where id=?"    , QVariantList() << id);
    HACC_DB->exec("delete from transactions_commisions where id=?", QVariantList() << id);
    HACC_DB->exec("delete from transactions_valuables where id=?" , QVariantList() << id);
    HACC_VALUABLES->transactionRemoved(id);
    detachTags(id);
    emit removed(id);
}

void CTransactions::removeUncommitedTransactions()
{
    cleanAfterRemoveTransactionPool(0);
}


void CTransactions::cleanAfterRemoveTransactionPool(const hacc::TDBID & poolId)
{
    hacc::TIDList list = HACC_DB->listID("transactions", "pool_id=?", QVariantList() << poolId);
    foreach(hacc::TDBID id, list)
    {
        removeTransaction(id);
    }
}

void CTransactions::cleanAfterThingRemove(const hacc::TDBID & thingID)
{
    hacc::TIDList list = HACC_DB->listID("transactions_things", "thing_id=?", QVariantList() << thingID);
    HACC_DB->exec("update transactions_things set thing_id=1 where thing_id=?", QVariantList() << thingID);
    foreach(hacc::TDBID id, list)
    {
        emit updated(id);
    }
}

void CTransactions::tagsEdit(const hacc::TDBID & id)
{
         ui::form::TItemTagsEdit< ui::tag::TTagContainer < CTransaction, CTransactions > > *dialog =
     new ui::form::TItemTagsEdit< ui::tag::TTagContainer < CTransaction, CTransactions > >(id);
    if(dialog->exec() == QDialog::Accepted)
    {}
    delete dialog;
}

bool CTransactions::checkSpecialPurposeTag(const hacc::TDBID &tagID)
{
    switch(tagID)
    {
        case HACC_TAG_ID_BUYING    :
        case HACC_TAG_ID_SELLING   :
        case HACC_TAG_ID_TRANSFER  :
        case HACC_TAG_ID_COMMISSION:
        case HACC_TAG_ID_INCOMING  :
        case HACC_TAG_ID_OUTGOING  :
        case HACC_TAG_ID_TAX       :
            return true;
    }
    return false;
}

QString CTransactions::purposeTagsIDString()
{
    return QString("%0,%1,%2,%3,%4,%5,%6")
            .arg(HACC_TAG_ID_BUYING    )
            .arg(HACC_TAG_ID_SELLING   )
            .arg(HACC_TAG_ID_TRANSFER  )
            .arg(HACC_TAG_ID_COMMISSION)
            .arg(HACC_TAG_ID_INCOMING  )
            .arg(HACC_TAG_ID_OUTGOING  )
            .arg(HACC_TAG_ID_TAX       );
}

bool        CTransactions::hasPurposeTags() { return true; }
hacc::TDBID CTransactions::maxDBID       () { return HACC_DB->nextID("transactions"); }

QAction * CTransactions::generateAction(base::EActionsTypes atype, QObject *reciever, const char * method)
{
    switch(atype)
    {
        HACC_GENERATE_ACTION_CASE(base::atAdd            , tools::icons::iTransaction, tools::icons::oIncoming, tr("New buy transaction") , tr("Add new transaction"));
        HACC_GENERATE_ACTION_CASE(base::atTransactionSell, tools::icons::iTransaction, tools::icons::oOutgoing, tr("New sell transaction"), tr("Add new transaction"));
        HACC_GENERATE_ACTION_CASE(base::atEdit           , tools::icons::iTransaction, tools::icons::oEdit    , tr("Edit transaction")    , tr("Edit transaction"   ));
        HACC_GENERATE_ACTION_CASE(base::atRemove         , tools::icons::iTransaction, tools::icons::oRemove  , tr("Delete transaction")  , tr("Delete transaction" ));
        HACC_GENERATE_ACTION_CASE(base::atTagsEdit       , tools::icons::iTransaction, tools::icons::oTag     , tr("Edit tags")           , tr("Edit tags"          ));
        default: break;
    }
    return new QAction("Somewhere bug", 0);
}




}
}
