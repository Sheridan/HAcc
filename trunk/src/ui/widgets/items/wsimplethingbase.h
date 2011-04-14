#ifndef WTHINGBASE_Hs
#define WTHINGBASE_Hs

#include "wbase.h"
#include "wsimplethingcontainer.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleThingBase : public ui::item::base::WBase
{
    Q_OBJECT
public:
    explicit WSimpleThingBase(QWidget *parent = 0);
    ~WSimpleThingBase();

private:
    void constructControls(QToolBar *tb);
    ui::item::base::WContainer *buidContainer();
    void constructHeader(base::WHeader *header);

};

}
}
}
#endif // WTHINGBASE_Hs
