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
    m_ui(new Ui::FTagEdit)
{
    m_ui->setupUi(this);
    setObjectName(objectName()+"_new");
}

FTagEdit::FTagEdit(const hacc::TDBID &id, QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::FTagEdit)
{
    m_ui->setupUi(this);
    setObjectName(objectName()+"_edit");
    m_ui->leName->setText(HACC_TAGS->tagName(id));
}

FTagEdit::~FTagEdit()
{
    delete m_ui;
}

QString FTagEdit::name()
{
    return m_ui->leName->text();
}

}
}
