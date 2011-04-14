#include "wsimpletagbase.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleTagBase::WSimpleTagBase(QWidget *parent) : ui::item::base::WBase(parent)
{}

WSimpleTagBase::~WSimpleTagBase()
{}

void WSimpleTagBase::constructControls(QToolBar *tb)
{
    tb->addAction(HACC_TAGS->addAction());
}

ui::item::base::WContainer *WSimpleTagBase::buidContainer()
{
    return new WSimpleTagContainer(this);
}

void WSimpleTagBase::constructHeader(base::WHeader *header)
{
    header->setLabels(1,1,QStringList() << tr("Name"));
}

}
}
}
