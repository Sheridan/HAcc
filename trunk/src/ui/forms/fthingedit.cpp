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
        m_ui->_checkBox->setChecked(true); \
        tools::date::STimePeriod period = tools::date::daysTo(days); \
        m_ui->_comboBox->setCurrentIndex(period.period); \
        m_ui->_spinBox->setValue(period.days); \
    } \
}

namespace ui
{
namespace form
{

HACC_STD_TRANSLATE_UI(FThingEdit, QDialog)

FThingEdit::FThingEdit(QWidget *parent) : QDialog(parent), m_ui(new Ui::FThingEdit)
{
    init();
    setObjectName(objectName()+"_new");
    m_ui->lImage->clear();
    m_ui->pwIcons->setID(7);
    HACC_RESTORE_DIALOG;
}

FThingEdit::FThingEdit(const hacc::TDBID &id, QWidget *parent) : QDialog(parent), m_ui(new Ui::FThingEdit)
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
        m_ui->leName ->setText(HACC_DB_2_STRG(q, 0));
        m_ui->pwIcons->setID(HACC_DB_2_DBID(q, 2));
        m_ui->teDescription->appendPlainText(HACC_DB_2_STRG(q, 1));
        m_ui->lImage->setPixmap(ui::images::byteArray2Pixmap(q.value(3).toByteArray()), 128);
        m_ui->pwEnumerateType->setID(HACC_DB_2_DBID(q, 4));
        m_ui->pwManufacturer ->setID(HACC_DB_2_DBID(q, 5));
        HACC_PERIOD_ASSIGN(HACC_DB_2_PERD(q ,6), cbExpiration, cbExpCount, sbExpDays);
        HACC_PERIOD_ASSIGN(HACC_DB_2_PERD(q, 7), cbGuarantee, cbGuarCount, sbGuarDays);
        m_ui->rbService   ->setChecked(HACC_THINGS->tagAttached(HACC_TAG_ID_SERVICE   , id));
        m_ui->rbObject    ->setChecked(HACC_THINGS->tagAttached(HACC_TAG_ID_OBJECT    , id));
        m_ui->rbExpendable->setChecked(HACC_THINGS->tagAttached(HACC_TAG_ID_EXPENDABLE, id));
    }
    HACC_RESTORE_DIALOG;
}

void FThingEdit::init()
{
    m_ui->setupUi(this);
    m_ui->lImage->setEmptyText(tr("No image"));
    m_ui->pwEnumerateType->init();
    m_ui->pwManufacturer->init();
}

FThingEdit::~FThingEdit()
{
    HACC_SAVE_DIALOG;
    delete m_ui;
}

void FThingEdit::on_tbLoadImage_clicked()
{
    m_ui->lImage->clear();
    tools::dialog::SFileDialogResult dlgResult =
            tools::dialog::CFileDialogs::getOpenImage(tr("Open image"));
    if(dlgResult.dialogOk && !dlgResult.fileNames[0].isEmpty())
    {
        QPixmap *pm = new QPixmap(dlgResult.fileNames[0]);
        m_ui->lImage->setPixmap(pm->scaled(QSize(128,128), Qt::KeepAspectRatio, Qt::SmoothTransformation), 128);
        delete pm;
    }
}

void FThingEdit::on_tbClearImage_clicked()
{
    m_ui->lImage->clear();
}

QString FThingEdit::name()
{
    return m_ui->leName->text();
}

QString FThingEdit::description()
{
    return m_ui->teDescription->toPlainText();
}

hacc::TDBID FThingEdit::iconID()
{
    return m_ui->pwIcons->id();
}

hacc::TDBID FThingEdit::enumeratedThingTypeID()
{
    return m_ui->pwEnumerateType->id();
}

hacc::TDBID FThingEdit::manufacturerID()
{
    return m_ui->pwManufacturer->id();
}

QByteArray FThingEdit::pixmapData()
{
    return ui::images::pixmap2ByteArray(m_ui->lImage->pixmap());
}

bool FThingEdit::hasImage()
{
    return !m_ui->lImage->empty();
}

int FThingEdit::expiration()
{
    return m_ui->cbExpiration->checkState() == Qt::Checked ?
                tools::date::daysFrom(m_ui->sbExpDays->value(), m_ui->cbExpCount->currentIndex()) :
                0;
}

int FThingEdit::guarantee()
{
    return m_ui->cbGuarantee->checkState() == Qt::Checked ?
                tools::date::daysFrom(m_ui->sbGuarDays->value(), m_ui->cbGuarCount->currentIndex()) :
                0;
}

int FThingEdit::thingType()
{
    if(m_ui->rbService->isChecked())    { return HACC_TAG_ID_SERVICE; }
    if(m_ui->rbObject->isChecked())     { return HACC_TAG_ID_OBJECT; }
    if(m_ui->rbExpendable->isChecked()) { return HACC_TAG_ID_EXPENDABLE; }
    return HACC_TAG_ID_OBJECT;
}

}
}
