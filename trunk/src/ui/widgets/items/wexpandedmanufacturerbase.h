/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WMANUFACTURERBASE_He
#define WMANUFACTURERBASE_He

#include "wbase.h"
#include "wexpandedmanufacturercontainer.h"

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedManufacturerBase : public ui::item::base::WBase
{
    Q_OBJECT
public:
    explicit WExpandedManufacturerBase(QWidget *parent = 0);
    ~WExpandedManufacturerBase();

private:
    void constructControls(QToolBar *tb);
    ui::item::base::WContainer *buidContainer();
    void constructHeader(base::WHeader *header);
};

}
}
}

#endif // WMANUFACTURERBASE_He
