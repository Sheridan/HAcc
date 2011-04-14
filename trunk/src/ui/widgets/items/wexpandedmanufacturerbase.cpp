#include "wexpandedmanufacturerbase.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

WExpandedManufacturerBase::WExpandedManufacturerBase(QWidget *parent) : ui::item::base::WBase(parent)
{}

WExpandedManufacturerBase::~WExpandedManufacturerBase()
{}

void WExpandedManufacturerBase::constructControls(QToolBar *tb)
{
    tb->addAction(HACC_MANUFACTURERS->addAction());
}

ui::item::base::WContainer *WExpandedManufacturerBase::buidContainer()
{
    return new WExpandedManufacturerContainer(this);
}

void WExpandedManufacturerBase::constructHeader(base::WHeader *header)
{
    header->setLabels(1,1,QStringList() << tr("Name"));
}

}
}
}
