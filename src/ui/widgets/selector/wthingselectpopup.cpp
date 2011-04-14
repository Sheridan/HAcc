#include "wthingselectpopup.h"
#include "wsimplethingbase.h"
namespace ui
{
namespace selector
{

WThingSelectPopup::WThingSelectPopup(QWidget *parent) : base::WSelectorPopup(parent)
{}

WThingSelectPopup::~WThingSelectPopup()
{}

ui::item::base::WBase *WThingSelectPopup::createContainer()
{
    return new ui::item::simple::WSimpleThingBase(this);
}

}
}
