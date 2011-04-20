#include "wexpandedtransactionthingbuycontainer.h"
#include "wexpandedtransactionthingbuyitem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

WExpandedTransactionThingBuyContainer::WExpandedTransactionThingBuyContainer(const hacc::TDBID &parentPool, QWidget *parent) : ui::item::base::WContainer(parent)
{
    m_parentPool = parentPool;
    HACC_CONTAINER_CONNECT_CREATED_REMOVED(HACC_TRANSACTIONS);
}

WExpandedTransactionThingBuyContainer::~WExpandedTransactionThingBuyContainer()
{}

void WExpandedTransactionThingBuyContainer::refresh(const hacc::TDBID &createdID)
{
    //! \todo Добавить валюту в сумму
    if(!createdID) { cleanItems(); }
    QVariantList parametres;
    QString sql = "select "
     /* 0*/ "transactions.id, "
     /* 1*/ "transactions.money, "
     /* 2*/ "transactions_things.amount, "
     /* 3*/ "things.id, "
     /* 4*/ "things.name, "
     /* 5*/ "things.icon_id, "
     /* 6*/ "thing_enumerated_types.precision, "
     /* 7*/ "thing_enumerated_types.name, "
     /* 8*/ "manufacturers.id, "
     /* 9*/ "manufacturers.name, "
     /*10*/ "manufacturers.icon_id "
            "from transactions "
            "left join transactions_things on transactions_things.id=transactions.id "
            "left join things on things.id=transactions_things.thing_id "
            "left join thing_enumerated_types on thing_enumerated_types.id=things.enumerated_type_id "
            "left join manufacturers on manufacturers.id=things.manufacturer_id ";
    QString where = " transactions.pool_id=? ";
    parametres << m_parentPool;
    if(createdID)
    {
        if(!where.isEmpty()) { where += " and "; }
        where += "transactions.id=?";
        parametres << createdID;
    }
    if(!where.isEmpty()) { sql += " where " + where; }
    QSqlQuery q = HACC_DB->query(sql, parametres);
    while(q.next())
    {
        appendTransaction(
                    HACC_DB_2_DBID(q, 0),
                    HACC_DB_2_MONY(q, 1),
                    HACC_DB_2_AMNT(q, 2),
                    HACC_DB_2_DBID(q, 3),
                    HACC_DB_2_STRG(q, 4),
                    HACC_DB_2_DBID(q, 5),
                    HACC_DB_2_PREC(q, 6),
                    HACC_DB_2_STRG(q, 7),
                    HACC_DB_2_DBID(q, 8),
                    HACC_DB_2_STRG(q, 9),
                    HACC_DB_2_DBID(q, 10)
                    );
    }
}

void WExpandedTransactionThingBuyContainer::appendTransaction (const hacc::TDBID &transactionID  , const hacc::TMoney &money       , const hacc::TAmount &amount,
                                                               const hacc::TDBID &thingID        , const QString &thingName        , const hacc::TDBID &thingIconID,
                                                               const int &precision              , const QString &eTTName          ,
                                                               const hacc::TDBID &manufactiurerID, const QString &manufactiurerName, const hacc::TDBID &manufactiurerIconID)
{
    WExpandedTransactionThingBuyItem *i = new WExpandedTransactionThingBuyItem(transactionID, thingID, manufactiurerID);
    i->setThingData(thingName, thingIconID);
    i->setTransactionData(money, amount, precision, eTTName);
    i->setManufacturerData(manufactiurerName, manufactiurerIconID);
    appendItem(i);
}

}
}
}
