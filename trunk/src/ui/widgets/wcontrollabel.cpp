#include "wcontrollabel.h"
#include <QGraphicsOpacityEffect>
#include <QMouseEvent>
#include <QAction>
#include "font.h"

namespace ui
{
namespace widget
{

#define ITEM_MIN_HEIGHT 18

WControlLabel::WControlLabel(QWidget *parent) : QLabel(parent)
{
    setMouseTracking(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    int sze = tools::font::fontHeight(font());
    setMinimumHeight(sze);
    setMaximumHeight(sze);
}

WControlLabel::~WControlLabel()
{
    while(!m_wicons.empty()) { delete m_wicons.takeLast(); }
}

void WControlLabel::enterEvent ( QEvent * event )
{
    setButtonsVisible(true);
    Q_UNUSED(event);
}

void WControlLabel::leaveEvent( QEvent * event )
{
    setButtonsVisible(false);
    Q_UNUSED(event);
}

void WControlLabel::resizeEvent ( QResizeEvent * event )
{
    fixButtonsPosition();
    Q_UNUSED(event);
}

void WControlLabel::fixButtonsPosition()
{
    int w = width() - 16;
    foreach(ui::icons::WIcon *wicon, m_wicons)
    {
        w = w-18;
        wicon->move(w, 0);
    }
}

void WControlLabel::setButtonsVisible(bool visible)
{
    foreach(ui::icons::WIcon *wicon, m_wicons)
    {
        wicon->setVisible(visible);
    }
}

/**
  Добавляет всплывающую кнопку и привязывает к ней данное действие
  */
void WControlLabel::addAction(QAction *action)
{
    ui::widget::WIconButton *wicon = new ui::widget::WIconButton(action->icon(), this);
    wicon->setWindowOpacity(0.5);
    wicon->setToolTip(action->toolTip());
    wicon->hide();
    connect(wicon, SIGNAL(clicked()), action, SLOT(trigger()));
    m_wicons.append(wicon);
    fixButtonsPosition();
    QWidget::addAction(action);
}

}
}
