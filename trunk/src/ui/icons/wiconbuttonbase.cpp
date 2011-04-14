#include "wiconbuttonbase.h"
#include "st.h"

namespace ui
{
namespace icons
{

WIconButtonBase::WIconButtonBase(const hacc::TDBID &iconId, QWidget *parent) : QToolButton(parent), hacc::CIDItem(iconId)
{
    setIcon(HACC_DB_ICONS->icon(id()));
}

WIconButtonBase::~WIconButtonBase()
{}

void WIconButtonBase::setID(const hacc::TDBID & id)
{
    hacc::CIDItem::setID(id);
    setIcon(HACC_DB_ICONS->icon(id));
}

}
}
