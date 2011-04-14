#include "wsimplecontractorcontainer.h"
#include "wsimplecontractoritem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleContractorContainer::WSimpleContractorContainer(hacc::model::EContractorFilter filter, QWidget *parent)
    : ui::item::base::WContainer(parent)
{
    m_filter = filter;
    HACC_CONTAINER_CONNECT_CREATED_REMOVED(HACC_CONTRACTORS);
}

WSimpleContractorContainer::~WSimpleContractorContainer()
{}

void WSimpleContractorContainer::refresh(const hacc::TDBID &createdID)
{
    if(!createdID) { cleanItems(); }
    QVariantList parametres;
    QString sql = "select "
            "contractors.id, "
            "contractors.name, "
            "contractors.icon_id "
            "from contractors ";
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
        where += QString( " (upper(contractors.name) like upper(\"%%%0%%\")) ").arg(m_searchText);
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
        appendContractor(
                    HACC_DB_2_DBID(q, 0),
                    HACC_DB_2_STRG(q, 1),
                    HACC_DB_2_DBID(q, 2)
                    );
    }
}

void WSimpleContractorContainer::appendContractor(const hacc::TDBID &contractorID, const QString &contractorName, const hacc::TDBID &contractorIconId)
{
    WSimpleContractorItem *i = new WSimpleContractorItem(contractorID);
    i->setContractorData(contractorIconId, contractorName);
    appendItem(i);
}

}
}
}
