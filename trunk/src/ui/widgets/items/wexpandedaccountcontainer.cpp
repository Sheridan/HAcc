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
    QString sql = "select "
            /* 0*/ "accounts.id, "
            /* 1*/ "accounts.name, "
            /* 2*/ "accounts.icon_id, "
            /* 3*/ "currencyes.id, "
            /* 4*/ "currencyes.name, "
            /* 5*/ "currencyes.icon_id "
                   "from accounts "
                   "left join currencyes on currencyes.id=accounts.currency_id "
                   "where accounts.contractor_id=?";
    QVariantList parametres;
    parametres << m_parentContractor;
    if(createdID)
    {
        sql += " and accounts.id=?";
        parametres << createdID;
    }
    QSqlQuery q = HACC_DB->query(sql, parametres);
    while(q.next())
    {
        appendRow   (
                    HACC_DB_2_DBID(q, 0),
                    HACC_DB_2_DBID(q, 2),
                    HACC_DB_2_STRG(q, 1),
                    HACC_DB_2_DBID(q, 3),
                    HACC_DB_2_DBID(q, 5),
                    HACC_DB_2_STRG(q, 4)
                    );
    }
}

void WExpandedAccountContainer::appendRow(const hacc::TDBID &accountID , const hacc::TDBID &accountIconID , const QString &accountName ,
                                          const hacc::TDBID &currencyID, const hacc::TDBID &currencyIconID, const QString &currencyName)
{
    WExpandedAccountItem *i = new WExpandedAccountItem(accountID, currencyID);
    i->setAccountData(accountIconID, accountName);
    i->setCurrencyData(currencyIconID, currencyName);
    appendItem(i);
}

}
}
}
