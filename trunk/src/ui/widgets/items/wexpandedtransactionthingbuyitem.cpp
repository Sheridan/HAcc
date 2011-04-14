#include "wexpandedtransactionthingbuyitem.h"
#include "convert.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

#define HACC_TTI_AMONT_PLACE 2, 0
#define HACC_TTI_MONEY_PLACE 3, 0

WExpandedTransactionThingBuyItem::WExpandedTransactionThingBuyItem(const hacc::TDBID &transactionID, const hacc::TDBID &thingID, const hacc::TDBID &manufactiurerID)
    : WExpandedTransactionThingItem(4, transactionID, thingID, manufactiurerID)
{
    HACC_INIT_ITEM;
}

WExpandedTransactionThingBuyItem::~WExpandedTransactionThingBuyItem()
{
}

void WExpandedTransactionThingBuyItem::setTransactionData(const hacc::TMoney &money, const hacc::TAmount &amount,
                                                          const int &precision     , const QString &eTTName)
{
    setText(HACC_TTI_AMONT_PLACE, tools::convert::amountToString(amount, precision) + " " + eTTName);
    setText(HACC_TTI_MONEY_PLACE, tools::convert::moneyToString(money));
}

void WExpandedTransactionThingBuyItem::assignActions()
{
    WExpandedTransactionThingItem::assignActions();

    controlLabel(HACC_TTI_MONEY_PLACE)->addAction(hacc::model::CTransaction::editAction());
    controlLabel(HACC_TTI_MONEY_PLACE)->addAction(hacc::model::CTransaction::removeAction());
    controlLabel(HACC_TTI_MONEY_PLACE)->addAction(hacc::model::CTransaction::tagsEditAction());
}

void WExpandedTransactionThingBuyItem::transactionUpdated()
{
    QSqlQuery q = HACC_DB->query("select "
                          /* 0*/ "transactions.money, "
                          /* 1*/ "transactions_things.amount, "
                          /* 2*/ "things.name, "
                          /* 3*/ "things.icon_id, "
                          /* 4*/ "thing_enumerated_types.precision, "
                          /* 5*/ "thing_enumerated_types.name, "
                          /* 6*/ "manufacturers.name, "
                          /* 7*/ "manufacturers.icon_id "
                                 "from transactions "
                                 "left join transactions_things on transactions_things.id=transactions.id "
                                 "left join things on things.id=transactions_things.thing_id "
                                 "left join thing_enumerated_types on thing_enumerated_types.id=things.enumerated_type_id "
                                 "left join manufacturers on manufacturers.id=things.manufacturer_id "
                                 "where transactions.id=?",
                                 QVariantList() << hacc::model::CTransaction::id());
    if(q.next())
    {
        setTransactionData (HACC_DB_2_MONY(q, 0),
                            HACC_DB_2_AMNT(q, 1),
                            HACC_DB_2_PREC(q, 4),
                            HACC_DB_2_STRG(q, 5));
        setThingData       (HACC_DB_2_STRG(q, 2),
                            HACC_DB_2_DBID(q, 3));
        setManufacturerData(HACC_DB_2_STRG(q, 6),
                            HACC_DB_2_DBID(q, 7));
    }
}

}
}
}
