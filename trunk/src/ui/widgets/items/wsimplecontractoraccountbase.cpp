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
    m_currencyID = 0;
    m_wContainer = NULL;
}

WSimpleContractorAccountBase::~WSimpleContractorAccountBase()
{

}

void WSimpleContractorAccountBase::constructControls(QToolBar *tb)
{
    switch(m_filter)
    {
        case hacc::model::ctSelf:  tb->addAction(HACC_CONTRACTORS->addSelfAction()); break;
        case hacc::model::ctOther: tb->addAction(HACC_CONTRACTORS->addAction()); break;
        case hacc::model::ctAll:
        {
            tb->addAction(HACC_CONTRACTORS->addAction());
            tb->addAction(HACC_CONTRACTORS->addSelfAction());
        }
        break;
    }
}

void WSimpleContractorAccountBase::setCurrencyFilter(const hacc::TDBID &currencyID)
{
    m_currencyID = currencyID;
    if(m_wContainer)
    {
        static_cast<WSimpleContractorAccountContainer *>(m_wContainer)->setCurrencyFilter(m_currencyID);
    }
}

ui::item::base::WContainer *WSimpleContractorAccountBase::buidContainer()
{
    m_wContainer = new WSimpleContractorAccountContainer(m_filter, this);
    static_cast<WSimpleContractorAccountContainer *>(m_wContainer)->setCurrencyFilter(m_currencyID);
    return m_wContainer;
}

void WSimpleContractorAccountBase::constructHeader(base::WHeader *header)
{
    header->setLabels(3, 1, QStringList() << tr("Contractor") << tr("Account") << tr("Currency"));
}

}
}
}
