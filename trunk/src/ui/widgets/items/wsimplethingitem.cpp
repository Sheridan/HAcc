#include "wsimplethingitem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleThingItem::WSimpleThingItem(const hacc::TDBID &thingID, const hacc::TDBID &manufacturerID)
    : ui::item::base::WItem(2, 1),
      hacc::model::CThing(),
      hacc::model::CManufacturer()
{
    hacc::model::CThing::setID(thingID);
    hacc::model::CManufacturer::setID(manufacturerID);
    HACC_INIT_ITEM;
}

WSimpleThingItem::~WSimpleThingItem()
{}

void WSimpleThingItem::setThingData(const hacc::TDBID &iconID, const QString &name)
{
    setIcon(0, 0, iconID);
    setText(0, 0, name);
}

void WSimpleThingItem::setManufacturerData(const hacc::TDBID &iconID, const QString &name)
{
    setIcon(1, 0, iconID);
    setText(1, 0, name);
}

void WSimpleThingItem::thingUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from things where id=?",
                                 QVariantList() << hacc::model::CThing::id());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setThingData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

void WSimpleThingItem::manufacturerUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from manufacturers where id=?",
                                 QVariantList() << hacc::model::CManufacturer::id());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setManufacturerData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

hacc::TDBID WSimpleThingItem::itemID()
{
    return hacc::model::CThing::id();
}

void WSimpleThingItem::assignActions()
{
    controlLabel(0, 0)->addAction(hacc::model::CThing::editAction());
    controlLabel(1, 0)->addAction(hacc::model::CManufacturer::editAction());
}

}
}
}
