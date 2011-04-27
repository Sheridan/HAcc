/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WSIMPLEVALUABLEBASE_H
#define WSIMPLEVALUABLEBASE_H
#include "wbase.h"
#include "wsimplevaluablecontainer.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleValuableBase : public ui::item::base::WBase
{
    Q_OBJECT
public:
    explicit WSimpleValuableBase(QWidget *parent = 0);
    ~WSimpleValuableBase();

private:
    void constructControls(QToolBar *tb);
    ui::item::base::WContainer *buidContainer();
    void constructHeader(base::WHeader *header);

};

}
}
}
#endif // WSIMPLEVALUABLEBASE_H
