#include "wvaluableselectpopup.h"
#include "wsimplevaluablebase.h"
namespace ui
{
namespace selector
{

WValuableSelectPopup::WValuableSelectPopup(QWidget *parent) : base::WSelectorPopup(parent)
{}

WValuableSelectPopup::~WValuableSelectPopup()
{}

ui::item::base::WBase *WValuableSelectPopup::createContainer()
{
    return new ui::item::simple::WSimpleValuableBase(this);
}

}
}
