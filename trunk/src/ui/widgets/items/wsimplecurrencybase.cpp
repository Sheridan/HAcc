#include "wsimplecurrencybase.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleCurrencyBase::WSimpleCurrencyBase(QWidget *parent) : ui::item::base::WBase(parent)
{}

WSimpleCurrencyBase::~WSimpleCurrencyBase()
{}

void WSimpleCurrencyBase::constructControls(QToolBar *tb)
{
    tb->addAction(HACC_CURRENCYES->addAction());
}

ui::item::base::WContainer *WSimpleCurrencyBase::buidContainer()
{
    return new WSimpleCurrencyContainer(this);
}

void WSimpleCurrencyBase::constructHeader(base::WHeader *header)
{
    header->setLabels(2, 1, QStringList() << tr("Name") << tr("Reduction"));
}

}
}
}
