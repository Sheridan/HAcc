#include "ctransactionspools.h"
#include "ftransactionpoolthingedit.h"
#include "titemtagsedit.h"
#include "ttagcontainer.h"
#include "ctransactionpool.h"
#include "ftransactionmoneyedit.h"
#include "ftransactiongiftedit.h"
#include <QDateTime>
#include "icons.h"
#include "st.h"

namespace hacc
{
namespace model
{

CTransactionPools::CTransactionPools()
    : base::CBases(),
    hacc::model::CTagged(HACC_TAG_TABLE_NAME(transaction_pool), HACC_TAG_TABLE_ID_NAME(transaction_pool))
{
    connect(HACC_TRANSACTIONS, SIGNAL(updated(const hacc::TDBID &)), this, SLOT(transactionUpdate(const hacc::TDBID &)));
    connect(HACC_TRANSACTIONS, SIGNAL(removed(const hacc::TDBID &)), this, SLOT(transactionUpdate(const hacc::TDBID &)));
    connect(HACC_TRANSACTIONS, SIGNAL(created(const hacc::TDBID &)), this, SLOT(transactionUpdate(const hacc::TDBID &)));
}

CTransactionPools::~CTransactionPools()
{}

void CTransactionPools::add()
{}

void CTransactionPools::remove(const hacc::TDBID & id)
{
    if(id > 0)
    {
        QSqlQuery q = HACC_DB->query("select date_time from transaction_pool where id=?", QVariantList() << id);
        q.next();
        if(QMessageBox::question(
                HACC_WINDOW,
                tr("Transaction pool remove"),
                tr("You sure you want to delete '%1' transaction pool with transactions?")
                    .arg(HACC_DB_2_STRG(q, 0)),
                QMessageBox::Yes | QMessageBox::No)
            == QMessageBox::Yes)
        {
            HACC_DB->exec("delete from transaction_pool where id=?", QVariantList() << id);
            QSqlQuery q = HACC_DB->query("select "
                                         "transactions.pool_id "
                                         "from transactions "
                                         "left join transactions_commisions on transactions_commisions.id=transactions.id "
                                         "where transactions_commisions.base_pool_id = ?", QVariantList() << id);
            if(HACC_QUERY_DATA_AVIALABLE(q) && !q.value(0).isNull())
            {
                    //! \todo Добавить действие, если запрос не вернет данных
                HACC_DB->exec("delete from transaction_pool where id=?", QVariantList() << HACC_DB_2_DBID(q, 0));
            }

            HACC_TRANSACTIONS->cleanAfterRemoveTransactionPool(id);
            emit removed(id);
        }
    }
}

void CTransactionPools::edit(const hacc::TDBID & id)
{
    if(id > 0)
    {
        int rType = HACC_DB->queryCell("select "
                                       "transaction_pools_tags.tag_id "
                                       "from transaction_pool "
                                       "left join transaction_pools_tags on transaction_pools_tags.transaction_pool_id = transaction_pool.id "
                                       "where transaction_pool.id=? and " + whereTagsInPurposeTags(), 0,
                                       QVariantList() << id).toInt();
        switch(rType)
        {
            case HACC_TAG_ID_BUYING :
            case HACC_TAG_ID_SELLING:
            {
                ui::form::FTransactionPoolThingEdit *dialog = new ui::form::FTransactionPoolThingEdit(id, rType);
                if(dialog->exec() == QDialog::Accepted)
                {
                    HACC_DB->exec("update transaction_pool set date_time=?,source_account_id=?,destination_account_id=? where id=?",
                                  QVariantList()
                                  << dialog->datetime()
                                  << dialog->buyerAccountID()
                                  << dialog->sellerAccountID()
                                  << id);
                    emit updated(id);
                }
                delete dialog;
            }
            break;
            case HACC_TAG_ID_INCOMING :
            case HACC_TAG_ID_OUTGOING :
            case HACC_TAG_ID_TRANSFER :
            case HACC_TAG_ID_COMMISSION:
            {
                ui::form::FTransactionMoneyEdit *dialog = new ui::form::FTransactionMoneyEdit(id, rType);
                if(dialog->exec() == QDialog::Accepted)
                {
                    HACC_DB->exec("update transaction_pool set date_time=?,source_account_id=?,destination_account_id=? where id=?",
                                  QVariantList() << dialog->datetime() << dialog->sourceAccountID() << dialog->destinationAccountID() << dialog->basePoolID());
                    bool reallyHasCommission = dialog->commission() == 0 ? false : dialog->hasCommission();
                    hacc::TDBID commissionPoolID = dialog->commissionPoolID();
                    if(reallyHasCommission)
                    {
                        if(commissionPoolID)
                        {
                            HACC_DB->exec("update transaction_pool set date_time=?,source_account_id=?,destination_account_id=? where id=?",
                                          QVariantList() << dialog->datetime() << dialog->sourceAccountID() << dialog->commissionTo() << commissionPoolID);
                        }
                        else
                        {
                            commissionPoolID = execAddTransactionPool(HACC_TAG_ID_COMMISSION, dialog->datetime(), dialog->sourceAccountID(), dialog->commissionTo());
                        }
                    }
                    else
                    {
                        HACC_DB->exec("delete from transaction_pool where id=?", QVariantList() << commissionPoolID);
                    }
                    HACC_TRANSACTIONS->editTransferTransaction(dialog->baseTransactionID()       , dialog->commissionTransactionID(),
                                                               dialog->basePoolID()              , commissionPoolID,
                                                               dialog->money()                   , reallyHasCommission,
                                                               dialog->commissionAlreadyInMoney(), dialog->commissionInPercents(),
                                                               dialog->commission()              , dialog->commissionTo());
                    emit updated(dialog->basePoolID());
                    if(reallyHasCommission)
                    {
                        emit updated(commissionPoolID);
                    }
                }
                delete dialog;
            }
            break;
        }
    }
}

void CTransactionPools::transactionUpdate(const hacc::TDBID & transactionId)
{
    hacc::TDBID poolId = HACC_DB->queryCell("select pool_id from transactions where id-?",
                                            0,
                                            QVariantList() << transactionId).toUInt();
    if(poolId)
    {
        emit updated(poolId);
    }
}

hacc::TDBID CTransactionPools::execAddTransactionPool(const int &transactionPoolType, const QDateTime &datetime,
                                                       const hacc::TDBID &source     , const hacc::TDBID &destination)
{
    hacc::TDBID newID = nextID();
    HACC_DB->exec("insert into transaction_pool (id,date_time,source_account_id,destination_account_id) values (?,?,?,?)",
                  QVariantList() << newID << datetime << source << destination);
    attachTag(transactionPoolType, newID);
    return newID;
}

void CTransactionPools::execCreateTransactionPoolMoney(const int &transactionPoolType)
{
    ui::form::FTransactionMoneyEdit *dialog = new ui::form::FTransactionMoneyEdit(transactionPoolType);
    if(dialog->exec() == QDialog::Accepted)
    {
        hacc::TDBID commID = 0;
        hacc::TDBID baseID = execAddTransactionPool(transactionPoolType, dialog->datetime(), dialog->sourceAccountID(), dialog->destinationAccountID());
        bool reallyHasCommission = dialog->commission() == 0 ? false : dialog->hasCommission();
        if(reallyHasCommission)
        {
            commID = execAddTransactionPool(HACC_TAG_ID_COMMISSION, dialog->datetime(), dialog->sourceAccountID(), dialog->commissionTo());
        }
        HACC_TRANSACTIONS->addTransferTransaction(transactionPoolType, baseID, commID,
                                                  dialog->money(), reallyHasCommission, dialog->commissionAlreadyInMoney(),
                                                  dialog->commissionInPercents(), dialog->commission(), dialog->commissionTo());

        emit created(baseID);
        if(reallyHasCommission)
        {
            emit created(commID);
        }
    }
    delete dialog;
}

void CTransactionPools::execCreateTransactionPoolThing(const int &transactionPoolType)
{
    ui::form::FTransactionPoolThingEdit *dialog = new ui::form::FTransactionPoolThingEdit(transactionPoolType);
    if(dialog->exec() == QDialog::Accepted)
    {
//        HACC_DEBUG("execCreateTransactionPoolThing" << dialog->source() << dialog->destination());
//        HACC_DEBUG("execCreateTransactionPoolThing" << HACC_ACCOUNTS->contractor(dialog->source()) << HACC_ACCOUNTS->contractor(dialog->destination()));
        hacc::TDBID newID = execAddTransactionPool(transactionPoolType, dialog->datetime(), dialog->buyerAccountID(), dialog->sellerAccountID());
        HACC_TRANSACTIONS->commitThingsTransactions(newID, transactionPoolType,
                                                    HACC_ACCOUNTS->contractor(dialog->buyerAccountID()), HACC_ACCOUNTS->contractor(dialog->sellerAccountID()),
                                                    dialog->datetime());
        emit created(newID);
    }
    else
    {
        HACC_TRANSACTIONS->removeUncommitedTransactions();
    }
    delete dialog;
}

void CTransactionPools::addTransactionSell         () { execCreateTransactionPoolThing(HACC_TAG_ID_SELLING ); }
void CTransactionPools::addTransactionBuy          () { execCreateTransactionPoolThing(HACC_TAG_ID_BUYING  ); }
void CTransactionPools::addTransactionMoneyIncoming() { execCreateTransactionPoolMoney(HACC_TAG_ID_INCOMING); }
void CTransactionPools::addTransactionMoneyOutgoing() { execCreateTransactionPoolMoney(HACC_TAG_ID_OUTGOING); }
void CTransactionPools::addTransactionLocal        () { execCreateTransactionPoolMoney(HACC_TAG_ID_TRANSFER); }

void CTransactionPools::tagsEdit(const hacc::TDBID & id)
{
    ui::form::TItemTagsEdit< ui::tag::TTagContainer < CTransactionPool, CTransactionPools > > *dialog =
            new ui::form::TItemTagsEdit< ui::tag::TTagContainer < CTransactionPool, CTransactionPools > >(id);
    if(dialog->exec() == QDialog::Accepted)
    {
    }
    delete dialog;
}

bool CTransactionPools::checkSpecialPurposeTag(const hacc::TDBID &tagID)
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

QString CTransactionPools::purposeTagsIDString()
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

       bool CTransactionPools::hasPurposeTags() { return true; }
hacc::TDBID CTransactionPools::maxDBID       () { return HACC_DB->nextID("transaction_pool"); }

QAction *CTransactionPools::addAction                        () { return CBases::addAction(0, this, SLOT(add())); }
QAction *CTransactionPools::addTransactionSellAction         () { return constructAction(base::atTransactionSell         , 0, this, SLOT(addTransactionSell())         ); }
QAction *CTransactionPools::addTransactionBuyAction          () { return constructAction(base::atTransactionBuy          , 0, this, SLOT(addTransactionBuy())          ); }
QAction *CTransactionPools::addTransactionMoneyIncomingAction() { return constructAction(base::atTransactionMoneyIncoming, 0, this, SLOT(addTransactionMoneyIncoming())); }
QAction *CTransactionPools::addTransactionMoneyOutgoingAction() { return constructAction(base::atTransactionMoneyOutgoing, 0, this, SLOT(addTransactionMoneyOutgoing())); }
QAction *CTransactionPools::addTransactionLocalAction        () { return constructAction(base::atTransactionLocal        , 0, this, SLOT(addTransactionLocal())        ); }

QAction * CTransactionPools::generateAction(base::EActionsTypes atype, QObject *reciever, const char * method)
{
    switch(atype)
    {
        HACC_GENERATE_ACTION_CASE(base::atAdd                     , tools::icons::iTransactionPool, tools::icons::oNew     , tr("New transaction pool")   , tr("Add new transaction pool"));
        HACC_GENERATE_ACTION_CASE(base::atEdit                    , tools::icons::iTransactionPool, tools::icons::oEdit    , tr("Edit transaction pool")  , tr("Edit transaction pool"   ));
        HACC_GENERATE_ACTION_CASE(base::atRemove                  , tools::icons::iTransactionPool, tools::icons::oRemove  , tr("Delete transaction pool"), tr("Delete transatransaction poolction" ));
        HACC_GENERATE_ACTION_CASE(base::atTagsEdit                , tools::icons::iTransactionPool, tools::icons::oTag     , tr("Edit tags")              , tr("Edit tags"));
        HACC_GENERATE_ACTION_CASE(base::atTransactionLocal        , tools::icons::iMoney          , tools::icons::oLocal   , tr("Add local transaction")  , tr("Add local transaction"));
        HACC_GENERATE_ACTION_CASE(base::atTransactionBuy          , tools::icons::iValuable       , tools::icons::oIncoming, tr("Buy transaction")        , tr("Add buy transaction"));
        HACC_GENERATE_ACTION_CASE(base::atTransactionSell         , tools::icons::iValuable       , tools::icons::oOutgoing, tr("Add sell transaction")   , tr("Add sell transaction"));
        HACC_GENERATE_ACTION_CASE(base::atTransactionMoneyIncoming, tools::icons::iMoney          , tools::icons::oIncoming, tr("Add incoming money")     , tr("Add incoming money transaction"));
        HACC_GENERATE_ACTION_CASE(base::atTransactionMoneyOutgoing, tools::icons::iMoney          , tools::icons::oOutgoing, tr("Add outgoing money")     , tr("Add outgoing money transaction"));
        default: break;
    }
    return new QAction("Somewhere bug", 0);
}

}
}
