#include "fitemtagsedit.h"
#include "ui_fitemtagsedit.h"
#include "ui_defines.h"
#include "st.h"

namespace ui
{
namespace form
{

HACC_STD_TRANSLATE_UI(FItemTagsEdit, QDialog)

FItemTagsEdit::FItemTagsEdit(const hacc::TDBID &id, QWidget *parent)
    : QDialog(parent),
      hacc::CIDItem(id),
      ui(new Ui::FItemTagsEdit)
{
    ui->setupUi(this);
    m_container = NULL;
}

FItemTagsEdit::~FItemTagsEdit()
{
    delete m_container;
    delete ui;
}

int FItemTagsEdit::exec()
{
    m_container = constructContainer();
    m_container->setEditMode(true);
    m_container->refresh();
    ui->containerLayout->addWidget(m_container);
    ui->tbTagAdd->setDefaultAction(HACC_TAGS->addAction());
    connect(ui->pbOk,     SIGNAL(clicked()), m_container, SLOT(accept()));
    connect(ui->pbApply,  SIGNAL(clicked()), m_container, SLOT(commit()));
    connect(ui->pbRevert, SIGNAL(clicked()), m_container, SLOT(refresh()));
    connect(ui->leSearch, SIGNAL(textChanged(QString)), m_container, SLOT(setSearchText(QString)));
    return QDialog::exec();
}

}
}
