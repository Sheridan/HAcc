#include "wmanufacturerselectpopup.h"
#include "wsimplemanufacturerbase.h"

namespace ui
{
namespace selector
{

WManufacturerSelectPopup::WManufacturerSelectPopup(QWidget *parent) : base::WSelectorPopup(parent)
{}

WManufacturerSelectPopup::~WManufacturerSelectPopup()
{}

ui::item::base::WBase *WManufacturerSelectPopup::createContainer()
{
    return new ui::item::simple::WSimpleManufacturerBase(this);
}

}
}
