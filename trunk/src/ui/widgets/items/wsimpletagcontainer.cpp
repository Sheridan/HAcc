#include "wsimpletagcontainer.h"
#include "wsimpletagitem.h"
#include "st.h"
namespace ui
{
namespace item
{
namespace simple
{

WSimpleTagContainer::WSimpleTagContainer(QWidget *parent) : ui::item::base::WContainer(parent)
{
    HACC_CONTAINER_CONNECT_CREATED_REMOVED(HACC_TAGS);
}

WSimpleTagContainer::~WSimpleTagContainer()
{}

void WSimpleTagContainer::appendTag(const hacc::TDBID &id, const QString &name)
{
    WSimpleTagItem *i = new WSimpleTagItem(id);
    i->setItemData(name);
    appendItem(i);
}

void WSimpleTagContainer::refresh(const hacc::TDBID &createdID)
{
    if(!createdID) { cleanItems(); }
    QVariantList parametres;
    QString where = "";
    QString sql = "select id, name from tags ";
    if(!m_searchText.isEmpty())
    {
        where += QString( " upper(name) like upper(\"%%%0%%\") ").arg(m_searchText);
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
        appendTag(
                    HACC_DB_2_DBID(q, 0),
                    HACC_DB_2_STRG(q, 1)
                    );
    }
}

}
}
}
