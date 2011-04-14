#ifndef WMANUFACTURERBASE_Hs
#define WMANUFACTURERBASE_Hs

#include "wbase.h"
#include "wsimplemanufacturercontainer.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleManufacturerBase : public ui::item::base::WBase
{
    Q_OBJECT
public:
    explicit WSimpleManufacturerBase(QWidget *parent = 0);
    ~WSimpleManufacturerBase();

private:
    void constructControls(QToolBar *tb);
    ui::item::base::WContainer *buidContainer();
    void constructHeader(base::WHeader *header);

};

}
}
}
#endif // WMANUFACTURERBASE_Hs
