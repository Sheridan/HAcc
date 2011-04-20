#include "wexpandedtransactionthingsellitem.h"
#include "convert.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

#define HACC_TTI_BUY_MONEY_PLACE  2, 0
#define HACC_TTI_SELL_MONEY_PLACE 3, 0
#define HACC_TTI_OWNER_PLACE      4, 0
#define HACC_TTI_SERIAL_PLACE     5, 0

WExpandedTransactionThingSellItem::WExpandedTransactionThingSellItem(const hacc::TDBID &transactionID,
                                                                     const hacc::TDBID &thingID,
                                                                     const hacc::TDBID &manufactiurerID,
                                                                     const hacc::TDBID &ownerID,
                                                                     const hacc::TDBID &valuableID)
    : WExpandedTransactionThingItem(6, transactionID, thingID, manufactiurerID),
      hacc::model::CContractor(),
      hacc::model::CValuable()
{
    hacc::model::CContractor::setID(ownerID);
    hacc::model::CValuable::setID(valuableID);
    HACC_INIT_ITEM;
}

WExpandedTransactionThingSellItem::~WExpandedTransactionThingSellItem()
{
}

void WExpandedTransactionThingSellItem::setTransactionData(const hacc::TMoney &buyMoney, const hacc::TMoney &sellMoney)
{
    setText(HACC_TTI_BUY_MONEY_PLACE ,  tools::convert::moneyToString(buyMoney));
    setText(HACC_TTI_SELL_MONEY_PLACE,  tools::convert::moneyToString(sellMoney));
}

void WExpandedTransactionThingSellItem::setOwnerData(const hacc::TDBID &iconID, const QString &name)
{
    setIcon(HACC_TTI_OWNER_PLACE, iconID);
    setText(HACC_TTI_OWNER_PLACE, name);
}

void WExpandedTransactionThingSellItem::setValuableData(const QString &serial)
{
    setText(HACC_TTI_SERIAL_PLACE, serial);
}

void WExpandedTransactionThingSellItem::assignActions()
{
    controlLabel(HACC_TTI_SELL_MONEY_PLACE)->addAction(hacc::model::CTransaction::editAction());
    controlLabel(HACC_TTI_SELL_MONEY_PLACE)->addAction(hacc::model::CTransaction::removeAction());
    controlLabel(HACC_TTI_SELL_MONEY_PLACE)->addAction(hacc::model::CTransaction::tagsEditAction());

    controlLabel(HACC_TTI_OWNER_PLACE)->addAction(hacc::model::CContractor::editAction());
    controlLabel(HACC_TTI_OWNER_PLACE)->addAction(hacc::model::CContractor::tagsEditAction());

    controlLabel(HACC_TTI_SERIAL_PLACE)->addAction(hacc::model::CValuable::editAction());
    controlLabel(HACC_TTI_SERIAL_PLACE)->addAction(hacc::model::CValuable::tagsEditAction());
}

void WExpandedTransactionThingSellItem::transactionUpdated()
{
    //! \todo Добавить валюту в сумму
    //! \todo Реализовать апдейт
//    QSqlQuery q = HACC_DB->query("select "
//                          /* 0*/ "transactions.money, "
//                          /* 1*/ "transactions_things.amount, "
//                          /* 2*/ "things.name, "
//                          /* 3*/ "things.icon_id, "
//                          /* 4*/ "thing_enumerated_types.precision, "
//                          /* 5*/ "thing_enumerated_types.name, "
//                          /* 6*/ "manufacturers.name, "
//                          /* 7*/ "manufacturers.icon_id "
//                                 "from transactions "
//                                 "left join transactions_things on transactions_things.id=transactions.id "
//                                 "left join things on things.id=transactions_things.thing_id "
//                                 "left join thing_enumerated_types on thing_enumerated_types.id=things.enumerated_type_id "
//                                 "left join manufacturers on manufacturers.id=things.manufacturer_id "
//                                 "where transactions.id=?",
//                                 QVariantList() << hacc::model::CTransaction::id());
//    if(q.next())
//    {
//        setTransactionData (HACC_DB_2_MONY(q, 0),
//                            HACC_DB_2_AMNT(q, 1),
//                            HACC_DB_2_PREC(q, 4),
//                            HACC_DB_2_STRG(q, 5));
//        setThingData       (HACC_DB_2_STRG(q, 2),
//                            HACC_DB_2_DBID(q, 3));
//        setManufacturerData(HACC_DB_2_STRG(q, 6),
//                            HACC_DB_2_DBID(q, 7));
//    }
}

void WExpandedTransactionThingSellItem::contractorUpdated()
{

}

void WExpandedTransactionThingSellItem::valuableUpdated()
{

}

}
}
}
