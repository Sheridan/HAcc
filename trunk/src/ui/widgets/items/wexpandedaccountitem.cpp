#include "wexpandedaccountitem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

WExpandedAccountItem::WExpandedAccountItem(const hacc::TDBID &accountID, const hacc::TDBID &currencyID)
    : ui::item::base::WItem(2, 1, true),
      hacc::model::CAccount(),
      hacc::model::CCurrency()
{
    hacc::model::CAccount ::setID( accountID);
    hacc::model::CCurrency::setID(currencyID);
    m_baseLayout = NULL;
    HACC_INIT_ITEM;
}

WExpandedAccountItem::~WExpandedAccountItem()
{
    delete m_baseLayout;
}

void WExpandedAccountItem::setAccountData(const hacc::TDBID &iconID , const QString &name)
{
    setIcon(0, 0, iconID);
    setText(0, 0, name);
}

void WExpandedAccountItem::setCurrencyData(const hacc::TDBID &iconID , const QString &name)
{
    setIcon(1, 0, iconID);
    setText(1, 0, name);
}

void WExpandedAccountItem::buildExpanderUIEvent()
{
    appendTagsTab < ui::tag::TTagContainer <hacc::model::CAccount, hacc::model::CAccounts> >();
}

/**
  Если счет - это счет контрагента "Ничто" или количество счетов контрагента - один, то удалять нельзя
  */
void WExpandedAccountItem::assignActions()
{
    controlLabel(0, 0)->addAction(hacc::model::CAccount::editAction());
    QSqlQuery q = HACC_DB->query("select "
                          /* 0*/ "(acc_base.contractor_id > 1) as is_not_nothing, "
                          /* 1*/ "(count(acc_cnt.id) > 1) as not_one "
                                 "from accounts acc_base "
                                 "left join accounts acc_cnt on acc_cnt.contractor_id = acc_base.contractor_id "
                                 "where acc_base.id=?",
                                 QVariantList() << itemID());
    q.next();
    if(HACC_DB_2_BOOL(q, 0) && HACC_DB_2_BOOL(q, 1))
    {
        controlLabel(0, 0)->addAction(hacc::model::CAccount::removeAction());
    }
    controlLabel(0, 0)->addAction(hacc::model::CAccount::tagsEditAction());

    controlLabel(1, 0)->addAction(hacc::model::CCurrency::editAction());
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

void WExpandedAccountItem::currencyUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from currencyes where id=?",
                                 QVariantList() << hacc::model::CCurrency::id());
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
