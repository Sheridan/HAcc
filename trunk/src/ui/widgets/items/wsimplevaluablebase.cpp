#include "wsimplevaluablebase.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleValuableBase::WSimpleValuableBase(QWidget *parent) : ui::item::base::WBase(parent)
{}

WSimpleValuableBase::~WSimpleValuableBase()
{}

void WSimpleValuableBase::constructControls(QToolBar *tb)
{
//    tb->addAction(HACC_THINGS->addAction());
}

ui::item::base::WContainer *WSimpleValuableBase::buidContainer()
{
    return new WSimpleValuableContainer(this);
}

void WSimpleValuableBase::constructHeader(base::WHeader *header)
{
    header->setLabels(3,1,QStringList() << tr("Thing name") << tr("Manufacturer name") << tr("Serial"));
}

}
}
}
