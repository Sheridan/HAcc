#include <QMessageBox>
#include "cfiledialogs.h"
#include "wiconitem.h"
#include "icons.h"
#include "st.h"

namespace ui
{
namespace icons
{

WIconItem::WIconItem(const hacc::TDBID &iconId, QWidget *parent) : WIconButtonBase(iconId, parent)
{
//    setProperty("btype", "icon");

    m_menu = new QMenu(this);
    m_menu->addAction(HACC_ICONS->icon(tools::icons::iIcon       , tools::icons::oEdit),   tr("Replace"), this, SLOT(edit()));
    if(iconId >= HACC_DB_ICONS->predeclaredIconsCount())
    {
        m_menu->addAction(HACC_ICONS->icon(tools::icons::iIcon   , tools::icons::oRemove), tr("Delete" ), this, SLOT(remove()));
    }

    setMenu(m_menu);
    setPopupMode(QToolButton::MenuButtonPopup);

    connect(this, SIGNAL(clicked()), this, SLOT(emitSelected()));
}

WIconItem::~WIconItem()
{
    delete m_menu;
}

void WIconItem::emitSelected()
{
    emit selected(id());
}

void WIconItem::remove()
{
    if(QMessageBox::question(
            HACC_WINDOW,
            tr("Icon remove"),
            tr("You sure you want to delete this icon?"),
            QMessageBox::Yes | QMessageBox::No)
        == QMessageBox::Yes)
    {
        HACC_DB_ICONS->remove(id());
    }
}

void WIconItem::edit()
{
    tools::dialog::SFileDialogResult dlgResult =
            tools::dialog::CFileDialogs::getOpenImage(tr("Open icon"));
    if(dlgResult.dialogOk)
    {
        foreach(QString fileName, dlgResult.fileNames)
        {
            if(QFile::exists(fileName))
            {
                HACC_DB_ICONS->replace(id(), fileName);
                setIcon(HACC_DB_ICONS->icon(id()));
            }
        }
    }
}

}
}
