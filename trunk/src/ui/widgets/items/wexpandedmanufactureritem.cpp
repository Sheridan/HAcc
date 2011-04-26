#include "wexpandedmanufactureritem.h"
#include "images.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

WExpandedManufacturerItem::WExpandedManufacturerItem(const hacc::TDBID &id)
    : ui::item::base::WItem(1, 1, true),
      hacc::model::CManufacturer()
{
    setID(id);
    HACC_INIT_ITEM;
}

WExpandedManufacturerItem::~WExpandedManufacturerItem()
{}

void WExpandedManufacturerItem::setManufacturerData(const hacc::TDBID &manufacturerIconID, const QString &manufacturerName)
{
    setIcon(0, 0, manufacturerIconID);
    setText(0, 0, manufacturerName);
}

void WExpandedManufacturerItem::setMoreData(const QString &description, const QVariant &logo)
{
    setDescription(description);
    setImage(tools::images::byteArray2Pixmap(logo.toByteArray()));
}


void WExpandedManufacturerItem::buildExpanderUIEvent()
{
    appendDescriptionTab();
    appendTagsTab < ui::tag::TTagContainer <hacc::model::CManufacturer, hacc::model::CManufacturers> >();

    QSqlQuery q = HACC_DB->query("select description, image from manufacturers where id=?", QVariantList() << itemID());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setMoreData(HACC_DB_2_STRG(q, 0), q.value(1));
    }
}

void WExpandedManufacturerItem::assignActions()
{
    controlLabel(0, 0)->addAction(hacc::model::CManufacturer::editAction());
    if(itemID() > 1) { controlLabel(0, 0)->addAction(hacc::model::CManufacturer::removeAction()); }
    controlLabel(0, 0)->addAction(hacc::model::CManufacturer::tagsEditAction());
}

void WExpandedManufacturerItem::manufacturerUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id, description, image from manufacturers where id=?",
                                 QVariantList() << itemID());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setManufacturerData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
        if(expanded())
        {
            setMoreData(HACC_DB_2_STRG(q, 2), q.value(3));
        }
        updateGeometry();
    }
}

hacc::TDBID WExpandedManufacturerItem::itemID()
{
    return hacc::model::CManufacturer::id();
}

}
}
}
