#include "faccountedit.h"
#include "ui_faccountedit.h"
#include "ui_defines.h"
#include "st.h"
namespace ui
{
namespace form
{
HACC_STD_TRANSLATE_UI(FAccountEdit, QDialog)

FAccountEdit::FAccountEdit(QWidget *parent) : QDialog(parent), m_ui(new Ui::FAccountEdit)
{
    init();
    setObjectName(objectName()+"_new");
    m_ui->pwIcons->setID(2);
    m_ui->pwCurrencySelectButton->setID(1); //! \todo Добавить валюту по умолчанию
    HACC_RESTORE_DIALOG;
}

FAccountEdit::FAccountEdit(const hacc::TDBID & id, QWidget *parent) : QDialog(parent), m_ui(new Ui::FAccountEdit)
{
    init();
    setObjectName(objectName()+"_edit");

    QSqlQuery q = HACC_DB->query("select name, icon_id, currency_id from accounts where id=?", QVariantList() << id);
    q.next();
    m_ui->leName ->setText(HACC_DB_2_STRG(q, 0));
    m_ui->pwIcons->setID  (HACC_DB_2_DBID(q, 1));
    m_ui->pwCurrencySelectButton->setID(HACC_DB_2_DBID(q, 2));

    HACC_RESTORE_DIALOG;
}

FAccountEdit::~FAccountEdit()
{
    HACC_SAVE_DIALOG;
    delete m_ui;
}

void FAccountEdit::init()
{
    m_ui->setupUi(this);
    m_ui->pwCurrencySelectButton->init();
}

QString FAccountEdit::name()
{
    return m_ui->leName->text();
}

hacc::TDBID FAccountEdit::iconId()
{
    return m_ui->pwIcons->id();
}

hacc::TDBID FAccountEdit::currencyID()
{
    return m_ui->pwCurrencySelectButton->id();
}

}
}
