#include "wiconscontainer.h"
#include <QVariant>
#include "wiconitem.h"
#include "st.h"

namespace ui
{
namespace icons
{

WIconsContainer::WIconsContainer(QWidget *parent) : ui::widget::WAbstractScrollArea(parent)
{
    m_baseLayout = new ui::layout::LFlowLayout();
//    HACC_DEBUG_OBJNAME_SET(m_vblContainer);
    m_baseLayout->setContentsMargins(0,0,0,0);
    m_baseLayout->setSpacing(0);
    setViewportLayout(m_baseLayout);
}

WIconsContainer::~WIconsContainer()
{
    clear();
}

void WIconsContainer::buildUi()
{}

int WIconsContainer::contentHeight()
{
    return 100;
}

void WIconsContainer::clear()
{
    if(!m_icons.empty())
    {
        foreach (WIconItem *i, m_icons)
        {
            m_baseLayout->removeWidget(i);
            delete i;
        }
        m_icons.clear();
    }
}

void WIconsContainer::refresh()
{
    clear();
    hacc::TDBID id;
    WIconItem *i;
    QSqlQuery q = HACC_DB->query("select id from icons order by id");
    while (q.next())
    {
        id = HACC_DB_2_DBID(q, 0);
        i = new WIconItem(id, viewport());
        connect(i, SIGNAL(selected(hacc::TDBID)), this, SIGNAL(selected(hacc::TDBID)));
        m_icons.append(i);
        m_baseLayout->addWidget(i);
    }
}

}
}
