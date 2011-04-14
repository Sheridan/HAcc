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
}

WContractorAccountSelectPopup::~WContractorAccountSelectPopup()
{}

ui::item::base::WBase *WContractorAccountSelectPopup::createContainer()
{
    return new ui::item::simple::WSimpleContractorAccountBase(m_filter, this);
}

}
}
