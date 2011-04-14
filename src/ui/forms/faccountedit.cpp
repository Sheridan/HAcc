#include "faccountedit.h"
#include "ui_faccountedit.h"
#include "ui_defines.h"
#include "st.h"
namespace ui
{
namespace form
{
HACC_STD_TRANSLATE_UI(FAccountEdit, QDialog)

FAccountEdit::FAccountEdit(QWidget *parent) : QDialog(parent), ui(new Ui::FAccountEdit)
{
    init();
    setObjectName(objectName()+"_new");
    ui->pwIcons->setID(2);
    HACC_RESTORE_DIALOG;
}

FAccountEdit::FAccountEdit(const hacc::TDBID & id, QWidget *parent) : QDialog(parent), ui(new Ui::FAccountEdit)
{
    init();
    setObjectName(objectName()+"_edit");

    QSqlQuery q = HACC_DB->query("select name, icon_id from accounts where id=?", QVariantList() << id);
    q.next();
    ui->leName ->setText(HACC_DB_2_STRG(q, 0));
    ui->pwIcons->setID  (HACC_DB_2_DBID(q, 1));
    HACC_RESTORE_DIALOG;
}

FAccountEdit::~FAccountEdit()
{
    HACC_SAVE_DIALOG;
    delete ui;
}

void FAccountEdit::init()
{
    ui->setupUi(this);
}

QString FAccountEdit::name()
{
    return ui->leName->text();
}

hacc::TDBID FAccountEdit::iconId()
{
    return ui->pwIcons->id();
}

}
}
