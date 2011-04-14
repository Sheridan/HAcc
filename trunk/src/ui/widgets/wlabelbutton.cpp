#include "wlabelbutton.h"
#include <QMouseEvent>

namespace ui
{
namespace widget
{

WLabelButton::WLabelButton(QWidget *parent) : QLabel(parent)
{
    enableHandCursor(true);
}

void WLabelButton::enableHandCursor(bool enable)
{
    if(enable)
    {
        setCursor(Qt::PointingHandCursor);
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
}

void WLabelButton::mousePressEvent ( QMouseEvent * ev )
{
    if (ev->buttons() || Qt::LeftButton)
    {
        emit clicked();
        mouseClickEvent();
    }
}

}
}
