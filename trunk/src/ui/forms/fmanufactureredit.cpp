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
    m_ui(new Ui::FManufacturerEdit)
{
   init();
   setObjectName(objectName()+"_new");
   m_ui->lLogo->clear();
   m_ui->pwIcons->setID(11);
   HACC_RESTORE_DIALOG;
}

FManufacturerEdit::FManufacturerEdit(const hacc::TDBID &id, QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::FManufacturerEdit)
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
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        m_ui->leName ->setText(HACC_DB_2_STRG(q, 0));
        m_ui->pwIcons->setID  (HACC_DB_2_DBID(q, 1));
        m_ui->teDescription->appendPlainText(HACC_DB_2_STRG(q, 2));
        m_ui->lLogo->setPixmap(ui::images::byteArray2Pixmap(q.value(3).toByteArray()), 128);
    }
    HACC_RESTORE_DIALOG;
}

FManufacturerEdit::~FManufacturerEdit()
{
    HACC_SAVE_DIALOG;
    delete m_ui;
}

void FManufacturerEdit::init()
{
    m_ui->setupUi(this);
    m_ui->lLogo->setEmptyText(tr("No image"));
}

void FManufacturerEdit::on_tbLoadLogo_clicked()
{
    m_ui->lLogo->clear();
    tools::dialog::SFileDialogResult dlgResult =
            tools::dialog::CFileDialogs::getOpenImage(tr("Open image"));
    if(dlgResult.dialogOk && !dlgResult.fileNames[0].isEmpty())
    {
        QPixmap *pm = new QPixmap(dlgResult.fileNames[0]);
        m_ui->lLogo->setPixmap(pm->scaled(QSize(128,128), Qt::KeepAspectRatio, Qt::SmoothTransformation), 128);
        delete pm;
    }
}

void FManufacturerEdit::on_tbClearLogo_clicked()
{
    m_ui->lLogo->clear();
}

QString FManufacturerEdit::name()
{
    return m_ui->leName->text();
}

QString FManufacturerEdit::description()
{
    return m_ui->teDescription->toPlainText();
}

hacc::TDBID FManufacturerEdit::iconID()
{
    return m_ui->pwIcons->id();
}

QByteArray FManufacturerEdit::pixmapData()
{
    return ui::images::pixmap2ByteArray(m_ui->lLogo->pixmap());
}

bool FManufacturerEdit::hasImage()
{
    return !m_ui->lLogo->empty();
}

}
}

