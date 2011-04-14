#ifndef WRESIZER_H
#define WRESIZER_H

#include "wstyledwidget.h"
#include <QPoint>
#include "ui_defines.h"

namespace ui
{
namespace item { namespace base { class WItem; } }
namespace widget
{

class WResizer : public ui::widget::WStyledWidget
{
    Q_OBJECT
public:
    explicit WResizer(ui::item::base::WItem *target);
    QSize sizeHint () const;
private:

    ui::item::base::WItem *m_target;
    void mouseMoveEvent ( QMouseEvent * event );
    QPoint m_mousePos;
    int m_delta;

};

}
}
#endif // WRESIZER_H
