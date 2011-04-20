#include "wicon.h"
#include "st.h"

namespace ui
{
namespace icons
{

WIcon::WIcon(QWidget *parent) : ui::images::WImage(16, parent), hacc::CIDItem()
{
    init();
}

WIcon::WIcon(int side, QWidget *parent) : ui::images::WImage(side, parent), hacc::CIDItem()
{
    init();
}

WIcon::~WIcon()
{}

void WIcon::init()
{
    setEmptyText(tr("--"));
}

void WIcon::setIcon(const QIcon &icon, int extent)
{
    setPixmap(icon.pixmap(extent), extent);
}

void WIcon::setIcon(const hacc::TDBID &iconID)
{
    setID(iconID);
    if (!m_connected)
    {
        m_connected = connect(HACC_DB_ICONS, SIGNAL(updated(hacc::TDBID)), this, SLOT(updated(hacc::TDBID)));
    }
    refreshIdIcon();
}

void WIcon::refreshIdIcon()
{
    setIcon(HACC_DB_ICONS->icon(id()), 16);
}

void WIcon::setIcon(const QString &iconFile, int extent)
{
    setPixmap(iconFile, extent);
}

void WIcon::updated(hacc::TDBID iconID)
{
    if (iconID == id())
    {
        refreshIdIcon();
    }
}

}
}
