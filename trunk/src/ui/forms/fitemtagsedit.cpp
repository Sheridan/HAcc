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
      m_ui(new Ui::FItemTagsEdit)
{
    m_ui->setupUi(this);
    m_container = NULL;
}

FItemTagsEdit::~FItemTagsEdit()
{
    delete m_container;
    delete m_ui;
}

int FItemTagsEdit::exec()
{
    m_container = constructContainer();
    m_container->setEditMode(true);
    m_container->refresh();
    m_ui->containerLayout->addWidget(m_container);
    m_ui->tbTagAdd->setDefaultAction(HACC_TAGS->addAction());
    connect(m_ui->pbOk,     SIGNAL(clicked()), m_container, SLOT(accept()));
    connect(m_ui->pbApply,  SIGNAL(clicked()), m_container, SLOT(commit()));
    connect(m_ui->pbRevert, SIGNAL(clicked()), m_container, SLOT(refresh()));
    connect(m_ui->leSearch, SIGNAL(textChanged(QString)), m_container, SLOT(setSearchText(QString)));
    return QDialog::exec();
}

}
}
