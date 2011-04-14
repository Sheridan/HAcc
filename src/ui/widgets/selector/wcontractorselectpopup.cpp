#include "wcontractorselectpopup.h"
#include "wsimplecontractorbase.h"

namespace ui
{
namespace selector
{

WContractorSelectPopup::WContractorSelectPopup(const hacc::model::EContractorFilter &filter, QWidget *parent)
    : base::WSelectorPopup(parent)
{
    m_filter = filter;
}

WContractorSelectPopup::~WContractorSelectPopup()
{}

ui::item::base::WBase *WContractorSelectPopup::createContainer()
{
    return new ui::item::simple::WSimpleContractorBase(m_filter, this);
}

}
}
