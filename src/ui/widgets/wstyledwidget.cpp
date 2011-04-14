#include "wstyledwidget.h"
#include <QPainter>
#include <QStyleOption>

namespace ui
{
namespace widget
{

WStyledWidget::WStyledWidget(QWidget *parent, Qt::WindowFlags f) : QWidget(parent, f)
{}

WStyledWidget::~WStyledWidget()
{}

void WStyledWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QStyleOption styleOption;
    styleOption.init(this);
    QPainter pir(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOption, &pir, this);
}

}
}
