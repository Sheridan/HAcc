#ifndef WCONTRACTORACCOUNTSELECTPOPUP_H
#define WCONTRACTORACCOUNTSELECTPOPUP_H

#include "wselectorpopup.h"
#include "hacc_types.h"
#include "ccontractors.h"

namespace ui
{
namespace selector
{

class WContractorAccountSelectPopup : public base::WSelectorPopup
{
    Q_OBJECT
public:
    explicit WContractorAccountSelectPopup(const hacc::model::EContractorFilter &filter, QWidget *parent = 0);
    ~WContractorAccountSelectPopup();

private:
    ui::item::base::WBase *createContainer();
    hacc::model::EContractorFilter m_filter;
};

}
}
#endif // WCONTRACTORACCOUNTSELECTPOPUP_H
