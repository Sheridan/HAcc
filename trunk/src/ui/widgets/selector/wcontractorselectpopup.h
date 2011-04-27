/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WCONTRACTORSELECTPOPUP_H
#define WCONTRACTORSELECTPOPUP_H

#include "wselectorpopup.h"
#include "hacc_types.h"
#include "ccontractors.h"

namespace ui
{
namespace selector
{

class WContractorSelectPopup : public base::WSelectorPopup
{
    Q_OBJECT
public:
    WContractorSelectPopup(const hacc::model::EContractorFilter &filter, QWidget *parent = 0);
    ~WContractorSelectPopup();

private:
    ui::item::base::WBase *createContainer();
    hacc::model::EContractorFilter m_filter;
};

}
}
#endif // WCONTRACTORSELECTPOPUP_H
