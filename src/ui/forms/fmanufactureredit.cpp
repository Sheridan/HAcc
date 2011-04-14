#include "fmanufactureredit.h"
#include "ui_fmanufactureredit.h"
#include "ui_defines.h"
#include "cfiledialogs.h"
#include "images.h"
#include "st.h"

namespace ui
{
namespace form
{

HACC_STD_TRANSLATE_UI(FManufacturerEdit, QDialog)

FManufacturerEdit::FManufacturerEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FManufacturerEdit)
{
   init();
   setObjectName(objectName()+"_new");
   ui->lLogo->clear();
   ui->pwIcons->setID(11);
   HACC_RESTORE_DIALOG;
}

FManufacturerEdit::FManufacturerEdit(const hacc::TDBID &id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FManufacturerEdit)
{
    init();
    setObjectName(objectName()+"_edit");
    QSqlQuery q = HACC_DB->query("select "
                                 "manufacturers.name, "
                                 "manufacturers.icon_id, "
                                 "manufacturers.description, "
                                 "manufacturers.image "
                                 "from manufacturers "
                                 "where id=?",
                                 QVariantList() << id);
    if(q.next())
    {
        ui->leName ->setText(HACC_DB_2_STRG(q, 0));
        ui->pwIcons->setID  (HACC_DB_2_DBID(q, 1));
        ui->teDescription->appendPlainText(HACC_DB_2_STRG(q, 2));
        ui->lLogo->setPixmap(ui::images::byteArray2Pixmap(q.value(3).toByteArray()), 128);
    }
    HACC_RESTORE_DIALOG;
}

FManufacturerEdit::~FManufacturerEdit()
{
    HACC_SAVE_DIALOG;
    delete ui;
}

void FManufacturerEdit::init()
{
    ui->setupUi(this);
    ui->lLogo->setEmptyText(tr("No image"));
}

void FManufacturerEdit::on_tbLoadLogo_clicked()
{
    ui->lLogo->clear();
    tools::dialog::SFileDialogResult dlgResult =
            tools::dialog::CFileDialogs::getOpenImage(tr("Open image"));
    if(dlgResult.dialogOk && !dlgResult.fileNames[0].isEmpty())
    {
        QPixmap *pm = new QPixmap(dlgResult.fileNames[0]);
        ui->lLogo->setPixmap(pm->scaled(QSize(128,128), Qt::KeepAspectRatio, Qt::SmoothTransformation), 128);
        delete pm;
    }
}

void FManufacturerEdit::on_tbClearLogo_clicked()
{
    ui->lLogo->clear();
}

QString FManufacturerEdit::name()
{
    return ui->leName->text();
}

QString FManufacturerEdit::description()
{
    return ui->teDescription->toPlainText();
}

hacc::TDBID FManufacturerEdit::iconId()
{
    return ui->pwIcons->id();
}

QByteArray FManufacturerEdit::pixmapData()
{
    return ui::images::pixmap2ByteArray(ui->lLogo->pixmap());
}

bool FManufacturerEdit::hasImage()
{
    return !ui->lLogo->empty();
}

}
}

