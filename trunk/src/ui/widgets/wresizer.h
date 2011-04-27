/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
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

//! Ресайзер родителя
/**
  Планочка, при перемещении которой изменяется размер родителя
  */
class WResizer : public ui::widget::WStyledWidget
{
    Q_OBJECT
public:
    explicit WResizer(ui::item::base::WItem *target);
    QSize sizeHint () const;

private:
    void mouseMoveEvent ( QMouseEvent * event );
    ui::item::base::WItem *m_target;   //!< Цель, у которой надо менять размер.
    QPoint                 m_mousePos; //!< Координаты мыша
    int                    m_delta;    //!< Дельта, на которую надо менять размер

};

}
}
#endif // WRESIZER_H
