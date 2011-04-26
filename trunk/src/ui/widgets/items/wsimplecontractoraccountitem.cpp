#include "wsimplecontractoraccountitem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleContractorAccountItem::WSimpleContractorAccountItem(const hacc::TDBID &accountID, const hacc::TDBID &contractorID, const hacc::TDBID &currencyID)
    : base::WItem(3, 1),
      hacc::model::CContractor(),
      hacc::model::CAccount(),
      hacc::model::CCurrency()
{
    hacc::model::CContractor::setID(contractorID);
    hacc::model::CAccount   ::setID(   accountID);
    hacc::model::CCurrency  ::setID(  currencyID);
    HACC_INIT_ITEM;
}

WSimpleContractorAccountItem::~WSimpleContractorAccountItem()
{
}

void WSimpleContractorAccountItem::setContractorData(const hacc::TDBID &iconID, const QString &name)
{
    setIcon(0, 0, iconID);
    setText(0, 0, name);
}

void WSimpleContractorAccountItem::setAccountData(const hacc::TDBID &iconID, const QString &name)
{
    setIcon(1, 0, iconID);
    setText(1, 0, name);
}

void WSimpleContractorAccountItem::setCurrencyData(const hacc::TDBID &iconID, const QString &name)
{
    setIcon(2, 0, iconID);
    setText(2, 0, name);
}

void WSimpleContractorAccountItem::assignActions()
{
    controlLabel(0,0)->addAction(hacc::model::CContractor::editAction());
    controlLabel(1,0)->addAction(hacc::model::CAccount   ::editAction());
    controlLabel(2,0)->addAction(hacc::model::CCurrency  ::editAction());
}

void WSimpleContractorAccountItem::contractorUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from contractors where id=?",
                                 QVariantList() << hacc::model::CContractor::id());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setContractorData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

void WSimpleContractorAccountItem::accountUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from accounts where id=?",
                                 QVariantList() << hacc::model::CAccount::id());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setAccountData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

void WSimpleContractorAccountItem::currencyUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from currencyes where id=?",
                                 QVariantList() << hacc::model::CCurrency::id());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setCurrencyData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

hacc::TDBID WSimpleContractorAccountItem::itemID()
{
    return hacc::model::CAccount::id();
}

}
}
}
