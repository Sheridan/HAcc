#include "wexpandedvaluablebase.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

WExpandedValuableBase::WExpandedValuableBase(QWidget *parent) : ui::item::base::WBase(parent)
{}

WExpandedValuableBase::~WExpandedValuableBase()
{}

void WExpandedValuableBase::constructControls(QToolBar *tb)
{
//    tb->addAction(HACC_THINGS->addAction());
//    tb->addSeparator();
//    tb->addAction(HACC_ENUMERATED_THING_TYPES->addAction());
}

base::WContainer *WExpandedValuableBase::buidContainer()
{
    return new WExpandedValuableContainer(this);
}

void WExpandedValuableBase::constructHeader(base::WHeader *header)
{
    header->setLabels(5,1,QStringList()
                      << tr("Thing name")
                      << tr("Manufacturer name")
                      << tr("Cost")
                      << tr("Purchase date")
                      << tr("Serial"));
}

}
}
}
