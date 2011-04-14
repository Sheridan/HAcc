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
    ui(new Ui::FTransactionSellThingEdit)
{
    init();
}

FTransactionSellThingEdit::FTransactionSellThingEdit(const hacc::TDBID &valuableID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FTransactionSellThingEdit)
{
    init();
}

FTransactionSellThingEdit::~FTransactionSellThingEdit()
{
    delete ui;
}

void FTransactionSellThingEdit::init()
{
    ui->setupUi(this);
    ui->pwValuableSelector->init();
}

hacc::TDBID FTransactionSellThingEdit::valuable()
{
    return ui->pwValuableSelector->id();
}

hacc::TMoney FTransactionSellThingEdit::money()
{
    return  tools::convert::stringToMoney(ui->leMoney->text());
}

}
}
