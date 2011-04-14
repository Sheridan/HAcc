#include "ftransactiongiftedit.h"
#include "ui_ftransactiongiftedit.h"
#include "ui_defines.h"
#include "st.h"
namespace ui
{
namespace form
{

HACC_STD_TRANSLATE_UI(FTransactionGiftEdit, QDialog)

FTransactionGiftEdit::FTransactionGiftEdit(const int &gType, QWidget *parent) : QDialog(parent), ui(new Ui::FTransactionGiftEdit)
{
    init(gType);
    ui->dtDateTime->setDateTime(QDateTime::currentDateTime());
}

FTransactionGiftEdit::FTransactionGiftEdit(const hacc::TDBID &id, const int &gType, QWidget *parent) : QDialog(parent), ui(new Ui::FTransactionGiftEdit)
{
    init(gType);
}

FTransactionGiftEdit::~FTransactionGiftEdit()
{
    delete ui;
}

void FTransactionGiftEdit::init(const int &gType)
{
    ui->setupUi(this);
    switch(gType)
    {
//    case hacc::model::type::transaction_pool::tptGiftFromMe:
//    {
//        ui->pwThingSelector   ->hide();
//        ui->pwValuableSelector->init();
//        ui->pwAccountFrom->setSelfFilter(hacc::model::ctSelf );
//        ui->pwAccountTo  ->setSelfFilter(hacc::model::ctOther);
//    }
//    break;
//    case hacc::model::type::transaction_pool::tptGiftToMe:
//    {
//        ui->pwThingSelector   ->init();
//        ui->pwValuableSelector->hide();
//        ui->pwAccountFrom->setSelfFilter(hacc::model::ctOther);
//        ui->pwAccountTo  ->setSelfFilter(hacc::model::ctSelf );
//    }
//    break;
    }
}

hacc::TDBID FTransactionGiftEdit::source()
{
    return ui->pwAccountFrom->id();
}

hacc::TDBID FTransactionGiftEdit::destination()
{
    return ui->pwAccountTo->id();
}

hacc::TDBID FTransactionGiftEdit::thing()
{
    return ui->pwThingSelector->id();
}

hacc::TDBID FTransactionGiftEdit::valuable()
{
    return ui->pwValuableSelector->id();
}

QDateTime FTransactionGiftEdit::datetime()
{
    return ui->dtDateTime->dateTime();
}

}
}
