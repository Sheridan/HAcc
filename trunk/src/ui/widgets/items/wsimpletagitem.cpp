#include "wsimpletagitem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleTagItem::WSimpleTagItem(const hacc::TDBID &tagID)
    : ui::item::base::WItem(1, 1),
      hacc::model::CTag()
{
    setID(tagID);
    setIcon(0, 0, HACC_ICONS->icon(tools::icons::iTag));
    HACC_INIT_ITEM;
}

WSimpleTagItem::~WSimpleTagItem()
{}

void WSimpleTagItem::setItemData(const QString &name)
{
    setText(0, 0, name);
}

void WSimpleTagItem::assignActions()
{
    controlLabel(0, 0)->addAction(hacc::model::CTag::editAction());
    if(!HACC_TAGS->checkSpetialPurposeTag(id())) // Неизменные теги. Трогать нельзя.
    {
        controlLabel(0, 0)->addAction(hacc::model::CTag::removeAction());
    }
}

void WSimpleTagItem:: tagUpdated()
{
    setItemData(HACC_TAGS->tagName(id()));
}

hacc::TDBID WSimpleTagItem::itemID()
{
    return id();
}

}
}
}
