#include "wexpandedcontractorcontainer.h"
#include "wexpandedcontractoritem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

WExpandedContractorContainer::WExpandedContractorContainer(QWidget *parent) : ui::item::base::WContainer(parent)
{
    m_contractorFilter = hacc::model::ctAll;
    HACC_CONTAINER_CONNECT_CREATED_REMOVED(HACC_CONTRACTORS);
}

WExpandedContractorContainer::~WExpandedContractorContainer()
{}

WExpandedContractorItem *WExpandedContractorContainer::contractorItem(const hacc::TDBID &id)
{
    return static_cast<WExpandedContractorItem *>(item(id));
}

void WExpandedContractorContainer::refresh(const hacc::TDBID &createdID)
{
    if(!createdID) { cleanItems(); }
    QVariantList parametres;
    QString where = "";
    QString sql = "select id, name, icon_id from contractors";
    switch (m_contractorFilter)
    {
        case hacc::model::ctSelf : where += " own_account='true' "; break;
        case hacc::model::ctOther: where += " own_account='false' "; break;
        case hacc::model::ctAll:
        default: break;
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
        appendContractor(
                    HACC_DB_2_DBID(q, 0),
                    HACC_DB_2_DBID(q, 2),
                    HACC_DB_2_STRG(q, 1)
                    );
    }
}

void WExpandedContractorContainer::appendContractor(const hacc::TDBID &id, const hacc::TDBID &iconId, const QString &name)
{
    WExpandedContractorItem *i = new WExpandedContractorItem(id);
    i->setItemData(iconId, name);
    appendItem(i);
}

void WExpandedContractorContainer::setAccountsFilter(int filter)
{
    m_contractorFilter = static_cast<hacc::model::EContractorFilter>(filter);
    refresh();
}

}
}
}
