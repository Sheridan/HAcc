#include "ftransactionpoolthingedit.h"
#include "ui_ftransactionpoolthingedit.h"
#include "wexpandedtransactionthingbuybase.h"
#include "wexpandedtransactionthingsellbase.h"
#include "ui_defines.h"
#include "st.h"

namespace ui
{
namespace form
{

HACC_STD_TRANSLATE_UI(FTransactionPoolThingEdit, QDialog)

FTransactionPoolThingEdit::FTransactionPoolThingEdit(int poolType, QWidget *parent)
    : QDialog(parent),
      m_ui(new Ui::FTransactionPoolThingEdit)
{
    m_type = poolType;
    m_transactions = constructContainer();
    init();
    m_ui->dtDateTime->setDateTime(QDateTime::currentDateTime());
}

FTransactionPoolThingEdit::FTransactionPoolThingEdit(const hacc::TDBID &id, int poolType, QWidget *parent) : QDialog(parent), m_ui(new Ui::FTransactionPoolThingEdit)
{
    m_type = poolType;
    m_transactions = constructContainer(id);
    init();
    QSqlQuery q = HACC_DB->query("select "
                                 "transactions_pool.date_time, "
                                 "transactions_pool.source_account_id, "
                                 "transactions_pool.destination_account_id "
                                 "from transactions_pool "
                                 "where transactions_pool.id=?",
                                 QVariantList() << id);
    if(q.next())
    {
        m_ui->dtDateTime->setDateTime(HACC_DB_2_DATI(q, 0));
        m_ui->pwBuyerAccount  ->setID(HACC_DB_2_DBID(q, 1));
        m_ui->pwSellerAccount ->setID(HACC_DB_2_DBID(q, 2));
    }
    m_transactions->container()->refresh();
}

FTransactionPoolThingEdit::~FTransactionPoolThingEdit()
{
    delete m_ui;
    delete m_transactions;
}

ui::item::base::WBase *FTransactionPoolThingEdit::constructContainer(const hacc::TDBID &id)
{
    switch(m_type)
    {
        case HACC_TAG_ID_SELLING: { return id
                 ? (new ui::item::expanded::WExpandedTransactionThingSellBase(id, this))
                 : (new ui::item::expanded::WExpandedTransactionThingSellBase(this)); }
        case HACC_TAG_ID_BUYING : { return id
                ? (new ui::item::expanded::WExpandedTransactionThingBuyBase (id, this))
                : (new ui::item::expanded::WExpandedTransactionThingBuyBase (this)); }
    }
    return NULL;
}

void FTransactionPoolThingEdit::init()
{
    m_ui->setupUi(this);
    m_transactions->buildUi();
    m_ui->dialogLayout->insertWidget(m_ui->dialogLayout->count()-1, m_transactions);
    switch(m_type)
    {
        case HACC_TAG_ID_SELLING:
        {
            m_ui->pwBuyerAccount ->setSelfFilter(hacc::model::ctOther);
            m_ui->pwSellerAccount->setSelfFilter(hacc::model::ctSelf);
        }
        break;
        case HACC_TAG_ID_BUYING:
        {
            m_ui->pwBuyerAccount ->setSelfFilter(hacc::model::ctSelf);
            m_ui->pwSellerAccount->setSelfFilter(hacc::model::ctOther);
        }
        break;
    }
}

hacc::TDBID FTransactionPoolThingEdit::buyerAccountID()      // account id
{
    return m_ui->pwBuyerAccount->id();
}

hacc::TDBID FTransactionPoolThingEdit::sellerAccountID() // account id
{
    return m_ui->pwSellerAccount->id();
}

QDateTime FTransactionPoolThingEdit::datetime()
{
    return m_ui->dtDateTime->dateTime();
}

}
}
