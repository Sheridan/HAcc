/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WSIMPLECURRENCYBASE_H
#define WSIMPLECURRENCYBASE_H

#include "wbase.h"
#include "wsimplecurrencycontainer.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleCurrencyBase :
        public ui::item::base::WBase
{
    Q_OBJECT
public:
    WSimpleCurrencyBase(QWidget *parent = 0);
    ~WSimpleCurrencyBase();
private:
    void constructControls(QToolBar *tb);
    ui::item::base::WContainer *buidContainer();
    void constructHeader(base::WHeader *header);

};

}
}
}
#endif // WSIMPLECURRENCYBASE_H
