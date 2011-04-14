#include "wsimplemovementbase.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleMovementBase::WSimpleMovementBase(QWidget *parent)
    : ui::item::base::WBase(parent)
{
}

WSimpleMovementBase::~WSimpleMovementBase()
{}

void WSimpleMovementBase::constructControls(QToolBar *tb)
{

}

ui::item::base::WContainer *WSimpleMovementBase::buidContainer()
{
    return new WSimpleMovementContainer(this);
}

void WSimpleMovementBase::constructHeader(base::WHeader *header)
{
    header->setLabels(5, 1,QStringList()
                      << tr("Date and time")
                      << tr("Source contractor")
                      << tr("Destination contractor")
                      << tr("Manufacturer")
                      << tr("Thing")
                      );
}

}
}
}
