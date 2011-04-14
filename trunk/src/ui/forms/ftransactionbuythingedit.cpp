#include "ftransactionbuythingedit.h"
#include "ui_ftransactionbuythingedit.h"
#include "ui_defines.h"
#include "convert.h"
#include "st.h"

namespace ui
{
namespace form
{

HACC_STD_TRANSLATE_UI(FTransactionBuyThingEdit, QDialog);

FTransactionBuyThingEdit::FTransactionBuyThingEdit(QWidget *parent) : QDialog(parent), ui(new Ui::FTransactionBuyThingEdit)
{
    init();
    m_minimumAmount = 0.00001;
}

FTransactionBuyThingEdit::FTransactionBuyThingEdit(const hacc::TDBID &id, QWidget *parent) : QDialog(parent), ui(new Ui::FTransactionBuyThingEdit)
{
    init();
     m_minimumAmount = 0.00001;
    QSqlQuery q = HACC_DB->query("select "
                          /* 0*/ "transactions_things.thing_id, "
                          /* 1*/ "transactions.money, "
                          /* 2*/ "transactions_things.amount, "
                          /* 3*/ "thing_enumerated_types.precision, "
                          /* 4*/ "things.enumerated_type_id "
                                 "from transactions "
                                 "left join transactions_things on transactions_things.id=transactions.id "
                                 "left join things on things.id=transactions_things.thing_id "
                                 "left join thing_enumerated_types on thing_enumerated_types.id=things.enumerated_type_id "
                                 "where transactions.id=?",
                                 QVariantList() << id);
    if(q.next())
    {
        ui->leMoney ->setText(tools::convert::moneyToString(HACC_DB_2_MONY(q, 1)));
        ui->leAmount->setText(tools::convert::amountToString(HACC_DB_2_AMNT(q, 2), HACC_DB_2_PREC(q, 3)));
        ui->pwThingSelector->setID(HACC_DB_2_DBID(q, 0));
        if(HACC_ENUMERATED_THING_TYPES->checkDivisibleEnumeratedType(HACC_DB_2_DBID(q, 4)))
        {
            m_minimumAmount = HACC_DB_2_AMNT(q, 2) - HACC_VALUABLES->listVithoutMoving("valuables.transaction_id=?", QVariantList() << id).count();
            if(m_minimumAmount == 0)
            {
                m_minimumAmount = 1;
            }
        }
    }
}

void FTransactionBuyThingEdit::init()
{
    ui->setupUi(this);
    ui->pwThingSelector->init();
    connect(ui->leAmount, SIGNAL(textChanged(QString)), this, SLOT(validateData()));
    connect(ui->leMoney, SIGNAL(textChanged(QString)), this, SLOT(validateData()));
    connect(ui->pwThingSelector, SIGNAL(selected(hacc::TDBID)), this, SLOT(validateData()));
}

FTransactionBuyThingEdit::~FTransactionBuyThingEdit()
{
    delete ui;
}

void FTransactionBuyThingEdit::validateData()
{
    ui->pbOk->setEnabled
            (
                amount() >= m_minimumAmount &&
                money()  >= 0 &&
                ui->pwThingSelector->id()
            );
}

void FTransactionBuyThingEdit::on_tbClearMoney_clicked () { ui->leMoney ->setText("0.00"); }
void FTransactionBuyThingEdit::on_tbClearAmount_clicked() { ui->leAmount->setText("0.00"); }
hacc::TDBID   FTransactionBuyThingEdit::thing () { return ui->pwThingSelector->id(); }
hacc::TMoney  FTransactionBuyThingEdit::money () { return tools::convert::stringToMoney( ui->leMoney ->text()); }
hacc::TAmount FTransactionBuyThingEdit::amount() { return tools::convert::stringToAmount(ui->leAmount->text()); }

}
}
