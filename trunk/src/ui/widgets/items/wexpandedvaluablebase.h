/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WEXPANDEDVALUABLEBASE_H
#define WEXPANDEDVALUABLEBASE_H

#include "wbase.h"
#include "wexpandedvaluablecontainer.h"

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedValuableBase : public ui::item::base::WBase
{
    Q_OBJECT
public:
    WExpandedValuableBase(QWidget *parent = 0);
    ~WExpandedValuableBase();

private:
    void constructControls(QToolBar *tb);
    ui::item::base::WContainer *buidContainer();
    void constructHeader(base::WHeader *header);
};

}
}
}

#endif // WEXPANDEDVALUABLEBASE_H
