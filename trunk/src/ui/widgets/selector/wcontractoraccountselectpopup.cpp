#include "wcontractoraccountselectpopup.h"
#include "wsimplecontractoraccountbase.h"

namespace ui
{
namespace selector
{

WContractorAccountSelectPopup::WContractorAccountSelectPopup(const hacc::model::EContractorFilter &filter, QWidget *parent)
    : base::WSelectorPopup(parent)
{
    m_filter = filter;
    m_currencyID = 0;
    m_ccOntainer = NULL;
}

WContractorAccountSelectPopup::~WContractorAccountSelectPopup()
{}

void WContractorAccountSelectPopup::setCurrencyFilter(const hacc::TDBID &currencyID)
{
    m_currencyID = currencyID;
    if(m_ccOntainer)
    {
        static_cast<ui::item::simple::WSimpleContractorAccountBase *>(m_ccOntainer)->setCurrencyFilter(m_currencyID);
    }
}

ui::item::base::WBase *WContractorAccountSelectPopup::createContainer()
{
    m_ccOntainer = new ui::item::simple::WSimpleContractorAccountBase(m_filter, this);
    static_cast<ui::item::simple::WSimpleContractorAccountBase *>(m_ccOntainer)->setCurrencyFilter(m_currencyID);
    return m_ccOntainer;
}

}
}
