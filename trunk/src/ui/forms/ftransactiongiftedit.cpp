#include "ftransactiongiftedit.h"
#include "ui_ftransactiongiftedit.h"
#include "ui_defines.h"
#include "st.h"
namespace ui
{
namespace form
{

HACC_STD_TRANSLATE_UI(FTransactionGiftEdit, QDialog)

FTransactionGiftEdit::FTransactionGiftEdit(const int &gType, QWidget *parent) : QDialog(parent), m_ui(new Ui::FTransactionGiftEdit)
{
    init(gType);
    m_ui->dtDateTime->setDateTime(QDateTime::currentDateTime());
}

FTransactionGiftEdit::FTransactionGiftEdit(const hacc::TDBID &id, const int &gType, QWidget *parent) : QDialog(parent), m_ui(new Ui::FTransactionGiftEdit)
{
    init(gType);
}

FTransactionGiftEdit::~FTransactionGiftEdit()
{
    delete m_ui;
}

void FTransactionGiftEdit::init(const int &gType)
{
    m_ui->setupUi(this);
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
    return m_ui->pwAccountFrom->id();
}

hacc::TDBID FTransactionGiftEdit::destination()
{
    return m_ui->pwAccountTo->id();
}

hacc::TDBID FTransactionGiftEdit::thing()
{
    return m_ui->pwThingSelector->id();
}

hacc::TDBID FTransactionGiftEdit::valuable()
{
    return m_ui->pwValuableSelector->id();
}

QDateTime FTransactionGiftEdit::datetime()
{
    return m_ui->dtDateTime->dateTime();
}

}
}
