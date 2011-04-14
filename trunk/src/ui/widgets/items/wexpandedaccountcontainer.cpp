#include "wexpandedaccountcontainer.h"
#include "wexpandedaccountitem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

WExpandedAccountContainer::WExpandedAccountContainer(const hacc::TDBID &parentContractor, QWidget *parent) : ui::item::base::WContainer(parent)
{
    m_parentContractor = parentContractor;
    HACC_CONTAINER_CONNECT_CREATED_REMOVED(HACC_ACCOUNTS);
}

WExpandedAccountContainer::~WExpandedAccountContainer()
{}

void WExpandedAccountContainer::refresh(const hacc::TDBID &createdID)
{
    if(!createdID) { cleanItems(); }
    QString sql = "select id, name, icon_id from accounts where contractor_id=?";
    QVariantList parametres;
    parametres << m_parentContractor;
    if(createdID)
    {
        sql += " and id=?";
        parametres << createdID;
    }
    QSqlQuery q = HACC_DB->query(sql, parametres);
    while(q.next())
    {
        appendAcount(
                    HACC_DB_2_DBID(q, 0),
                    HACC_DB_2_DBID(q, 2),
                    HACC_DB_2_STRG(q, 1)
                    );
    }
}

void WExpandedAccountContainer::appendAcount(const hacc::TDBID &id, const hacc::TDBID &iconId, const QString &name)
{
    WExpandedAccountItem *i = new WExpandedAccountItem(id);
    i->setAccountData(iconId, name);
    appendItem(i);
}

}
}
}
