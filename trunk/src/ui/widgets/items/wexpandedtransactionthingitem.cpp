#include "wexpandedtransactionthingitem.h"
#include "convert.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

#define HACC_TTI_THING_PLACE 0, 0
#define HACC_TTI_MANUF_PLACE 1, 0

WExpandedTransactionThingItem::WExpandedTransactionThingItem(const int &columns, const hacc::TDBID &transactionID, const hacc::TDBID &thingID, const hacc::TDBID &manufactiurerID)
    : ui::item::base::WItem(columns, 1, true),
      hacc::model::CTransaction(),
      hacc::model::CThing(),
      hacc::model::CManufacturer()
{
    hacc::model::CTransaction ::setID(transactionID);
    hacc::model::CThing       ::setID(thingID);
    hacc::model::CManufacturer::setID(manufactiurerID);
//    HACC_INIT_ITEM;
}

WExpandedTransactionThingItem::~WExpandedTransactionThingItem()
{
}

void WExpandedTransactionThingItem::setThingData(const QString &thingName, const hacc::TDBID &thingIconID)
{
    setIcon(HACC_TTI_THING_PLACE, thingIconID);
    setText(HACC_TTI_THING_PLACE, thingName);
}

void WExpandedTransactionThingItem::setManufacturerData(const QString &manufactiurerName, const hacc::TDBID &manufactiurerIconID)
{
    setIcon(HACC_TTI_MANUF_PLACE, manufactiurerIconID);
    setText(HACC_TTI_MANUF_PLACE, manufactiurerName);
}

void WExpandedTransactionThingItem::buildExpanderUIEvent()
{
    appendTagsTab < ui::tag::TTagContainer <hacc::model::CTransaction, hacc::model::CTransactions> >();
}

void WExpandedTransactionThingItem::assignActions()
{
    controlLabel(HACC_TTI_THING_PLACE)->addAction(hacc::model::CThing::editAction());
    if(hacc::model::CThing::id() > 1) { controlLabel(HACC_TTI_THING_PLACE)->addAction(hacc::model::CThing::removeAction()); }
    controlLabel(HACC_TTI_THING_PLACE)->addAction(hacc::model::CThing::tagsEditAction());

    controlLabel(HACC_TTI_MANUF_PLACE)->addAction(hacc::model::CManufacturer::editAction());
    if(hacc::model::CManufacturer::id() > 1) { controlLabel(HACC_TTI_MANUF_PLACE)->addAction(hacc::model::CManufacturer::removeAction()); }
    controlLabel(HACC_TTI_MANUF_PLACE)->addAction(hacc::model::CManufacturer::tagsEditAction());
}

void WExpandedTransactionThingItem::thingUpdated()
{
    QSqlQuery q = HACC_DB->query("select "
                                 "things.name, "
                                 "things.icon_id "
                                 "from things "
                                 "where things.id=?",
                                 QVariantList() << hacc::model::CThing::id());
    if(q.next())
    {
        setThingData(HACC_DB_2_STRG(q, 0),
                     HACC_DB_2_DBID(q, 1));
    }
}

void WExpandedTransactionThingItem::manufacturerUpdated()
{
    QSqlQuery q = HACC_DB->query("select "
                                 "manufacturers.name, "
                                 "manufacturers.icon_id "
                                 "from manufacturers "
                                 "where manufacturers.id=?",
                                 QVariantList() << hacc::model::CManufacturer::id());
    if(q.next())
    {
        setManufacturerData(HACC_DB_2_STRG(q, 0),
                            HACC_DB_2_DBID(q, 1));
    }
}

hacc::TDBID WExpandedTransactionThingItem::itemID()
{
    return hacc::model::CTransaction::id();
}

}
}
}
