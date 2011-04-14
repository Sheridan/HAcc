#include "wresizer.h"
#include <QMouseEvent>
#include <QSize>
#include "hacc_debug.h"
#include "witem.h"

namespace ui
{
namespace widget
{

#define HACC_RESIZER_HEIGHT 4

WResizer::WResizer(ui::item::base::WItem *target) : ui::widget::WStyledWidget(target), m_target(target)
{
    setProperty("resizer", true);
    setMouseTracking(true);
    setMinimumHeight(HACC_RESIZER_HEIGHT);
    setMaximumHeight(HACC_RESIZER_HEIGHT);
    setCursor(Qt::SplitVCursor);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_mousePos = QPoint(0,0);
    m_delta = 0;
}

void WResizer::mouseMoveEvent ( QMouseEvent * event )
{
    if(event->buttons() && Qt::LeftButton)
    {
        int delta = event->globalPos().y() - m_mousePos.y();
        if(delta != 0)
        {
            m_delta += delta;
            m_target->setHeightDelta(m_delta);
        }
    }
    m_mousePos = event->globalPos();
}

QSize WResizer::sizeHint () const
{
    return QSize(0, HACC_RESIZER_HEIGHT);
}

}
}
