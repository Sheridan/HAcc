#include "wexpandedvaluablecontainer.h"
#include "wexpandedvaluableitem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

WExpandedValuableContainer::WExpandedValuableContainer(QWidget *parent) : ui::item::base::WContainer(parent)
{
    HACC_CONTAINER_CONNECT_CREATED_REMOVED(HACC_VALUABLES);
}

WExpandedValuableContainer::~WExpandedValuableContainer()
{}

void WExpandedValuableContainer::appendValuable(const hacc::TDBID &valuableID, const QString &serial,
                                                const hacc::TDBID &thingId   , const hacc::TDBID &thingIconId, const QString &thingName,
                                                const hacc::TDBID &manId     , const hacc::TDBID &manIconId  , const QString &manName,
                                                const hacc::TDBID &transId   , const hacc::TMoney &cost      , const QDateTime &purchaseDate)
{
    WExpandedValuableItem *i = new WExpandedValuableItem(valuableID, thingId, manId, transId);
    i->setThingData(thingIconId, thingName);
    i->setManufacturerData(manIconId, manName);
    i->setTransactionData(cost, purchaseDate);
    i->setValuableData(serial);
    appendItem(i);
}

void WExpandedValuableContainer::refresh(const hacc::TDBID &createdID)
{
    if(!createdID) { cleanItems(); }
    QVariantList parametres;
    QString where = "";
    QString sql = "select "
           /* 0*/ "valuables.id, "
           /* 1*/ "valuables.transaction_id, "
           /* 2*/ "(transactions.money /  transactions_things.amount) as cost, "
           /* 3*/ "transactions_pool.date_time, "
           /* 4*/ "things.id, "
           /* 5*/ "things.icon_id, "
           /* 6*/ "things.name, "
           /* 7*/ "manufacturers.id, "
           /* 8*/ "manufacturers.icon_id, "
           /* 9*/ "manufacturers.name, "
           /*10*/ "valuables.serial_number "
                  "from valuables "
                  "left join transactions on transactions.id = valuables.transaction_id "
                  "left join transactions_things on transactions_things.id=transactions.id "
                  "left join transactions_pool on transactions_pool.id = transactions.pool_id "
                  "left join things on things.id = transactions_things.thing_id "
                  "left join manufacturers on manufacturers.id=things.manufacturer_id ";
    if(createdID)
    {
        if(!where.isEmpty()) { where += " and "; }
        where += "valuables.id=?";
        parametres << createdID;
    }
    if(!where.isEmpty()) { sql += " where " + where; }
    QSqlQuery q = HACC_DB->query(sql, parametres);
    while(q.next())
    {
        appendValuable(
                    HACC_DB_2_DBID(q, 0),
                    HACC_DB_2_STRG(q, 10),
                    HACC_DB_2_DBID(q, 4),
                    HACC_DB_2_DBID(q, 5),
                    HACC_DB_2_STRG(q, 6),
                    HACC_DB_2_DBID(q, 7),
                    HACC_DB_2_DBID(q, 8),
                    HACC_DB_2_STRG(q, 9),
                    HACC_DB_2_DBID(q, 1),
                    HACC_DB_2_MONY(q, 2),
                    HACC_DB_2_DATI(q, 3)
                    );
    }
}

}
}
}
