#include "wsimplevaluablecontainer.h"
#include "wsimplevaluableitem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleValuableContainer::WSimpleValuableContainer(QWidget *parent) : ui::item::base::WContainer(parent)
{
    HACC_CONTAINER_CONNECT_CREATED_REMOVED(HACC_VALUABLES);
}

WSimpleValuableContainer::~WSimpleValuableContainer()
{

}
void WSimpleValuableContainer::appendValuable(const hacc::TDBID &thingId, const hacc::TDBID &thingIconId, const QString &thingName,
                                              const hacc::TDBID &manId, const hacc::TDBID &manIconId, const QString &manName,
                                              const hacc::TDBID &valuableId, const QString &serial)
{
    WSimpleValuableItem *i = new WSimpleValuableItem(thingId, manId, valuableId);
    i->setThingData(thingIconId, thingName);
    i->setManufacturerData(manIconId, manName);
    i->setValuableData(serial);
    appendItem(i);
}

void WSimpleValuableContainer::refresh(const hacc::TDBID &createdID)
{
    if(!createdID) { cleanItems(); }
    QVariantList parametres;
    QString where = " contractors.own_account=\"true\" ";
    QString sql = "select "
            /*0*/ "things.id, "
            /*1*/ "things.icon_id, "
            /*2*/ "things.name, "
            /*3*/ "manufacturers.id, "
            /*4*/ "manufacturers.icon_id, "
            /*5*/ "manufacturers.name, "
            /*6*/ "valuables.id, "
            /*7*/ "valuables.serial_number "
                  "from things "
                  "left join manufacturers on manufacturers.id=things.manufacturer_id "
                  "left join transactions_things on transactions_things.thing_id=things.id "
                  "left join valuables on valuables.transaction_id=transactions_things.id "
                  "left join contractors on contractors.id=valuables.owner_id ";
    if(!m_searchText.isEmpty())
    {
        if(!where.isEmpty()) { where += " and "; }
        where += QString( "  (upper(things.name)             like upper(\"%%%0%%\") "
                         "or  upper(manufacturers.name)      like upper(\"%%%0%%\") "
                         "or  upper(valuables.serial_number) like upper(\"%%%0%%\")) ").arg(m_searchText);
    }
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
                    HACC_DB_2_DBID(q, 1),
                    HACC_DB_2_STRG(q, 2),
                    HACC_DB_2_DBID(q, 3),
                    HACC_DB_2_DBID(q, 4),
                    HACC_DB_2_STRG(q, 5),
                    HACC_DB_2_DBID(q, 6),
                    HACC_DB_2_STRG(q, 7)
                    );
    }
}

}
}
}
