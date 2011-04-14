#ifndef WENUMERATEDTHINGTYPEPOPUP_H
#define WENUMERATEDTHINGTYPEPOPUP_H

#include "wselectorpopup.h"
#include "wsimpleenumeratedthingtypebase.h"

namespace ui
{
namespace selector
{

class WEnumeratedThingTypePopup : public base::WSelectorPopup
{
    Q_OBJECT
public:
    explicit WEnumeratedThingTypePopup(QWidget *parent = 0);
    ~WEnumeratedThingTypePopup();
private:
    ui::item::base::WBase *createContainer();
};

}
}
#endif // WENUMERATEDTHINGTYPEPOPUP_H
