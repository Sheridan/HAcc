#include "wsimpleenumeratedthingtypecontainer.h"
#include "wsimpleenumeratedthingtypeitem.h"
#include "st.h"
namespace ui
{
namespace item
{
namespace simple
{

WSimpleEnumeratedThingTypeContainer::WSimpleEnumeratedThingTypeContainer(QWidget *parent) : base::WContainer(parent)
{
    HACC_CONTAINER_CONNECT_CREATED_REMOVED(HACC_ENUMERATED_THING_TYPES);
}

WSimpleEnumeratedThingTypeContainer::~WSimpleEnumeratedThingTypeContainer()
{}

void WSimpleEnumeratedThingTypeContainer::appendThingEnumerateType(const hacc::TDBID &eTTypeId, const QString &eTTypeName, const int &precision)
{
    WSimpleEnumeratedThingTypeItem *i = new WSimpleEnumeratedThingTypeItem(eTTypeId);
    i->setItemData(eTTypeName, precision);
    appendItem(i);
}

void WSimpleEnumeratedThingTypeContainer::refresh(const hacc::TDBID &createdID)
{
    if(!createdID) { cleanItems(); }
    QVariantList parametres;
    QString where = "";
    QString sql = "select id, name, precision from thing_enumerated_types ";
    if(!m_searchText.isEmpty())
    {
        where += QString( " (upper(name) like upper(\"%%%0%%\") ").arg(m_searchText);
    }
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
        appendThingEnumerateType(
                    HACC_DB_2_DBID(q, 0),
                    HACC_DB_2_STRG(q, 1),
                    HACC_DB_2_PREC(q, 2)
                    );
    }
}


}
}
}
