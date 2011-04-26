#include "wsimplemovementitem.h"
#include "convert.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

#define HACC_MI_MOV_DATE_PLACE 0, 0
#define HACC_MI_SRC_CTR_PLACE  1, 0
#define HACC_MI_DST_CTR_PLACE  2, 0
#define HACC_MI_MANUF_PLACE    3, 0
#define HACC_MI_THING_PLACE    4, 0

WSimpleMovementItem::WSimpleMovementItem(const hacc::TDBID &movementID,
                                         const hacc::TDBID &sourceContractorID, const hacc::TDBID &destinationContractorID,
                                         const hacc::TDBID &manufacturerID, const hacc::TDBID &thingID)
    : base::WItem(5, 1),
      hacc::model::CMovement(),
      hacc::model::composite::CContractorSource(),
      hacc::model::composite::CContractorDestination(),
      hacc::model::CManufacturer(),
      hacc::model::CThing()
{
    hacc::model::CMovement::setID(movementID);
    setSourceContractorID(sourceContractorID);
    setDestinationContractorID(destinationContractorID);
    hacc::model::CManufacturer::setID(manufacturerID);
    hacc::model::CThing::setID(thingID);
    HACC_INIT_ITEM;
}

WSimpleMovementItem::~WSimpleMovementItem()
{}

void WSimpleMovementItem::setMovementData(const QDateTime &datetime)
{
    if(HACC_MOVEMENTS->tagAttached(HACC_TAG_ID_BUYING, itemID()))
    {
        setIcon(HACC_MI_MOV_DATE_PLACE, HACC_ICONS->icon(tools::icons::iMovement, tools::icons::oIncoming));
    }
    else if(HACC_MOVEMENTS->tagAttached(HACC_TAG_ID_WRITE_OFF, itemID()))
    {
        setIcon(HACC_MI_MOV_DATE_PLACE, HACC_ICONS->icon(tools::icons::iMovement, tools::icons::oWriteOff));
    }
    else if(HACC_MOVEMENTS->tagAttached(HACC_TAG_ID_SELLING, itemID()))
    {
        setIcon(HACC_MI_MOV_DATE_PLACE, HACC_ICONS->icon(tools::icons::iMovement, tools::icons::oOutgoing));
    }
    else
    {
        setIcon(HACC_MI_MOV_DATE_PLACE, HACC_ICONS->icon(tools::icons::iMovement));
    }
    setText(HACC_MI_MOV_DATE_PLACE, tools::convert::datetimeToString(datetime));
}

void WSimpleMovementItem::setSourceContractorData(const hacc::TDBID &iconID, const QString &name)
{
    setIcon(HACC_MI_SRC_CTR_PLACE, iconID);
    setText(HACC_MI_SRC_CTR_PLACE, name);
}
void WSimpleMovementItem::setDestinationContractorData(const hacc::TDBID &iconID, const QString &name)
{
    setIcon(HACC_MI_DST_CTR_PLACE, iconID);
    setText(HACC_MI_DST_CTR_PLACE, name);
}

void WSimpleMovementItem::setManufacturerData(const hacc::TDBID &iconID, const QString &name)
{
    setIcon(HACC_MI_MANUF_PLACE, iconID);
    setText(HACC_MI_MANUF_PLACE, name);
}

void WSimpleMovementItem::setThingData(const hacc::TDBID &iconID, const QString &name)
{
    setIcon(HACC_MI_THING_PLACE, iconID);
    setText(HACC_MI_THING_PLACE, name);
}

void WSimpleMovementItem::assignActions()
{
    controlLabel(HACC_MI_MOV_DATE_PLACE)->addAction(hacc::model::CMovement::tagsEditAction());

    controlLabel(HACC_MI_SRC_CTR_PLACE)->addAction(hacc::model::composite::CContractorSource::editAction());
    controlLabel(HACC_MI_SRC_CTR_PLACE)->addAction(hacc::model::composite::CContractorSource::tagsEditAction());

    controlLabel(HACC_MI_DST_CTR_PLACE)->addAction(hacc::model::composite::CContractorDestination::editAction());
    controlLabel(HACC_MI_DST_CTR_PLACE)->addAction(hacc::model::composite::CContractorDestination::tagsEditAction());

    controlLabel(HACC_MI_MANUF_PLACE)->addAction(hacc::model::CManufacturer::editAction());
    controlLabel(HACC_MI_MANUF_PLACE)->addAction(hacc::model::CManufacturer::tagsEditAction());

    controlLabel(HACC_MI_THING_PLACE)->addAction(hacc::model::CThing::editAction());
    controlLabel(HACC_MI_THING_PLACE)->addAction(hacc::model::CThing::tagsEditAction());
}

void WSimpleMovementItem::thingUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from things where id=?",
                                 QVariantList() << hacc::model::CThing::id());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setThingData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

void WSimpleMovementItem::manufacturerUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from manufacturers where id=?",
                                 QVariantList() << hacc::model::CManufacturer::id());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setManufacturerData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

void WSimpleMovementItem::sourceContractorUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from contractors where id=?",
                                 QVariantList() << sourceContractorID());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setSourceContractorData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

void WSimpleMovementItem::destinationContractorUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from contractors where id=?",
                                 QVariantList() << destinationContractorID());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setDestinationContractorData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

hacc::TDBID WSimpleMovementItem::itemID()
{
    return hacc::model::CMovement::id();
}

}
}
}
