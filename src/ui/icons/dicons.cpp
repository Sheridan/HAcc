#include "dicons.h"
#include "ui_dicons.h"
#include "ui_defines.h"
#include "cfiledialogs.h"
#include "icons.h"
#include "st.h"
namespace ui
{
namespace icons
{
HACC_STD_TRANSLATE_UI(DIcons, QDialog)

DIcons::DIcons(QWidget *parent) : QDialog(parent), ui(new Ui::DIcons)
{
    selectedId = 0;
    ui->setupUi(this);
    ui->tbAdd->setIcon(HACC_ICONS->icon(tools::icons::iIcon, tools::icons::oNew));
    connect(ui->tbRefresh       , SIGNAL(clicked())            , ui->pwIconsContainer, SLOT(refresh())            );
    connect(HACC_DB_ICONS       , SIGNAL(updated())            , ui->pwIconsContainer, SLOT(refresh())            );
    connect(ui->tbAdd           , SIGNAL(clicked())            , this                , SLOT(add())                );
    connect(ui->pwIconsContainer, SIGNAL(selected(hacc::TDBID)), this                , SLOT(selected(hacc::TDBID)));
    connect(ui->tbClearUnused   , SIGNAL(clicked())            , HACC_DB_ICONS       , SLOT(removeUnused())       );
    ui->pwIconsContainer->refresh();
    HACC_RESTORE_DIALOG;
}

DIcons::~DIcons()
{
    HACC_SAVE_DIALOG;
    delete ui;
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
        ui->pwIconsContainer->refresh();
    }
}

hacc::TDBID DIcons::selected()
{
    return selectedId;
}

void DIcons::selected(hacc::TDBID id)
{
    selectedId = id;
    accept();
}

}
}
