/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WTHINGSELECTPOPUP_H
#define WTHINGSELECTPOPUP_H
#include "wselectorpopup.h"
namespace ui
{
namespace selector
{

class WThingSelectPopup : public base::WSelectorPopup
{
    Q_OBJECT
public:
    explicit WThingSelectPopup(QWidget *parent = 0);
    ~WThingSelectPopup();
private:
    ui::item::base::WBase *createContainer();
};

}
}
#endif // WTHINGSELECTPOPUP_H
