#include "wsimplecontractoraccountbase.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleContractorAccountBase::WSimpleContractorAccountBase(hacc::model::EContractorFilter filter, QWidget *parent)
    : ui::item::base::WBase(parent)
{
    m_filter = filter;
}

WSimpleContractorAccountBase::~WSimpleContractorAccountBase()
{

}

void WSimpleContractorAccountBase::constructControls(QToolBar *tb)
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

ui::item::base::WContainer *WSimpleContractorAccountBase::buidContainer()
{
    return new WSimpleContractorAccountContainer(m_filter, this);
}

void WSimpleContractorAccountBase::constructHeader(base::WHeader *header)
{
    header->setLabels(2,1,QStringList() << tr("Contractor") << tr("Account"));
}

}
}
}
