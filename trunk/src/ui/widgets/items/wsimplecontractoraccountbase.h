/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WCONTRACTORACCOUNTBASE_Hs
#define WCONTRACTORACCOUNTBASE_Hs

#include "wbase.h"
#include "wsimplecontractoraccountcontainer.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleContractorAccountBase : public ui::item::base::WBase
{
    Q_OBJECT
public:
    explicit WSimpleContractorAccountBase(hacc::model::EContractorFilter filter, QWidget *parent = 0);
    ~WSimpleContractorAccountBase();
    void setCurrencyFilter(const hacc::TDBID &currencyID);

private:
    void constructControls(QToolBar *tb);
    hacc::model::EContractorFilter m_filter;
    hacc::TDBID m_currencyID;
    ui::item::base::WContainer *m_wContainer;
    ui::item::base::WContainer *buidContainer();
    void constructHeader(base::WHeader *header);

};

}
}
}
#endif // WCONTRACTORACCOUNTBASE_Hs
