#include "wsimplemanufacturercontainer.h"
#include "wsimplemanufactureritem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleManufacturerContainer::WSimpleManufacturerContainer(QWidget *parent) : ui::item::base::WContainer(parent)
{
    HACC_CONTAINER_CONNECT_CREATED_REMOVED(HACC_MANUFACTURERS);
}

WSimpleManufacturerContainer::~WSimpleManufacturerContainer()
{}

void WSimpleManufacturerContainer::appendManufacturer(const hacc::TDBID &manufacturerID, const hacc::TDBID &manufacturerIconID, const QString &manufacturerName)
{
    WSimpleManufacturerItem *i = new WSimpleManufacturerItem(manufacturerID);
    i->setItemData(manufacturerIconID, manufacturerName);
    appendItem(i);
}

void WSimpleManufacturerContainer::refresh(const hacc::TDBID &createdID)
{
    if(!createdID) { cleanItems(); }
    QVariantList parametres;
    QString where = "";
    QString sql = "select "
            "manufacturers.id, "
            "manufacturers.name, "
            "manufacturers.icon_id "
            "from manufacturers ";
    if(!m_searchText.isEmpty())
    {
        where += QString( " (upper(manufacturers.name) like upper(\"%%%0%%\")) ").arg(m_searchText);
    }
    if(createdID)
    {
        if(!where.isEmpty()) { where += " and "; }
        where += "manufacturers.id=?";
        parametres << createdID;
    }
    if(!where.isEmpty()) { sql += " where " + where; }
    QSqlQuery q = HACC_DB->query(sql, parametres);
    while(q.next())
    {
        appendManufacturer(
                    HACC_DB_2_DBID(q, 0),
                    HACC_DB_2_DBID(q, 2),
                    HACC_DB_2_STRG(q, 1)
                    );
    }
}

}
}
}
