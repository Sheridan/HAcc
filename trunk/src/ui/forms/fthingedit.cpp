#include "fthingedit.h"
#include "ui_fthingedit.h"
#include "ui_defines.h"
#include "cfiledialogs.h"
#include "images.h"
#include "st.h"
#include "hacc_date.h"

#define HACC_PERIOD_ASSIGN(_value,_checkBox,_comboBox,_spinBox) \
{ \
    int days = _value; \
    if(days) \
    { \
        ui->_checkBox->setChecked(true); \
        tools::date::STimePeriod period = tools::date::daysTo(days); \
        ui->_comboBox->setCurrentIndex(period.period); \
        ui->_spinBox->setValue(period.days); \
    } \
}

namespace ui
{
namespace form
{

HACC_STD_TRANSLATE_UI(FThingEdit, QDialog)

FThingEdit::FThingEdit(QWidget *parent) : QDialog(parent), ui(new Ui::FThingEdit)
{
    init();
    setObjectName(objectName()+"_new");
    ui->lImage->clear();
    ui->pwIcons->setID(7);
    HACC_RESTORE_DIALOG;
}

FThingEdit::FThingEdit(const hacc::TDBID &id, QWidget *parent) : QDialog(parent), ui(new Ui::FThingEdit)
{
    init();
    setObjectName(objectName()+"_edit");
    QSqlQuery q = HACC_DB->query("select "
                          /* 0*/ "name, "
                          /* 1*/ "description, "
                          /* 2*/ "icon_id, "
                          /* 3*/ "image, "
                          /* 4*/ "enumerated_type_id, "
                          /* 5*/ "manufacturer_id, "
                          /* 6*/ "expiration_period, "
                          /* 7*/ "guarantee_period "
                                 "from things where id=?",
                                 QVariantList() << id);
    if(q.next())
    {
        ui->leName ->setText(HACC_DB_2_STRG(q, 0));
        ui->pwIcons->setID(HACC_DB_2_DBID(q, 2));
        ui->teDescription->appendPlainText(HACC_DB_2_STRG(q, 1));
        ui->lImage->setPixmap(ui::images::byteArray2Pixmap(q.value(3).toByteArray()), 128);
        ui->pwEnumerateType->setID(HACC_DB_2_DBID(q, 4));
        ui->pwManufacturer ->setID(HACC_DB_2_DBID(q, 5));
        HACC_PERIOD_ASSIGN(HACC_DB_2_PERD(q ,6), cbExpiration, cbExpCount, sbExpDays);
        HACC_PERIOD_ASSIGN(HACC_DB_2_PERD(q, 7), cbGuarantee, cbGuarCount, sbGuarDays);
        ui->rbService   ->setChecked(HACC_THINGS->tagAttached(HACC_TAG_ID_SERVICE   , id));
        ui->rbObject    ->setChecked(HACC_THINGS->tagAttached(HACC_TAG_ID_OBJECT    , id));
        ui->rbExpendable->setChecked(HACC_THINGS->tagAttached(HACC_TAG_ID_EXPENDABLE, id));
    }
    HACC_RESTORE_DIALOG;
}

void FThingEdit::init()
{
    ui->setupUi(this);
    ui->lImage->setEmptyText(tr("No image"));
    ui->pwEnumerateType->init();
    ui->pwManufacturer->init();
}

FThingEdit::~FThingEdit()
{
    HACC_SAVE_DIALOG;
    delete ui;
}

void FThingEdit::on_tbLoadImage_clicked()
{
    ui->lImage->clear();
    tools::dialog::SFileDialogResult dlgResult =
            tools::dialog::CFileDialogs::getOpenImage(tr("Open image"));
    if(dlgResult.dialogOk && !dlgResult.fileNames[0].isEmpty())
    {
        QPixmap *pm = new QPixmap(dlgResult.fileNames[0]);
        ui->lImage->setPixmap(pm->scaled(QSize(128,128), Qt::KeepAspectRatio, Qt::SmoothTransformation), 128);
        delete pm;
    }
}

void FThingEdit::on_tbClearImage_clicked()
{
    ui->lImage->clear();
}

QString FThingEdit::name()
{
    return ui->leName->text();
}

QString FThingEdit::description()
{
    return ui->teDescription->toPlainText();
}

hacc::TDBID FThingEdit::iconId()
{
    return ui->pwIcons->id();
}

hacc::TDBID FThingEdit::enumeratedTypeThingId()
{
    return ui->pwEnumerateType->id();
}

hacc::TDBID FThingEdit::manufacturerId()
{
    return ui->pwManufacturer->id();
}

QByteArray FThingEdit::pixmapData()
{
    return ui::images::pixmap2ByteArray(ui->lImage->pixmap());
}

bool FThingEdit::hasImage()
{
    return !ui->lImage->empty();
}

int FThingEdit::expiration()
{
    return ui->cbExpiration->checkState() == Qt::Checked ?
                tools::date::daysFrom(ui->sbExpDays->value(), ui->cbExpCount->currentIndex()) :
                0;
}

int FThingEdit::guarantee()
{
    return ui->cbGuarantee->checkState() == Qt::Checked ?
                tools::date::daysFrom(ui->sbGuarDays->value(), ui->cbGuarCount->currentIndex()) :
                0;
}

int FThingEdit::thingType()
{
    if(ui->rbService->isChecked())    { return HACC_TAG_ID_SERVICE; }
    if(ui->rbObject->isChecked())     { return HACC_TAG_ID_OBJECT; }
    if(ui->rbExpendable->isChecked()) { return HACC_TAG_ID_EXPENDABLE; }
    return HACC_TAG_ID_OBJECT;
}

}
}
