/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
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
    void setCurrencyFilter(const hacc::TDBID &currencyID);

private:
    ui::item::base::WBase *createContainer();
    hacc::model::EContractorFilter m_filter;
    hacc::TDBID m_currencyID;
    ui::item::base::WBase *m_ccOntainer;
};

}
}
#endif // WCONTRACTORACCOUNTSELECTPOPUP_H
