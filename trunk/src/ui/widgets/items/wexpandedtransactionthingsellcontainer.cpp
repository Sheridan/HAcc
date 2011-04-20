#include "wexpandedtransactionthingsellcontainer.h"
#include "wexpandedtransactionthingsellitem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

WExpandedTransactionThingSellContainer::WExpandedTransactionThingSellContainer(const hacc::TDBID &parentPool, QWidget *parent) : ui::item::base::WContainer(parent)
{
    m_parentPool = parentPool;
    HACC_CONTAINER_CONNECT_CREATED_REMOVED(HACC_TRANSACTIONS);
}

WExpandedTransactionThingSellContainer::~WExpandedTransactionThingSellContainer()
{}

void WExpandedTransactionThingSellContainer::refresh(const hacc::TDBID &createdID)
{
    //! \todo Добавить валюту в сумму
    if(!createdID) { cleanItems(); }
    QVariantList parametres;
    QString sql = "select "
           /* 0*/ "base_transactions.id as base_transaction_id, "
           /* 1*/ "base_transactions.money as sell_cost, "
           /* 2*/ "(valuable_buy_transaction.money/transactions_things.amount) as buy_cost, "
           /* 3*/ "transactions_things.thing_id as thing_id, "
           /* 4*/ "things.name as thing_name, "
           /* 5*/ "things.icon_id as thing_icon_id, "
           /* 6*/ "things.manufacturer_id as manufacturer_id, "
           /* 7*/ "manufacturers.name as manufacturer_name, "
           /* 8*/ "manufacturers.icon_id as manufacturer_icon_id, "
           /* 9*/ "valuables.id as valuable_id, "
           /*10*/ "valuables.serial_number, "
           /*11*/ "valuables.owner_id as owner_id, "
           /*12*/ "contractors.icon_id as owner_icon_id, "
           /*13*/ "contractors.name as owner_name "
                  "from transactions base_transactions "
                  "left join transactions_valuables on transactions_valuables.id=base_transactions.id "
                  "left join valuables on valuables.id=transactions_valuables.valuable_id "
                  "left join transactions valuable_buy_transaction on valuable_buy_transaction.id=valuables.transaction_id "
                  "left join transactions_things on transactions_things.id=valuable_buy_transaction.id "
                  "left join things on things.id=transactions_things.thing_id "
                  "left join manufacturers on manufacturers.id=things.manufacturer_id "
                  "left join contractors on contractors.id=valuables.owner_id ";
    QString where = "base_transactions.pool_id = ? ";
    parametres << m_parentPool;
    if(createdID)
    {
        if(!where.isEmpty()) { where += " and "; }
        where += "base_transactions.id=?";
        parametres << createdID;
    }
    if(!where.isEmpty()) { sql += " where " + where; }
    QSqlQuery q = HACC_DB->query(sql, parametres);
    while(q.next())
    {
        appendTransaction(
                    HACC_DB_2_DBID(q,  0), HACC_DB_2_MONY(q,  2), HACC_DB_2_MONY(q,  1),
                    HACC_DB_2_DBID(q,  3), HACC_DB_2_STRG(q,  4), HACC_DB_2_DBID(q,  5),
                    HACC_DB_2_DBID(q,  6), HACC_DB_2_STRG(q,  7), HACC_DB_2_DBID(q,  8),
                    HACC_DB_2_DBID(q, 11), HACC_DB_2_STRG(q, 13), HACC_DB_2_DBID(q, 12),
                    HACC_DB_2_DBID(q,  9), HACC_DB_2_STRG(q, 10)
                    );
    }
}

void WExpandedTransactionThingSellContainer::appendTransaction(const hacc::TDBID &transactionID  , const hacc::TMoney &buyMoney    , const hacc::TMoney &sellMoney,
                                                               const hacc::TDBID &thingID        , const QString &thingName        , const hacc::TDBID &thingIconID,
                                                               const hacc::TDBID &manufactiurerID, const QString &manufactiurerName, const hacc::TDBID &manufactiurerIconID,
                                                               const hacc::TDBID &ownerID        , const QString &ownerName        , const hacc::TDBID &ownerIconID,
                                                               const hacc::TDBID &valuableID     , const QString &serial)
{
    WExpandedTransactionThingSellItem *i = new WExpandedTransactionThingSellItem(transactionID, thingID, manufactiurerID, ownerID, valuableID);
    i->setThingData(thingName, thingIconID);
    i->setManufacturerData(manufactiurerName, manufactiurerIconID);
    i->setTransactionData(buyMoney, sellMoney);
    i->setOwnerData(ownerIconID, ownerName);
    i->setValuableData(serial);
    appendItem(i);
}

}
}
}
