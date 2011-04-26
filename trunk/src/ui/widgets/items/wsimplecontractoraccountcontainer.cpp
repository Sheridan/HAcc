#include "wsimplecontractoraccountcontainer.h"
#include "wsimplecontractoraccountitem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleContractorAccountContainer::WSimpleContractorAccountContainer(hacc::model::EContractorFilter filter, QWidget *parent)
    : ui::item::base::WContainer(parent)
{
    m_filter = filter;
    m_currencyID = 0;
    HACC_CONTAINER_CONNECT_CREATED_REMOVED(HACC_CONTRACTORS);
}

WSimpleContractorAccountContainer::~WSimpleContractorAccountContainer()
{}

void WSimpleContractorAccountContainer::refresh(const hacc::TDBID &createdID)
{
    if(!createdID) { cleanItems(); }
    QVariantList parametres;
    QString sql = "select "
     /* 0*/ "accounts.id, "
     /* 1*/ "accounts.name, "
     /* 2*/ "accounts.icon_id, "
     /* 3*/ "contractors.id, "
     /* 4*/ "contractors.name, "
     /* 5*/ "contractors.icon_id, "
     /* 6*/ "currencyes.id, "
     /* 7*/ "currencyes.name, "
     /* 8*/ "currencyes.icon_id "
            "from contractors "
            "left join accounts on contractors.id=accounts.contractor_id "
            "left join currencyes on currencyes.id=accounts.currency_id";
    QString where = "";
    switch (m_filter)
    {
        case hacc::model::ctSelf : where += " contractors.own_account='true' "; break;
        case hacc::model::ctOther: where += " contractors.own_account='false' "; break;
        case hacc::model::ctAll:
        default: break;
    }
    if(m_currencyID)
    {
        if(!where.isEmpty()) { where += " and "; }
        where += " currencyes.id=? ";
        parametres << m_currencyID;
    }
    if(!m_searchText.isEmpty())
    {
        if(!where.isEmpty()) { where += " and "; }
        where += QString( " (upper(accounts.name)    like upper(\"%%%0%%\") or  "
                          "  upper(contractors.name) like upper(\"%%%0%%\")   ) ").arg(m_searchText);
    }
    if(createdID)
    {
        if(!where.isEmpty()) { where += " and "; }
        where += " contractors.id=? ";
        parametres << createdID;
    }
    if(!where.isEmpty()) { sql += " where " + where; }
    QSqlQuery q = HACC_DB->query(sql, parametres);
    while(q.next())
    {
        appendRow(
                    HACC_DB_2_DBID(q, 0),
                    HACC_DB_2_STRG(q, 1),
                    HACC_DB_2_DBID(q, 2),
                    HACC_DB_2_DBID(q, 3),
                    HACC_DB_2_STRG(q, 4),
                    HACC_DB_2_DBID(q, 5),
                    HACC_DB_2_DBID(q, 6),
                    HACC_DB_2_STRG(q, 7),
                    HACC_DB_2_DBID(q, 8)
                 );
    }
}

void WSimpleContractorAccountContainer::appendRow(const hacc::TDBID &accountID   , const QString &accountName   , const hacc::TDBID &accountIconID,
                                                  const hacc::TDBID &contractorID, const QString &contractorName, const hacc::TDBID &contractorIconID,
                                                  const hacc::TDBID &currencyID  , const QString &currencyName  , const hacc::TDBID &currencyIconID)
{
    WSimpleContractorAccountItem *i = new WSimpleContractorAccountItem(accountID, contractorID, currencyID);
    i->setAccountData   (accountIconID   , accountName   );
    i->setContractorData(contractorIconID, contractorName);
    i->setCurrencyData  (currencyIconID  , currencyName  );
    appendItem(i);
}

void WSimpleContractorAccountContainer::setCurrencyFilter(const hacc::TDBID &currencyID)
{
    m_currencyID = currencyID;
    refresh();
}

}
}
}
