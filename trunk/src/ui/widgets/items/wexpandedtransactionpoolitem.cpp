#include "wexpandedtransactionpoolitem.h"
#include "convert.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

#define HACC_TPI_SRC_CTR_PLACE 0, 0
#define HACC_TPI_DST_CTR_PLACE 1, 0
#define HACC_TPI_SRC_ACC_PLACE 0, 1
#define HACC_TPI_DST_ACC_PLACE 1, 1
#define HACC_TPI_DATE_PLACE    2, 0
#define HACC_TPI_TIME_PLACE    2, 1
#define HACC_TPI_TRCOUNT_PLACE 3, 0
#define HACC_TPI_TRSUMM_PLACE  3, 1


WExpandedTransactionPoolItem::WExpandedTransactionPoolItem(const hacc::TDBID &poolID,
                                                           const hacc::TDBID &accountSourceID,
                                                           const hacc::TDBID &accountDestinationID,
                                                           const hacc::TDBID &contractorSourceID,
                                                           const hacc::TDBID &contractorDestinationID)
    : ui::item::base::WItem(4, 2, true),
      hacc::model::CTransactionPool(),
      hacc::model::composite::CContractorAccountSource(),
      hacc::model::composite::CContractorAccountDestination()
{
    hacc::model::CTransactionPool::setID(poolID);
    hacc::model::composite::CContractorAccountSource::setAccountID(accountSourceID);
    hacc::model::composite::CContractorAccountSource::setContractorID(contractorSourceID);
    hacc::model::composite::CContractorAccountDestination::setAccountID(accountDestinationID);
    hacc::model::composite::CContractorAccountDestination::setContractorID(contractorDestinationID);

    HACC_INIT_ITEM;
}

WExpandedTransactionPoolItem::~WExpandedTransactionPoolItem()
{}

void WExpandedTransactionPoolItem::setTransactionPoolData(const QDateTime &datetime, const uint &transactionsCount,
                                                          const hacc::TMoney &transactionsSumm, const int &transactionPoolType)
{
    setText(HACC_TPI_DATE_PLACE, tools::convert::datetimeToDateString(datetime));
    setText(HACC_TPI_TIME_PLACE, tools::convert::datetimeToTimeString(datetime));
    setText(HACC_TPI_TRCOUNT_PLACE, QString::number(transactionsCount));
    setText(HACC_TPI_TRSUMM_PLACE, tools::convert::moneyToString(transactionsSumm));
    setIcon(HACC_TPI_TRSUMM_PLACE, HACC_ICONS->icon(transactionPoolType));
}

void WExpandedTransactionPoolItem::setSourceContractorData(const hacc::TDBID &iconID, const QString &name)
{
    setIcon(HACC_TPI_SRC_CTR_PLACE, iconID);
    setText(HACC_TPI_SRC_CTR_PLACE, name);
}

void WExpandedTransactionPoolItem::setSourceAccountData(const hacc::TDBID &iconID, const QString &name)
{
    setIcon(HACC_TPI_SRC_ACC_PLACE, iconID);
    setText(HACC_TPI_SRC_ACC_PLACE, name);
}

void WExpandedTransactionPoolItem::setDestinationContractorData(const hacc::TDBID &iconID, const QString &name)
{
    setIcon(HACC_TPI_DST_CTR_PLACE, iconID);
    setText(HACC_TPI_DST_CTR_PLACE, name);
}

void WExpandedTransactionPoolItem::setDestinationAccountData(const hacc::TDBID &iconID, const QString &name)
{
    setIcon(HACC_TPI_DST_ACC_PLACE, iconID);
    setText(HACC_TPI_DST_ACC_PLACE, name);
}

void WExpandedTransactionPoolItem::assignActions()
{
    controlLabel(HACC_TPI_SRC_CTR_PLACE)->addAction(hacc::model::composite::CContractorAccountSource::contractorEditAction());
    controlLabel(HACC_TPI_SRC_CTR_PLACE)->addAction(hacc::model::composite::CContractorAccountSource::contractorRemoveAction());
    controlLabel(HACC_TPI_SRC_CTR_PLACE)->addAction(hacc::model::composite::CContractorAccountSource::contractorTagsEditAction());

    controlLabel(HACC_TPI_SRC_ACC_PLACE)->addAction(hacc::model::composite::CContractorAccountSource::accountEditAction());
    controlLabel(HACC_TPI_SRC_ACC_PLACE)->addAction(hacc::model::composite::CContractorAccountSource::accountRemoveAction());
    controlLabel(HACC_TPI_SRC_ACC_PLACE)->addAction(hacc::model::composite::CContractorAccountSource::accountTagsEditAction());

    controlLabel(HACC_TPI_DST_CTR_PLACE)->addAction(hacc::model::composite::CContractorAccountDestination::contractorEditAction());
    controlLabel(HACC_TPI_DST_CTR_PLACE)->addAction(hacc::model::composite::CContractorAccountDestination::contractorRemoveAction());
    controlLabel(HACC_TPI_DST_CTR_PLACE)->addAction(hacc::model::composite::CContractorAccountDestination::contractorTagsEditAction());

    controlLabel(HACC_TPI_DST_ACC_PLACE)->addAction(hacc::model::composite::CContractorAccountDestination::accountEditAction());
    controlLabel(HACC_TPI_DST_ACC_PLACE)->addAction(hacc::model::composite::CContractorAccountDestination::accountRemoveAction());
    controlLabel(HACC_TPI_DST_ACC_PLACE)->addAction(hacc::model::composite::CContractorAccountDestination::accountTagsEditAction());

    controlLabel(HACC_TPI_TRSUMM_PLACE)->addAction(hacc::model::CTransactionPool::editAction());
    controlLabel(HACC_TPI_TRSUMM_PLACE)->addAction(hacc::model::CTransactionPool::removeAction());
    controlLabel(HACC_TPI_TRSUMM_PLACE)->addAction(hacc::model::CTransactionPool::tagsEditAction());
}

void WExpandedTransactionPoolItem::transactionPoolUpdated()
{
    //! \todo Добавить валюту в сумму
    QSqlQuery q = HACC_DB->query("select "
                           /*0*/ "transactions_pool.date_time ,"
                           /*1*/ "count(transactions.id) as trcnt, "
                           /*2*/ "sum(transactions.money) as trsum, "
                           /*3*/ "transactions_pools_tags.tag_id "
                                 "from transactions_pool "
                                 "left join transactions on transactions.pool_id=transactions_pool.id "
                                 "left join transactions_pools_tags on transactions_pools_tags.transactions_pool_id=transactions_pool.id "
                                 "where transactions_pool.id=? and " + HACC_TRANSACTIONS_POOLS->whereTagsInPurposeTags() + " "
                                 "group by transactions.pool_id ",
                                 QVariantList() << hacc::model::CTransactionPool::id());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setTransactionPoolData(
                    HACC_DB_2_DATI(q, 0),
                    HACC_DB_2_DBID(q, 1),
                    HACC_DB_2_MONY(q, 2),
                    HACC_DB_2_TYPE(q, 3)
                    );
    }
}

void WExpandedTransactionPoolItem::sourceContractorUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from contractors where id=?",
                                 QVariantList() << hacc::model::composite::CContractorAccountSource::contractorID());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setSourceContractorData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

void WExpandedTransactionPoolItem::sourceAccountUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from accounts where id=?",
                                 QVariantList() << hacc::model::composite::CContractorAccountSource::accountID());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setSourceAccountData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

void WExpandedTransactionPoolItem::destinationContractorUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from contractors where id=?",
                                 QVariantList() << hacc::model::composite::CContractorAccountDestination::contractorID());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setDestinationContractorData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

void WExpandedTransactionPoolItem::destinationAccountUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from accounts where id=?",
                                 QVariantList() << hacc::model::composite::CContractorAccountDestination::accountID());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setDestinationAccountData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

hacc::TDBID WExpandedTransactionPoolItem::itemID()
{
    return hacc::model::CTransactionPool::id();
}

}
}
}
