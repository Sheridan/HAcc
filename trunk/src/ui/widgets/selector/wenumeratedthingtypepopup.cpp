#include "wenumeratedthingtypepopup.h"

namespace ui
{
namespace selector
{

WEnumeratedThingTypePopup::WEnumeratedThingTypePopup(QWidget *parent) : base::WSelectorPopup(parent)
{}

WEnumeratedThingTypePopup::~WEnumeratedThingTypePopup()
{}

ui::item::base::WBase *WEnumeratedThingTypePopup::createContainer()
{
    return new ui::item::simple::WSimpleEnumeratedThingTypeBase(this);
}

}
}
