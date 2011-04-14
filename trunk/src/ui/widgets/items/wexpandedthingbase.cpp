#include "wexpandedthingbase.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

WExpandedThingBase::WExpandedThingBase(QWidget *parent) : ui::item::base::WBase(parent)
{}

WExpandedThingBase::~WExpandedThingBase()
{}

void WExpandedThingBase::constructControls(QToolBar *tb)
{
    tb->addAction(HACC_THINGS->addAction());
    tb->addSeparator();
    tb->addAction(HACC_ENUMERATED_THING_TYPES->addAction());
}

base::WContainer *WExpandedThingBase::buidContainer()
{
    return new WExpandedThingContainer(this);
}

void WExpandedThingBase::constructHeader(base::WHeader *header)
{
    header->setLabels(2,1,QStringList() << tr("Thing name") << tr("Manufacturer name"));
}

}
}
}
