#include "doptions.h"
#include "ui_doptions.h"
#include "ui_defines.h"
#include "st.h"

namespace ui
{
namespace form
{

HACC_STD_TRANSLATE_UI(DOptions, QDialog)

DOptions::DOptions(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::DOptions)
{
    m_ui->setupUi(this);
    m_ui->cbMDIFace->setChecked(HACC_OPTIONS->sectionValue("view", "mdi", false).toBool());
}

DOptions::~DOptions()
{
    delete m_ui;
}

void DOptions::on_buttonBox_accepted()
{
    HACC_OPTIONS->setSectionValue("view", "mdi", m_ui->cbMDIFace->checkState() == Qt::Checked);
    accept();
}


}
}
