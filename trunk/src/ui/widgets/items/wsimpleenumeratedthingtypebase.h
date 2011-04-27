/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WENUMERATEDTHINGTYPEBASE_Hs
#define WENUMERATEDTHINGTYPEBASE_Hs

#include "wbase.h"
#include "wsimpleenumeratedthingtypecontainer.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleEnumeratedThingTypeBase : public ui::item::base::WBase
{
    Q_OBJECT
public:
    explicit WSimpleEnumeratedThingTypeBase(QWidget *parent = 0);
    ~WSimpleEnumeratedThingTypeBase();
private:
    void constructControls(QToolBar *tb);
    ui::item::base::WContainer *buidContainer();
    void constructHeader(base::WHeader *header);

};

}
}
}
#endif // WENUMERATEDTHINGTYPEBASE_Hs
