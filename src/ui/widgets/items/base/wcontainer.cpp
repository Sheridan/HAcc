
#include "wcontainer.h"
#include "witem.h"
#include "st.h"
#include "hacc_debug.h"

#include <QResizeEvent>

namespace ui
{
namespace item
{
namespace base
{

WContainer::WContainer(QWidget *parent) : ui::widget::WAbstractScrollArea(parent)
{
    m_vblContainer = new QVBoxLayout();
    setViewportLayout(m_vblContainer);
    m_vblContainer->addStretch();
    connect(HACC_DB, SIGNAL(opened()), this, SLOT(refresh()));
    connect(HACC_DB, SIGNAL(closed()), this, SLOT(cleanItems()));
}

WContainer::~WContainer()
{
    cleanItems();
    delete m_vblContainer;
}

void WContainer::cleanItems()
{
    if(!m_items.empty())
    {
        foreach(WItem *i, m_items)
        {
            removeItem(i);
        }
    }
}

void WContainer::appendItem(WItem *i)
{
    m_items[i->itemID()] = i;
    i->setParent(viewport());
    int icnt = m_vblContainer->count();
    i->setAlternateBackground(!(icnt % 2));
//    m_vblContainer->insertWidget(icnt-1, new QLabel("-----------------------------", viewport()));
    m_vblContainer->insertWidget(icnt-1, i);
    connect(i, SIGNAL(clicked(const hacc::TDBID &))      , this, SIGNAL(clicked(const hacc::TDBID &))      );
    connect(i, SIGNAL(doubleClicked(const hacc::TDBID &)), this, SIGNAL(doubleClicked(const hacc::TDBID &)));
    resizeWievport();
}

void WContainer::removeItem(WItem *i)
{
    m_vblContainer->removeWidget(i);
    m_items.remove(i->itemID());
    delete i;
}

void WContainer::removeItem(const hacc::TDBID &id)
{
    removeItem(item(id));
}

WItem *WContainer::item(const hacc::TDBID &id)
{
    return m_items[id];
}

int WContainer::contentHeight()
{
    int h = 0;
    foreach(WItem *i, m_items)
    {
        h += i->height();
    }
    return h;
}

void WContainer::setSearchText(const QString &text)
{
    m_searchText = text;
    refresh();
}

void WContainer::itemRemoved(const hacc::TDBID &id)
{
    removeItem(id);
}

//void WContainer::resizeEvent ( QResizeEvent * event )
//{
////    HACC_DEBUG(event->size());
//    ui::widget::WAbstractScrollArea::resizeEvent(event);
//}

}
}
}
