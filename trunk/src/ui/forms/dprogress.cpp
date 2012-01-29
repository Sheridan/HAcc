#include "dprogress.h"
#include "ui_dprogress.h"
#include "ui_defines.h"
#include "st.h"

namespace ui
{
namespace form
{

HACC_STD_TRANSLATE_UI(DProgress, QDialog)

DProgress::DProgress() :
    QDialog(HACC_WINDOW, Qt::SplashScreen),
    m_ui(new Ui::DProgress)
{
    m_ui->setupUi(this);
}

DProgress::~DProgress()
{
    delete m_ui;
}

void DProgress::show(const QString &caption, const int &maximumSteps)
{
    m_ui->m_lCaption->setText(caption);
    m_ui->m_pBar->setMaximum(maximumSteps);
    m_ui->m_pBar->setValue(0);
    QDialog::show();
}

void DProgress::step()
{
    int v = m_ui->m_pBar->value()+1;
    m_ui->m_pBar->setValue(v);
    if(v == m_ui->m_pBar->maximum())
    {
        hide();
    }
}

}
}
