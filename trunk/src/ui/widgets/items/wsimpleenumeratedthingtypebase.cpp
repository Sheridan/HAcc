#include "wsimpleenumeratedthingtypebase.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleEnumeratedThingTypeBase::WSimpleEnumeratedThingTypeBase(QWidget *parent) : ui::item::base::WBase(parent)
{}

WSimpleEnumeratedThingTypeBase::~WSimpleEnumeratedThingTypeBase()
{}

void WSimpleEnumeratedThingTypeBase::constructControls(QToolBar *tb)
{
    tb->addAction(HACC_ENUMERATED_THING_TYPES->addAction());
}

ui::item::base::WContainer *WSimpleEnumeratedThingTypeBase::buidContainer()
{
    return new WSimpleEnumeratedThingTypeContainer(this);
}

void WSimpleEnumeratedThingTypeBase::constructHeader(base::WHeader *header)
{
    header->setLabels(2,1,QStringList() << tr("Name") << tr("Precision"));
}

}
}
}
