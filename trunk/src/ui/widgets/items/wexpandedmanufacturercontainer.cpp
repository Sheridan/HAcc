#include "wexpandedmanufacturercontainer.h"
#include "wexpandedmanufactureritem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

WExpandedManufacturerContainer::WExpandedManufacturerContainer(QWidget *parent) : ui::item::base::WContainer(parent)
{
    HACC_CONTAINER_CONNECT_CREATED_REMOVED(HACC_MANUFACTURERS);
}

WExpandedManufacturerContainer::~WExpandedManufacturerContainer()
{}

void WExpandedManufacturerContainer::appendManufacturer(const hacc::TDBID &mId, const hacc::TDBID &mIconId, const QString &mName)
{
    WExpandedManufacturerItem *i = new WExpandedManufacturerItem(mId);
    i->setManufacturerData(mIconId, mName);
    appendItem(i);
}

void WExpandedManufacturerContainer::refresh(const hacc::TDBID &createdID)
{
    if(!createdID) { cleanItems(); }
    QVariantList parametres;
    QString where = "";
    QString sql = "select "
            "manufacturers.id, "
            "manufacturers.name, "
            "manufacturers.icon_id "
            "from manufacturers ";
    if(createdID)
    {
        if(!where.isEmpty()) { where += " and "; }
        where += "id=?";
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
