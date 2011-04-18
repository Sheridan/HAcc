#include "wcurrencyselectpopup.h"
#include "wsimplecurrencybase.h"

namespace ui
{
namespace selector
{

WCurrencySelectPopup::WCurrencySelectPopup(QWidget *parent)
    : base::WSelectorPopup(parent)
{}

WCurrencySelectPopup::~WCurrencySelectPopup()
{}

ui::item::base::WBase *WCurrencySelectPopup::createContainer()
{
    return new ui::item::simple::WSimpleCurrencyBase(this);
}

}
}
