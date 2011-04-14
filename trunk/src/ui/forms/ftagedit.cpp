#include "ftagedit.h"
#include "ui_ftagedit.h"
#include "ui_defines.h"
#include "st.h"

namespace ui
{
namespace form
{

HACC_STD_TRANSLATE_UI(FTagEdit, QDialog)

FTagEdit::FTagEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FTagEdit)
{
    ui->setupUi(this);
    setObjectName(objectName()+"_new");
}

FTagEdit::FTagEdit(const hacc::TDBID &id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FTagEdit)
{
    ui->setupUi(this);
    setObjectName(objectName()+"_edit");
    ui->leName->setText(HACC_TAGS->tagName(id));
}

FTagEdit::~FTagEdit()
{
    delete ui;
}

QString FTagEdit::name()
{
    return ui->leName->text();
}

}
}
