#include "wheader.h"
#include "resources.h"
#include <QVariant>

namespace ui
{
namespace item
{
namespace base
{

WHeader::WHeader(QWidget *parent)
    : ui::widget::WStyledWidget(parent),
      CItemLabels()
{
    setProperty("header", "base");
    m_layout = new QGridLayout();

    setLayout(m_layout);
}

WHeader::~WHeader()
{
    delete m_layout;
}

void WHeader::setLabels(const int &columns, const int &rows, const QStringList& strings)
{
    initialize(columns, rows, this, m_layout);
    CItemLabels::setLabels(strings);
    setPropertyToAll("header", "item");
}

}
}
}
