#include "dicons.h"
#include "ui_dicons.h"
#include "ui_defines.h"
#include "cfiledialogs.h"
#include "icons.h"
#include "st.h"
#include "hacc_options.h"

namespace ui
{
namespace icons
{
HACC_STD_TRANSLATE_UI(DIcons, QDialog)

DIcons::DIcons(QWidget *parent) : QDialog(parent), m_ui(new Ui::DIcons)
{
    m_selectedId = 0;
    m_ui->setupUi(this);
    m_ui->tbAdd->setIcon(HACC_ICONS->icon(tools::icons::iIcon, tools::icons::oNew));
    connect(m_ui->tbRefresh       , SIGNAL(clicked())            , m_ui->pwIconsContainer, SLOT(refresh())            );
    connect(HACC_DB_ICONS       , SIGNAL(updated())            , m_ui->pwIconsContainer, SLOT(refresh())            );
    connect(m_ui->tbAdd           , SIGNAL(clicked())            , this                , SLOT(add())                );
    connect(m_ui->pwIconsContainer, SIGNAL(selected(hacc::TDBID)), this                , SLOT(selected(hacc::TDBID)));
    connect(m_ui->tbClearUnused   , SIGNAL(clicked())            , HACC_DB_ICONS       , SLOT(removeUnused())       );
    m_ui->pwIconsContainer->refresh();
    HACC_RESTORE_DIALOG;
}

DIcons::~DIcons()
{
    HACC_SAVE_DIALOG;
    delete m_ui;
}

void DIcons::add()
{
    tools::dialog::SFileDialogResult dlgResult =
            tools::dialog::CFileDialogs::getOpenImage(tr("Open icon"));
    if(dlgResult.dialogOk)
    {
        foreach(QString fileName, dlgResult.fileNames)
        {
            if(QFile::exists(fileName)) { HACC_DB_ICONS->add(fileName); }
        }
        m_ui->pwIconsContainer->refresh();
    }
}

hacc::TDBID DIcons::selected()
{
    return m_selectedId;
}

void DIcons::selected(hacc::TDBID id)
{
    m_selectedId = id;
    accept();
}

}
}
