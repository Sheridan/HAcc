#include "citemlabels.h"
#include <QVariant>
#include "hacc_debug.h"

namespace ui
{
namespace item
{
namespace base
{

CItemLabels::CItemLabels()
{}

CItemLabels::~CItemLabels()
{
    foreach (WItemLabel *l, m_labels)
    {
        delete l;
    }
    m_labels.clear();
}

void CItemLabels::initialize(const int &columns, const int &rows, QWidget *parent, QGridLayout *layout)
{
    m_parent  = parent;
    m_layout  = layout;
    m_columns = columns;
    m_rows    = rows;
    m_maxDim  = qMax(m_columns, m_rows);
    WItemLabel *l;
    for (int column=0; column<m_columns; column++)
    {
        for (int row=0; row<m_rows; row++)
        {
            l = new WItemLabel(m_parent);
            m_layout->addWidget(l, row, column);
            m_labels[row*m_maxDim+column] = l;
        }
    }
}

void CItemLabels::setLabels(const QStringList& strings)
{
    int cnt=0;
    for (int column=0; column<m_columns; column++)
    {
        for (int row=0; row<m_rows; row++)
        {
            m_labels[row*m_maxDim+column]->setText(strings[cnt]);
            cnt++;
        }
    }
}

int CItemLabels::labelsHeight()
{
    int maxItemHeight = 0;
    int rowsHeight = 0;
    for (int row=0; row<m_rows; row++)
    {
        maxItemHeight = 0;
        for (int column=0; column<m_columns; column++)
        {
             maxItemHeight = qMax(maxItemHeight, m_labels[row*m_maxDim+column]->height());
        }
        rowsHeight += maxItemHeight;
    }
    return rowsHeight;
}

void CItemLabels::setText(const int &column, const int &row, const QString &text)
{
    m_labels[row*m_maxDim+column]->setText(text);
}

void CItemLabels::setIcon(const int &column, const int &row, const QIcon &icon)
{
    m_labels[row*m_maxDim+column]->setIcon(icon);
}

void CItemLabels::setIcon(const int &column, const int &row, const QString &file)
{
    m_labels[row*m_maxDim+column]->setIcon(file);
}

void CItemLabels::setIcon(const int &column, const int &row, const hacc::TDBID &id)
{
    m_labels[row*m_maxDim+column]->setIcon(id);
}

ui::widget::WControlLabel *CItemLabels::controlLabel(const int &column, const int &row)
{
    return m_labels[row*m_maxDim+column]->label();
}

void CItemLabels::setPropertyToAll(const char *name, const QVariant &property)
{
    foreach (WItemLabel *l, m_labels)
    {
        l->setProperty(name, property);
    }
}

void CItemLabels::setStyleSrcToAll(const QString &style)
{
    foreach (WItemLabel *l, m_labels)
    {
        l->setStyleSheet(style);
    }
}

}
}
}
