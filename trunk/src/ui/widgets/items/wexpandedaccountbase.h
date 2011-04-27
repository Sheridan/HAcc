/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WACCOUNTBASE_He
#define WACCOUNTBASE_He

#include "wbase.h"
#include "hacc_types.h"
#include "ccontractor.h"
#include "wexpandedaccountcontainer.h"

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedAccountBase : public ui::item::base::WBase, public hacc::model::CContractor
{
public:
    WExpandedAccountBase(const hacc::TDBID &parentContractor, QWidget *parent = 0);
    ~WExpandedAccountBase();

private:
    void constructControls(QToolBar *tb);
    base::WContainer *buidContainer();
    void constructHeader(base::WHeader *header);
};

}
}
}
#endif // WACCOUNTBASE_He
