#include "ftransactionsellthingedit.h"
#include "ui_ftransactionsellthingedit.h"
#include "ui_defines.h"
#include "convert.h"
#include "st.h"

namespace ui
{
namespace form
{

HACC_STD_TRANSLATE_UI(FTransactionSellThingEdit, QDialog);

FTransactionSellThingEdit::FTransactionSellThingEdit(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::FTransactionSellThingEdit)
{
    init();
}

FTransactionSellThingEdit::FTransactionSellThingEdit(const hacc::TDBID &valuableID, QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::FTransactionSellThingEdit)
{
    init();
}

FTransactionSellThingEdit::~FTransactionSellThingEdit()
{
    delete m_ui;
}

void FTransactionSellThingEdit::init()
{
    m_ui->setupUi(this);
    m_ui->pwValuableSelector->init();
}

hacc::TDBID FTransactionSellThingEdit::valuable()
{
    return m_ui->pwValuableSelector->id();
}

hacc::TMoney FTransactionSellThingEdit::money()
{
    return  tools::convert::stringToMoney(m_ui->leMoney->text());
}

}
}
