#include "wsimplecurrencycontainer.h"
#include "wsimplecurrencyitem.h"
#include "st.h"
namespace ui
{
namespace item
{
namespace simple
{

WSimpleCurrencyContainer::WSimpleCurrencyContainer(QWidget *parent) : ui::item::base::WContainer(parent)
{
    HACC_CONTAINER_CONNECT_CREATED_REMOVED(HACC_CURRENCYES);
}

WSimpleCurrencyContainer::~WSimpleCurrencyContainer()
{}

void WSimpleCurrencyContainer::appendCurrency(const hacc::TDBID &id, const QString &name, const QString &reduction)
{
    WSimpleCurrencyItem *i = new WSimpleCurrencyItem(id);
    i->setCurrencyData(name, reduction);
    appendItem(i);
}

void WSimpleCurrencyContainer::refresh(const hacc::TDBID &createdID)
{
    if(!createdID) { cleanItems(); }
    QVariantList parametres;
    QString where = "";
    QString sql = "select id, name, reduction from currencyes ";
    if(!m_searchText.isEmpty())
    {
        where += QString( " (  upper(name)      like upper(\"%%%0%%\")"
                          " or upper(reduction) like upper(\"%%%0%%\"))").arg(m_searchText);
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
        appendCurrency(
                    HACC_DB_2_DBID(q, 0),
                    HACC_DB_2_STRG(q, 1),
                    HACC_DB_2_STRG(q, 2)
                    );
    }
}

}
}
}
