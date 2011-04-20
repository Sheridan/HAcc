#include "wiconselect.h"
#include "dicons.h"
#include "st.h"
namespace ui
{
namespace icons
{

WIconSelect::WIconSelect(const hacc::TDBID &iconID, QWidget *parent) : WIconButtonBase(iconID, parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(select()));
}

WIconSelect::WIconSelect(QWidget *parent) : WIconButtonBase(1, parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(select()));
}

WIconSelect::~WIconSelect()
{
}

void WIconSelect::select()
{
    ui::icons::DIcons icons(this);
    if(icons.exec() == QDialog::Accepted)
    {
        setID(icons.selected());
        setIcon(HACC_DB_ICONS->icon(id()));
    }
}

}
}
