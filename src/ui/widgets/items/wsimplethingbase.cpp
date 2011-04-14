#include "wsimplethingbase.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleThingBase::WSimpleThingBase(QWidget *parent) : ui::item::base::WBase(parent)
{}

WSimpleThingBase::~WSimpleThingBase()
{}

void WSimpleThingBase::constructControls(QToolBar *tb)
{
    tb->addAction(HACC_THINGS->addAction());
}

ui::item::base::WContainer *WSimpleThingBase::buidContainer()
{
    return new WSimpleThingContainer(this);
}

void WSimpleThingBase::constructHeader(base::WHeader *header)
{
    header->setLabels(2,1,QStringList() << tr("Thing name") << tr("Manufacturer name"));
}

}
}
}
