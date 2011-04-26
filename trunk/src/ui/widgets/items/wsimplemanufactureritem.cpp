#include "wsimplemanufactureritem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleManufacturerItem::WSimpleManufacturerItem(const hacc::TDBID &id)
    : ui::item::base::WItem(1, 1),
      hacc::model::CManufacturer()
{
    setID(id);
    HACC_INIT_ITEM;
}

WSimpleManufacturerItem::~WSimpleManufacturerItem()
{}

void WSimpleManufacturerItem::setItemData(const hacc::TDBID &manufacturerIconID, const QString &manufacturerName)
{
    setIcon(0, 0, manufacturerIconID);
    setText(0, 0, manufacturerName);
}

void WSimpleManufacturerItem::manufacturerUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from manufacturers where id=?",
                                 QVariantList() << itemID());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setItemData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

hacc::TDBID WSimpleManufacturerItem::itemID()
{
    return hacc::model::CManufacturer::id();
}

void WSimpleManufacturerItem::assignActions()
{
    controlLabel(0, 0)->addAction(hacc::model::CManufacturer::editAction());
}

}
}
}
