#include "fcontractoredit.h"
#include "ui_fcontractoredit.h"
#include "ui_defines.h"
#include "st.h"
namespace ui
{
namespace form
{

HACC_STD_TRANSLATE_UI(FContractorEdit, QDialog)

FContractorEdit::FContractorEdit(const bool &isSelf, QWidget *parent) :  QDialog(parent),  ui(new Ui::FContractorEdit)
{
    init();
    setObjectName(objectName()+"_new");
    m_accounts = NULL;
    ui->lAccounts->hide();
    ui->pwIcons->setID(isSelf?9:3);
    ui->cbOwnAccount->setChecked(isSelf);
    HACC_RESTORE_DIALOG;
}

FContractorEdit::FContractorEdit(const hacc::TDBID & id, QWidget *parent) :  QDialog(parent),  ui(new Ui::FContractorEdit)
{
    init();
    setObjectName(objectName()+"_edit");

    QSqlQuery q = HACC_DB->query("select name, icon_id, own_account from contractors where id=?", QVariantList() << id);
    if(q.next())
    {
        ui->leName ->setText(HACC_DB_2_STRG(q, 0));
        ui->pwIcons->setID  (HACC_DB_2_DBID(q, 1));

        m_accounts = new ui::item::expanded::WExpandedAccountBase(id, this);
        m_accounts->buildUi();
        ui->lAccountsLayout->addWidget(m_accounts);
        ui->lAccounts->show();
        m_accounts->container()->refresh();

        ui->cbOwnAccount->setChecked(HACC_DB_2_BOOL(q, 2));
    }
    HACC_RESTORE_DIALOG;
}

FContractorEdit::~FContractorEdit()
{
    HACC_SAVE_DIALOG;
    delete m_accounts;
    delete ui;
}

void FContractorEdit::init()
{
    ui->setupUi(this);
}

QString FContractorEdit::name()
{
    return ui->leName->text();
}

hacc::TDBID FContractorEdit::iconId()
{
    return ui->pwIcons->id();
}

bool FContractorEdit::ownAccount()
{
    return ui->cbOwnAccount->checkState() == Qt::Checked;
}

}
}
