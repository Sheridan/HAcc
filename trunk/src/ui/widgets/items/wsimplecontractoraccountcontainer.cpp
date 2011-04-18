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
    HACC_CONTAINER_CONNECT_CREATED_REMOVED(HACC_CONTRACTORS);
}

WSimpleContractorAccountContainer::~WSimpleContractorAccountContainer()
{}

void WSimpleContractorAccountContainer::refresh(const hacc::TDBID &createdID)
{
    //! \todo Добавить валюту счета
    if(!createdID) { cleanItems(); }
    QVariantList parametres;
    QString sql = "select "
            "accounts.id, "
            "accounts.name, "
            "accounts.icon_id, "
            "contractors.id, "
            "contractors.name, "
            "contractors.icon_id "
            "from contractors "
            "left join accounts on contractors.id=accounts.contractor_id";
    QString where = "";
    switch (m_filter)
    {
        case hacc::model::ctSelf : where += " contractors.own_account='true' "; break;
        case hacc::model::ctOther: where += " contractors.own_account='false' "; break;
        case hacc::model::ctAll:
        default: break;
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
        appendContractorAcount(
                    HACC_DB_2_DBID(q, 0),
                    HACC_DB_2_STRG(q, 1),
                    HACC_DB_2_DBID(q, 2),
                    HACC_DB_2_DBID(q, 3),
                    HACC_DB_2_STRG(q, 4),
                    HACC_DB_2_DBID(q, 5)
                    );
    }
}

void WSimpleContractorAccountContainer::appendContractorAcount(const hacc::TDBID &accountId, const QString &accountName,
                                                            const hacc::TDBID &accountIconId,  const hacc::TDBID &contractorID,
                                                            const QString &contractorName, const hacc::TDBID &contractorIconId)
{
    WSimpleContractorAccountItem *i = new WSimpleContractorAccountItem(accountId, contractorID);
    i->setAccountData(accountIconId, accountName);
    i->setContractorData(contractorIconId, contractorName);
    appendItem(i);
}

}
}
}
