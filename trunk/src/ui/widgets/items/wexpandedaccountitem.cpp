#include "wexpandedaccountitem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

WExpandedAccountItem::WExpandedAccountItem(const hacc::TDBID &id)
    : ui::item::base::WItem(1, 1, true),
      hacc::model::CAccount()
{
    setID(id);
    m_baseLayout = NULL;
    HACC_INIT_ITEM;
}

WExpandedAccountItem::~WExpandedAccountItem()
{
    delete m_baseLayout;
}

void WExpandedAccountItem::setAccountData(const hacc::TDBID &iconId, const QString &name)
{
    setIcon(0, 0, iconId);
    setText(0, 0, name);
}

void WExpandedAccountItem::buildExpanderUIEvent()
{
    appendTagsTab < ui::tag::TTagContainer <hacc::model::CAccount, hacc::model::CAccounts> >();
}

void WExpandedAccountItem::assignActions()
{
    controlLabel(0, 0)->addAction(hacc::model::CAccount::editAction());
    controlLabel(0, 0)->addAction(hacc::model::CAccount::removeAction());
    controlLabel(0, 0)->addAction(hacc::model::CAccount::tagsEditAction());
}

void WExpandedAccountItem::accountUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from accounts where id=?",
                                 QVariantList() << hacc::model::CAccount::id());
    if(q.next())
    {
        setAccountData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

hacc::TDBID WExpandedAccountItem::itemID()
{
    return hacc::model::CAccount::id();
}

}
}
}
