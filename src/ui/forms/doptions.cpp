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
    ui(new Ui::DOptions)
{
    ui->setupUi(this);
    ui->cbMDIFace->setChecked(HACC_OPTIONS->sectionValue("view", "mdi", false).toBool());
}

DOptions::~DOptions()
{
    delete ui;
}

void DOptions::on_buttonBox_accepted()
{
    HACC_OPTIONS->setSectionValue("view", "mdi", ui->cbMDIFace->checkState() == Qt::Checked);
    accept();
}


}
}
