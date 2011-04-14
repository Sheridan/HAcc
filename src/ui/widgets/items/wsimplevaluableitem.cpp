#include "wsimplevaluableitem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleValuableItem::WSimpleValuableItem(const hacc::TDBID &thingID, const hacc::TDBID &manufacturerID, const hacc::TDBID &valuableID)
    : ui::item::base::WItem(3, 1),
      hacc::model::CThing(),
      hacc::model::CManufacturer(),
      hacc::model::CValuable()
{
    hacc::model::CThing::setID(thingID);
    hacc::model::CManufacturer::setID(manufacturerID);
    hacc::model::CValuable::setID(valuableID);
    HACC_INIT_ITEM;
}

WSimpleValuableItem::~WSimpleValuableItem()
{}

void WSimpleValuableItem::setThingData(const hacc::TDBID &iconID, const QString &name)
{
    setIcon(0, 0, iconID);
    setText(0, 0, name);
}

void WSimpleValuableItem::setManufacturerData(const hacc::TDBID &iconID, const QString &name)
{
    setIcon(1, 0, iconID);
    setText(1, 0, name);
}

void WSimpleValuableItem::setValuableData(const QString &serial)
{
    if(HACC_VALUABLES->tagAttached(HACC_TAG_ID_WRITE_OFF, itemID()))
    {
        setIcon(2, 0, HACC_ICONS->icon(HACC_TAG_ID_WRITE_OFF));
    }
    setText(2, 0, serial);
}

void WSimpleValuableItem::thingUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from things where id=?",
                                 QVariantList() << hacc::model::CThing::id());
    if(q.next())
    {
        setThingData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

void WSimpleValuableItem::manufacturerUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from manufacturers where id=?",
                                 QVariantList() << hacc::model::CManufacturer::id());
    if(q.next())
    {
        setManufacturerData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

void WSimpleValuableItem::valuableUpdated()
{
    QSqlQuery q = HACC_DB->query("select serial_number from valuables where id=?",
                                 QVariantList() << hacc::model::CValuable::id());
    if(q.next())
    {
        setValuableData(HACC_DB_2_STRG(q, 0));
    }
}

hacc::TDBID WSimpleValuableItem::itemID()
{
    return hacc::model::CValuable::id();
}

void WSimpleValuableItem::assignActions()
{
    controlLabel(0, 0)->addAction(hacc::model::CThing::editAction());
    controlLabel(1, 0)->addAction(hacc::model::CManufacturer::editAction());
    controlLabel(2, 0)->addAction(hacc::model::CValuable::editAction());
}

}
}
}
