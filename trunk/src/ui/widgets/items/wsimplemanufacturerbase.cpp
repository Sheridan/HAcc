#include "wsimplemanufacturerbase.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleManufacturerBase::WSimpleManufacturerBase(QWidget *parent) : ui::item::base::WBase(parent)
{}

WSimpleManufacturerBase::~WSimpleManufacturerBase()
{}

void WSimpleManufacturerBase::constructControls(QToolBar *tb)
{
    tb->addAction(HACC_MANUFACTURERS->addAction());
}

ui::item::base::WContainer *WSimpleManufacturerBase::buidContainer()
{
    return new WSimpleManufacturerContainer(this);
}

void WSimpleManufacturerBase::constructHeader(base::WHeader *header)
{
    header->setLabels(1,1,QStringList() << tr("Name"));
}

}
}
}
