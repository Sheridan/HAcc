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
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
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

/**
   Доступные счета продавцов фильтруются по валюте счета покупателя. (connect(...currencyIDChanged...setCurrencyFilter...))
   \todo Организовать сброс значения, если у продавца выбрана валюта раньше покупателя, а покупатель выбрал другую валюту
  */
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
            connect(m_ui->pwSellerAccount, SIGNAL(currencyIDChanged(const hacc::TDBID &)),
                    m_ui->pwBuyerAccount, SLOT(setCurrencyFilter(const hacc::TDBID &)));
        }
        break;
        case HACC_TAG_ID_BUYING:
        {
            m_ui->pwBuyerAccount ->setSelfFilter(hacc::model::ctSelf);
            m_ui->pwSellerAccount->setSelfFilter(hacc::model::ctOther);
            connect(m_ui->pwBuyerAccount, SIGNAL(currencyIDChanged(const hacc::TDBID &)),
                    m_ui->pwSellerAccount, SLOT(setCurrencyFilter(const hacc::TDBID &)));
        }
        break;
    }
}

hacc::TDBID FTransactionPoolThingEdit::buyerAccountID()
{
    return m_ui->pwBuyerAccount->id();
}

hacc::TDBID FTransactionPoolThingEdit::sellerAccountID()
{
    return m_ui->pwSellerAccount->id();
}

QDateTime FTransactionPoolThingEdit::datetime()
{
    return m_ui->dtDateTime->dateTime();
}

}
}
