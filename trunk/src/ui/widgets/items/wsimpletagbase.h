#ifndef WTAGBASE_Hs
#define WTAGBASE_Hs
#include "wbase.h"
#include "wsimpletagcontainer.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleTagBase : public ui::item::base::WBase
{
    Q_OBJECT
public:
    explicit WSimpleTagBase(QWidget *parent = 0);
    ~WSimpleTagBase();
private:
    void constructControls(QToolBar *tb);
    ui::item::base::WContainer *buidContainer();
    void constructHeader(base::WHeader *header);

};

}
}
}
#endif // WTAGBASE_Hs
