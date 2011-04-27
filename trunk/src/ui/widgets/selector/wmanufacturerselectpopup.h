/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WMANUFACTURERSELECTPOPUP_H
#define WMANUFACTURERSELECTPOPUP_H

#include "wselectorpopup.h"

namespace ui
{
namespace selector
{

class WManufacturerSelectPopup : public base::WSelectorPopup
{
    Q_OBJECT
public:
    explicit WManufacturerSelectPopup(QWidget *parent = 0);
    ~WManufacturerSelectPopup();
private:
    ui::item::base::WBase *createContainer();
};

}
}
#endif // WMANUFACTURERSELECTPOPUP_H
