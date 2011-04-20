#include "wexpandedthingitem.h"
#include "images.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

WExpandedThingItem::WExpandedThingItem(const hacc::TDBID &thingID, const hacc::TDBID &manufacturerID) :
        ui::item::base::WItem(2, 1, true),
        hacc::model::CThing(),
        hacc::model::CManufacturer()
{
    hacc::model::CThing::setID(thingID);
    hacc::model::CManufacturer::setID(manufacturerID);
    HACC_INIT_ITEM;
}

WExpandedThingItem::~WExpandedThingItem()
{
}

void WExpandedThingItem::setThingData(const hacc::TDBID &iconID, const QString &name)
{
    setIcon(0, 0, iconID);
    setText(0, 0, name);
}

void WExpandedThingItem::setManufacturerData(const hacc::TDBID &iconID, const QString &name)
{
    setIcon(1, 0, iconID);
    setText(1, 0, name);
}

void WExpandedThingItem::setMoreData(const QString &description, const QVariant &image)
{
    setDescription(description);
    setImage(ui::images::byteArray2Pixmap(image.toByteArray()));
}

void WExpandedThingItem::buildExpanderUIEvent()
{
    appendDescriptionTab();
    appendTagsTab < ui::tag::TTagContainer <hacc::model::CThing, hacc::model::CThings> >();


    QSqlQuery q = HACC_DB->query("select description, image from things where id=?",
                                 QVariantList() << hacc::model::CThing::id());
    if(q.next())
    {
        setMoreData(HACC_DB_2_STRG(q, 0), q.value(1));
    }
}

void WExpandedThingItem::assignActions()
{
    controlLabel(0, 0)->addAction(hacc::model::CThing::editAction());
    if(hacc::model::CThing::id() > 1) { controlLabel(0, 0)->addAction(hacc::model::CThing::removeAction()); }
    controlLabel(0, 0)->addAction(hacc::model::CThing::tagsEditAction());
    controlLabel(1, 0)->addAction(hacc::model::CManufacturer::editAction());
    if(hacc::model::CManufacturer::id() > 1) { controlLabel(1, 0)->addAction(hacc::model::CManufacturer::removeAction()); }
    controlLabel(1, 0)->addAction(hacc::model::CManufacturer::tagsEditAction());
}

void WExpandedThingItem::thingUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id, description, image from things where id=?",
                                 QVariantList() << hacc::model::CThing::id());
    if(q.next())
    {
        setThingData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
        if(expanded())
        {
            setMoreData(HACC_DB_2_STRG(q, 2), q.value(3));
        }
        updateGeometry();
    }
}

void WExpandedThingItem::manufacturerUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from manufacturers where id=?",
                                 QVariantList() << hacc::model::CManufacturer::id());
    if(q.next())
    {
        setManufacturerData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

hacc::TDBID WExpandedThingItem::itemID()
{
    return hacc::model::CThing::id();
}

}
}
}
