#include "wabstractscrollarea.h"
#include <QVariant>
#include <QScrollBar>
#include "hacc_debug.h"

namespace ui
{
namespace widget
{

WAbstractScrollArea::WAbstractScrollArea(QWidget *parent) : QAbstractScrollArea(parent)
{
    setProperty("scrollarea", true);
    m_topPosition = 0;
    m_wArea = NULL;
    m_lArea = NULL;
}

WAbstractScrollArea::~WAbstractScrollArea()
{
    delete m_wArea;
}

void WAbstractScrollArea::buildSelfUi()
{
    setVerticalScrollBarPolicy  (Qt::ScrollBarAsNeeded );
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_wArea = new QWidget(this);
    m_wArea->setLayout(m_lArea);
    setViewport(m_wArea);
}

void WAbstractScrollArea::resizeWievport()
{
    int sAreaHeight = height();
    int ctntHeight = contentHeight();
    if(ctntHeight > sAreaHeight)
    {
        verticalScrollBar()->setPageStep(sAreaHeight);
        verticalScrollBar()->setRange(0, ctntHeight - sAreaHeight);
    }
    else
    {
        verticalScrollBar()->setPageStep(0);
        verticalScrollBar()->setRange(0,0);
        m_topPosition = 0;
        m_wArea->move(1, 1);
    }
}

void WAbstractScrollArea::scrollContentsBy ( int dx, int dy )
{
    m_topPosition += dy;
    m_wArea->move(1, m_topPosition);
    Q_UNUSED(dx);
}

void WAbstractScrollArea::resizeEvent ( QResizeEvent * event )
{
    resizeWievport();
    Q_UNUSED(event);
}

void WAbstractScrollArea::setViewportLayout(QLayout *ly)
{
    m_lArea = ly;
    m_lArea->setContentsMargins(0,0,0,0);
    m_lArea->setSpacing(0);
    m_lArea->setSizeConstraint(QLayout::SetMinimumSize);
    buildSelfUi();
}

}
}
