#include "wsimplethingcontainer.h"
#include "wsimplethingitem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleThingContainer::WSimpleThingContainer(QWidget *parent) : ui::item::base::WContainer(parent)
{
    HACC_CONTAINER_CONNECT_CREATED_REMOVED(HACC_THINGS);
}

WSimpleThingContainer::~WSimpleThingContainer()
{

}
void WSimpleThingContainer::appendThing(const hacc::TDBID &thingId, const hacc::TDBID &thingIconId,
                                     const QString &thingName, const hacc::TDBID &manId,
                                     const hacc::TDBID &manIconId, const QString &manName)
{
    WSimpleThingItem *i = new WSimpleThingItem(thingId, manId);
    i->setThingData(thingIconId, thingName);
    i->setManufacturerData(manIconId, manName);
    appendItem(i);
}

void WSimpleThingContainer::refresh(const hacc::TDBID &createdID)
{
    if(!createdID) { cleanItems(); }
    QVariantList parametres;
    QString where = "";
    QString sql = "select "
            "things.id, "
            "things.icon_id, "
            "things.name, "
            "manufacturers.id, "
            "manufacturers.icon_id, "
            "manufacturers.name "
            "from things "
            "left join manufacturers on manufacturers.id=things.manufacturer_id ";
    if(!m_searchText.isEmpty())
    {
        where += QString( "  (upper(things.name)        like upper(\"%%%0%%\") "
                         "or  upper(manufacturers.name) like upper(\"%%%0%%\")) ").arg(m_searchText);
    }
    if(createdID)
    {
        if(!where.isEmpty()) { where += " and "; }
        where += "things.id=?";
        parametres << createdID;
    }
    if(!where.isEmpty()) { sql += " where " + where; }
    QSqlQuery q = HACC_DB->query(sql, parametres);
    while(q.next())
    {
        appendThing(
                    HACC_DB_2_DBID(q, 0),
                    HACC_DB_2_DBID(q, 1),
                    HACC_DB_2_STRG(q, 2),
                    HACC_DB_2_DBID(q, 3),
                    HACC_DB_2_DBID(q, 4),
                    HACC_DB_2_STRG(q, 5)
                    );
    }
}

}
}
}
