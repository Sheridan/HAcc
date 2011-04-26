#include "fcontractoredit.h"
#include "ui_fcontractoredit.h"
#include "ui_defines.h"
#include "st.h"
namespace ui
{
namespace form
{

HACC_STD_TRANSLATE_UI(FContractorEdit, QDialog)

FContractorEdit::FContractorEdit(const bool &isSelf, QWidget *parent) :  QDialog(parent),  m_ui(new Ui::FContractorEdit)
{
    init();
    setObjectName(objectName()+"_new");
    m_accounts = NULL;
    m_ui->lAccounts->hide();
    m_ui->pwIcons->setID(isSelf?9:3);
    m_ui->cbOwnAccount->setChecked(isSelf);
    HACC_RESTORE_DIALOG;
}

FContractorEdit::FContractorEdit(const hacc::TDBID & id, QWidget *parent) :  QDialog(parent),  m_ui(new Ui::FContractorEdit)
{
    init();
    setObjectName(objectName()+"_edit");

    QSqlQuery q = HACC_DB->query("select name, icon_id, own_account from contractors where id=?", QVariantList() << id);
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        m_ui->leName ->setText(HACC_DB_2_STRG(q, 0));
        m_ui->pwIcons->setID  (HACC_DB_2_DBID(q, 1));

        m_accounts = new ui::item::expanded::WExpandedAccountBase(id, this);
        m_accounts->buildUi();
        m_ui->lAccountsLayout->addWidget(m_accounts);
        m_ui->lAccounts->show();
        m_accounts->container()->refresh();

        m_ui->cbOwnAccount->setChecked(HACC_DB_2_BOOL(q, 2));
    }
    HACC_RESTORE_DIALOG;
}

FContractorEdit::~FContractorEdit()
{
    HACC_SAVE_DIALOG;
    delete m_accounts;
    delete m_ui;
}

void FContractorEdit::init()
{
    m_ui->setupUi(this);
}

QString FContractorEdit::name()
{
    return m_ui->leName->text();
}

hacc::TDBID FContractorEdit::iconID()
{
    return m_ui->pwIcons->id();
}

bool FContractorEdit::ownAccount()
{
    return m_ui->cbOwnAccount->checkState() == Qt::Checked;
}

}
}
