#ifndef WTHINGBASE_He
#define WTHINGBASE_He

#include "wbase.h"
#include "wexpandedthingcontainer.h"

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedThingBase : public ui::item::base::WBase
{
    Q_OBJECT
public:
    WExpandedThingBase(QWidget *parent = 0);
    ~WExpandedThingBase();

private:
    void constructControls(QToolBar *tb);
    ui::item::base::WContainer *buidContainer();
    void constructHeader(base::WHeader *header);
};

}
}
}
#endif // WTHINGBASE_He
