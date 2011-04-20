#include "wexpandedtransactionpoolcontainer.h"
#include "wexpandedtransactionpoolitem.h"
#include "wexpandedtransactionpoolthingitem.h"
#include "wexpandedtransactionpoolmoneyitem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

WExpandedTransactionPoolContainer::WExpandedTransactionPoolContainer(QWidget *parent) : ui::item::base::WContainer(parent)
{
    HACC_CONTAINER_CONNECT_CREATED_REMOVED(HACC_TRANSACTIONS_POOLS);
}

WExpandedTransactionPoolContainer::~WExpandedTransactionPoolContainer()
{}

WExpandedTransactionPoolItem *WExpandedTransactionPoolContainer::transactionPoolItem(const hacc::TDBID &id)
{
    return static_cast<WExpandedTransactionPoolItem *>(item(id));
}

void WExpandedTransactionPoolContainer::appendTransactionPool(const hacc::TDBID &poolID,                  const QDateTime &datetime,                const int &transactionPoolType,
                                                              const uint &transactionsCount,              const hacc::TMoney &transactionsSumm,
                                                              const hacc::TDBID &accountSourceID,         const QString &accountSourceName,         const hacc::TDBID &accountSourceIconID,
                                                              const hacc::TDBID &accountDestinationID,    const QString &accountDestinationName,    const hacc::TDBID &accountDestinationIconID,
                                                              const hacc::TDBID &contractorSourceID,      const QString &contractorSourceName,      const hacc::TDBID &contractorSourceIconID,
                                                              const hacc::TDBID &contractorDestinationID, const QString &contractorDestinationName, const hacc::TDBID &contractorDestinationIconID)
{
    WExpandedTransactionPoolItem *i = NULL;
    switch(transactionPoolType)
    {
    case HACC_TAG_ID_BUYING:
    case HACC_TAG_ID_SELLING:
    {
        i = new WExpandedTransactionPoolThingItem(poolID,
                                                  accountSourceID,
                                                  accountDestinationID,
                                                  contractorSourceID,
                                                  contractorDestinationID);
    }
        break;
    case HACC_TAG_ID_INCOMING  :
    case HACC_TAG_ID_OUTGOING  :
    case HACC_TAG_ID_TRANSFER  :
    case HACC_TAG_ID_COMMISSION:
    {
        i = new WExpandedTransactionPoolMoneyItem(poolID,
                                                  accountSourceID,
                                                  accountDestinationID,
                                                  contractorSourceID,
                                                  contractorDestinationID);
    }
        break;
    }

    if(!i) return; // временно

    i->setTransactionPoolData(datetime, transactionsCount , transactionsSumm, transactionPoolType);
    i->setSourceContractorData     (contractorSourceIconID     , contractorSourceName     );
    i->setSourceAccountData        (accountSourceIconID        , accountSourceName        );
    i->setDestinationContractorData(contractorDestinationIconID, contractorDestinationName);
    i->setDestinationAccountData   (accountDestinationIconID   , accountDestinationName   );
    appendItem(i);
}

void WExpandedTransactionPoolContainer::refresh(const hacc::TDBID &createdID)
{
    //! \todo Добавить валюту в сумму
    if(!createdID) { cleanItems(); }
    QVariantList parametres;
    QString where = HACC_TRANSACTIONS_POOLS->whereTagsInPurposeTags();// "transactions_pools_tags.tag_id in (4,5,6,7,8,9)";
    QString groupBy = " transactions.pool_id ";
    QString sql =  "select "
            /* 0*/ "transactions_pool.id, "
            /* 1*/ "transactions_pool.date_time, "
            /* 2*/ "count(transactions.id) as trcnt, "
            /* 3*/ "sum(transactions.money) as trsum, "
            /* 4*/ "accsrc.id as accsrc_id, "
            /* 5*/ "accsrc.name as accsrc_name, "
            /* 6*/ "accsrc.icon_id as accsrc_icon_id, "
            /* 7*/ "accdst.id as accdst_id, "
            /* 8*/ "accdst.name as accdst_name, "
            /* 9*/ "accdst.icon_id as accdst_icon_id, "
            /*10*/ "consrc.id as consrc_id, "
            /*11*/ "consrc.name as consrc_name, "
            /*12*/ "consrc.icon_id as consrc_icon_id, "
            /*13*/ "condst.id as condst_id, "
            /*14*/ "condst.name as condst_name, "
            /*15*/ "condst.icon_id as condst_icon_id, "
            /*16*/ "transactions_pools_tags.tag_id "
            "from transactions_pool "
            "left join transactions on transactions.pool_id=transactions_pool.id "
            "left join accounts accsrc on transactions_pool.source_account_id=accsrc.id "
            "left join accounts accdst on transactions_pool.destination_account_id=accdst.id "
            "left join contractors consrc on accsrc.contractor_id=consrc.id "
            "left join contractors condst on accdst.contractor_id=condst.id "
            "left join transactions_pools_tags on transactions_pools_tags.transactions_pool_id=transactions_pool.id ";
    if(createdID)
    {
        if(!where.isEmpty()) { where += " and "; }
        where += "transactions_pool.id=?";
        parametres << createdID;
    }
    if(!where.isEmpty()) { sql += " where " + where; }
    QSqlQuery q = HACC_DB->query(sql + " group by " + groupBy, parametres);
    while(q.next())
    {
        appendTransactionPool(
                    HACC_DB_2_DBID(q, 0),
                    HACC_DB_2_DATI(q, 1),
                    HACC_DB_2_TYPE(q, 16),
                    HACC_DB_2_DBID(q, 2),
                    HACC_DB_2_MONY(q, 3),
                    HACC_DB_2_DBID(q, 4),
                    HACC_DB_2_STRG(q, 5),
                    HACC_DB_2_DBID(q, 6),
                    HACC_DB_2_DBID(q, 7),
                    HACC_DB_2_STRG(q, 8),
                    HACC_DB_2_DBID(q, 9),
                    HACC_DB_2_DBID(q, 10),
                    HACC_DB_2_STRG(q, 11),
                    HACC_DB_2_DBID(q, 12),
                    HACC_DB_2_DBID(q, 13),
                    HACC_DB_2_STRG(q, 14),
                    HACC_DB_2_DBID(q, 15)
                    );
    }
}

}
}
}
