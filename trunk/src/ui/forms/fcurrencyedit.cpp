#include "fcurrencyedit.h"
#include "ui_fcurrencyedit.h"
#include "ui_defines.h"
#include "st.h"
namespace ui
{
namespace form
{

HACC_STD_TRANSLATE_UI(FCurrencyEdit, QDialog)

FCurrencyEdit::FCurrencyEdit(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::FCurrencyEdit)
{
    init();
}

FCurrencyEdit::FCurrencyEdit(const hacc::TDBID &currencyID, QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::FCurrencyEdit)
{
    init();
    QSqlQuery q = HACC_DB->query("select name, icon_id, reduction, show_reduction_before_value from currencyes where id=?",
                                 QVariantList() << currencyID);
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        m_ui->leName->setText(HACC_DB_2_STRG(q, 0));
        m_ui->pwIcons->setID(HACC_DB_2_DBID(q, 1));
        m_ui->leReduction->setText(HACC_DB_2_STRG(q, 2));
        m_ui->cbReductionBeforeNumber->setChecked(HACC_DB_2_BOOL(q, 3));
    }
}

FCurrencyEdit::~FCurrencyEdit()
{
    delete m_ui;
}

void FCurrencyEdit::init()
{
    m_ui->setupUi(this);
}

QString FCurrencyEdit::name()
{
    return m_ui->leName->text();
}

QString FCurrencyEdit::reduction()
{
    return m_ui->leReduction->text();
}

bool FCurrencyEdit::reductionBeforeNumber()
{
    return m_ui->cbReductionBeforeNumber->isChecked();
}

hacc::TDBID FCurrencyEdit::iconID()
{
    return m_ui->pwIcons->id();
}


}
}
