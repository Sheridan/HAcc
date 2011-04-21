#include "doptions.h"
#include "ui_doptions.h"
#include "ui_defines.h"
#include "st.h"
#include "hacc_options.h"

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
    m_ui->pwCurrencySelectButton->init();
    m_ui->pwCurrencySelectButton->setID(HACC_O_DEFAULT_CURRENCY);

    connect(m_ui->pwCurrencySelectButton, SIGNAL(selected(const hacc::TDBID &)), this, SLOT(defaultCurrencySet(const hacc::TDBID &)));
}

DOptions::~DOptions()
{
    delete m_ui;
}

void DOptions::defaultCurrencySet(const hacc::TDBID &currencyID)
{
    HACC_O_DEFAULT_CURRENCY_SET(currencyID);
}

}
}
