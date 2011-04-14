#ifndef WSIMPLEMOVEMENTBASE_H
#define WSIMPLEMOVEMENTBASE_H

#include "wbase.h"
#include "wsimplemovementcontainer.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleMovementBase : public ui::item::base::WBase
{
    Q_OBJECT
public:
    explicit WSimpleMovementBase(QWidget *parent = 0);
    ~WSimpleMovementBase();
private:
    void constructControls(QToolBar *tb);
    ui::item::base::WContainer *buidContainer();
    void constructHeader(base::WHeader *header);

};

}
}
}

#endif // WSIMPLEMOVEMENTBASE_H
