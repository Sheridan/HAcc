#ifndef WCURRENCYSELECTPOPUP_H
#define WCURRENCYSELECTPOPUP_H

#include "wselectorpopup.h"
#include "hacc_types.h"
#include "ccontractors.h"

namespace ui
{
namespace selector
{

class WCurrencySelectPopup : public base::WSelectorPopup
{
    Q_OBJECT
public:
    WCurrencySelectPopup(QWidget *parent = 0);
    ~WCurrencySelectPopup();

private:
    ui::item::base::WBase *createContainer();
};

}
}

#endif // WCURRENCYSELECTPOPUP_H
