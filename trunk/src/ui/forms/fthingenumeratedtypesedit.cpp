#include "fthingenumeratedtypesedit.h"
#include "ui_fthingenumeratedtypesedit.h"
#include "ui_defines.h"
#include "st.h"

namespace ui
{
namespace form
{

HACC_STD_TRANSLATE_UI(FThingEnumeratedTypesEdit, QDialog)

FThingEnumeratedTypesEdit::FThingEnumeratedTypesEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FThingEnumeratedTypesEdit)
{
    init();
    setObjectName(objectName()+"_new");
    HACC_RESTORE_DIALOG;
}

FThingEnumeratedTypesEdit::FThingEnumeratedTypesEdit(const hacc::TDBID &id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FThingEnumeratedTypesEdit)
{
    init();
    setObjectName(objectName()+"_edit");
    QSqlQuery q = HACC_DB->query("select name, precision "
                                 "from thing_enumerated_types where id=?",
                                 QVariantList() << id);
    if(q.next())
    {
        ui->leName ->setText(HACC_DB_2_STRG(q, 0));
        ui->sbPrecision->setValue(HACC_DB_2_PREC(q, 1));
    }
    HACC_RESTORE_DIALOG;
}

void FThingEnumeratedTypesEdit::init()
{
    ui->setupUi(this);
}

FThingEnumeratedTypesEdit::~FThingEnumeratedTypesEdit()
{
    HACC_SAVE_DIALOG;
    delete ui;
}

QString FThingEnumeratedTypesEdit::name()
{
    return ui->leName->text();
}

int FThingEnumeratedTypesEdit::precision()
{
    return ui->sbPrecision->value();
}

}
}
