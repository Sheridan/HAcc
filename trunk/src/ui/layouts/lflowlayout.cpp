#include "lflowlayout.h"
#include <QWidget>
namespace ui
{
namespace layout
{

LFlowLayout::LFlowLayout(QWidget *parent, int margin, int hSpacing, int vSpacing)
    : QLayout(parent),
      m_hSpace(hSpacing),
      m_vSpace(vSpacing)
{
    setContentsMargins(margin, margin, margin, margin);
    m_height = 0;
    m_width = 0;
}

LFlowLayout::LFlowLayout(int margin, int hSpacing, int vSpacing)
    : QLayout(),
      m_hSpace(hSpacing),
      m_vSpace(vSpacing)
{
    setContentsMargins(margin, margin, margin, margin);
    m_height = 0;
    m_width = 0;
}

LFlowLayout::~LFlowLayout()
{
    while (!itemList.empty())
    {
        delete itemList.takeLast();
    }
}

void         LFlowLayout::addItem(QLayoutItem *item) {        itemList.append(item); }
int          LFlowLayout::count  (         ) const   { return itemList.size();       }
QLayoutItem *LFlowLayout::itemAt (int index) const   { return itemList.value(index); }
QLayoutItem *LFlowLayout::takeAt (int index)
{
    if (index >= 0 && index < itemList.size())
        return itemList.takeAt(index);
    return 0;
}

Qt::Orientations LFlowLayout::expandingDirections() const { return Qt::Vertical; }
bool             LFlowLayout::hasHeightForWidth  () const { return true        ; }


int LFlowLayout::heightForWidth(int width) const
{
    return doLayout(QRect(0, 0, width, 0), true);
}

void LFlowLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);
    doLayout(rect, false);
}

QSize LFlowLayout::sizeHint() const
{
    return minimumSize();
}

QSize LFlowLayout::minimumSize() const
{
    return QSize(m_width + 2*margin(), m_height + 2*margin());
}

int LFlowLayout::doLayout(const QRect &rect, bool testOnly) const
{
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
    int x = effectiveRect.x();
    int y = effectiveRect.y();
    int lineHeight = 0;
    QSize itemSizeHint;
    int nextX   = 0;
    int tHeight = 0;
    int tWidth  = 0;
    foreach (QLayoutItem *item, itemList)
    {
        itemSizeHint = item->sizeHint();
        nextX = x + itemSizeHint.width() + m_hSpace;
        if (nextX - m_hSpace > effectiveRect.right() && lineHeight > 0)
        {
            x = effectiveRect.x();
            y = y + lineHeight + m_vSpace;
            nextX = x + itemSizeHint.width() + m_hSpace;
            lineHeight = 0;
            tWidth = qMax(tWidth, x);
        }
        if (!testOnly)
        {
            item->setGeometry(QRect(QPoint(x, y), itemSizeHint));
        }
        x = nextX;
        lineHeight = qMax(lineHeight, itemSizeHint.height());
    }
    tHeight = y + lineHeight - rect.y() + bottom;
    if(!testOnly)
    {
        m_height = tHeight;
        m_width = tWidth;
    }
    return tHeight;
}

int LFlowLayout::totalHeight()
{
    return m_height;
}

}
}
