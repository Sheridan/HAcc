#include "wsimplecontractorbase.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleContractorBase::WSimpleContractorBase(hacc::model::EContractorFilter filter, QWidget *parent)
    : ui::item::base::WBase(parent)
{
    m_filter = filter;
}

WSimpleContractorBase::~WSimpleContractorBase()
{}

void WSimpleContractorBase::constructControls(QToolBar *tb)
{
    switch(m_filter)
    {
        case hacc::model::ctSelf: tb->addAction(HACC_CONTRACTORS->addSelfAction()); break;
        case hacc::model::ctOther: tb->addAction(HACC_CONTRACTORS->addAction()); break;
        case hacc::model::ctAll:
        {
            tb->addAction(HACC_CONTRACTORS->addAction());
            tb->addAction(HACC_CONTRACTORS->addSelfAction());
        }
        break;
    }
}

ui::item::base::WContainer *WSimpleContractorBase::buidContainer()
{
    return new WSimpleContractorContainer(m_filter, this);
}

void WSimpleContractorBase::constructHeader(base::WHeader *header)
{
    header->setLabels(1, 1,QStringList() << tr("Contractor"));
}

}
}
}
