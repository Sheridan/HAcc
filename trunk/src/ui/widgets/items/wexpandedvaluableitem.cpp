#include "wexpandedvaluableitem.h"
#include "images.h"
#include "convert.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

WExpandedValuableItem::WExpandedValuableItem(const hacc::TDBID &valID, const hacc::TDBID &thingID,
                                             const hacc::TDBID &manufacturerID, const hacc::TDBID &transactionID) :
        ui::item::base::WItem(5, 1, true),
        hacc::model::CValuable(),
        hacc::model::CThing(),
        hacc::model::CManufacturer(),
        hacc::model::CTransaction()
{
    hacc::model::CValuable::setID(valID);
    hacc::model::CThing::setID(thingID);
    hacc::model::CManufacturer::setID(manufacturerID);
    hacc::model::CTransaction::setID(transactionID);
    HACC_INIT_ITEM;
}

WExpandedValuableItem::~WExpandedValuableItem()
{
}

void WExpandedValuableItem::setThingData(const hacc::TDBID &iconID, const QString &name)
{
    setIcon(0, 0, iconID);
    setText(0, 0, name);
}

void WExpandedValuableItem::setManufacturerData(const hacc::TDBID &iconID, const QString &name)
{
    setIcon(1, 0, iconID);
    setText(1, 0, name);
}

void WExpandedValuableItem::setTransactionData(const hacc::TMoney &cost, const QDateTime &purchaseDate)
{
    //! \todo Добавить валюту в сумму
    setText(2, 0, tools::convert::moneyToString(cost));
    setText(3, 0, tools::convert::datetimeToDateString(purchaseDate));
}

void WExpandedValuableItem::setValuableData(const QString &serial)
{
    if(HACC_VALUABLES->tagAttached(HACC_TAG_ID_WRITE_OFF, itemID()))
    {
        setIcon(4, 0, HACC_ICONS->icon(HACC_TAG_ID_WRITE_OFF));
    }
    setText(4, 0, serial);
}

void WExpandedValuableItem::setMoreData(const QString &description, const QVariant &image)
{
    setDescription(description);
    setImage(tools::images::byteArray2Pixmap(image.toByteArray()));
}

void WExpandedValuableItem::buildExpanderUIEvent()
{
    appendDescriptionTab();
    appendTagsTab < ui::tag::TTagContainer <hacc::model::CValuable, hacc::model::CValuables> >();

    QSqlQuery q = HACC_DB->query("select description, image from valuables where id=?",
                                 QVariantList() << hacc::model::CValuable::id());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setMoreData(HACC_DB_2_STRG(q, 0), q.value(1));
    }
}

void WExpandedValuableItem::assignActions()
{
    controlLabel(0, 0)->addAction(hacc::model::CThing::editAction());
    if(hacc::model::CThing::id() > 1) { controlLabel(0, 0)->addAction(hacc::model::CThing::removeAction()); }
    controlLabel(0, 0)->addAction(hacc::model::CThing::tagsEditAction());
    controlLabel(1, 0)->addAction(hacc::model::CManufacturer::editAction());
    if(hacc::model::CManufacturer::id() > 1) { controlLabel(1, 0)->addAction(hacc::model::CManufacturer::removeAction()); }
    controlLabel(1, 0)->addAction(hacc::model::CManufacturer::tagsEditAction());
    controlLabel(4, 0)->addAction(hacc::model::CValuable::tagsEditAction());
}

void WExpandedValuableItem::thingUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from things where id=?",
                                 QVariantList() << hacc::model::CThing::id());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setThingData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

void WExpandedValuableItem::manufacturerUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from manufacturers where id=?",
                                 QVariantList() << hacc::model::CManufacturer::id());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setManufacturerData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

hacc::TDBID WExpandedValuableItem::itemID()
{
    return hacc::model::CValuable::id();
}

}
}
}
