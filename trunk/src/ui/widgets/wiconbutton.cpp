#include "wiconbutton.h"
#include <QMouseEvent>

namespace ui
{
namespace widget
{

WIconButton::WIconButton(const QString &iconPath, QWidget *parent) : ui::icons::WIcon(16, parent)
{
    init();
    setIcon(iconPath);
}

WIconButton::WIconButton(const QIcon &icon, QWidget *parent) : ui::icons::WIcon(16, parent)
{
    init();
    setIcon(icon);
}

WIconButton::WIconButton(QWidget *parent) : ui::icons::WIcon(16, parent)
{
    init();
}

WIconButton::~WIconButton()
{}

void WIconButton::init()
{
    setCursor(Qt::PointingHandCursor);
}

void WIconButton::mousePressEvent ( QMouseEvent * ev )
{
    if (ev->buttons() || Qt::LeftButton)
    {
        emit clicked();
    }
}

}
}
