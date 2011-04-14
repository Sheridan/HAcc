#ifndef WVALUABLESELECTPOPUP_H
#define WVALUABLESELECTPOPUP_H

#include "wselectorpopup.h"
namespace ui
{
namespace selector
{

class WValuableSelectPopup : public base::WSelectorPopup
{
    Q_OBJECT
public:
    explicit WValuableSelectPopup(QWidget *parent = 0);
    ~WValuableSelectPopup();
private:
    ui::item::base::WBase *createContainer();
};

}
}
#endif // WVALUABLESELECTPOPUP_H
