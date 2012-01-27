#include "ftransactionmoneyedit.h"
#include "ui_ftransactionmoneyedit.h"
#include "ui_defines.h"
#include "convert.h"
#include "st.h"

namespace ui
{
namespace form
{

HACC_STD_TRANSLATE_UI(FTransactionMoneyEdit, QDialog);

FTransactionMoneyEdit::FTransactionMoneyEdit(const int &trType, QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::FTransactionMoneyEdit)
{
    init(trType);
    m_ui->dtDateTime->setDateTime(QDateTime::currentDateTime());
}

FTransactionMoneyEdit::FTransactionMoneyEdit(const hacc::TDBID &id, const int &trType, QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::FTransactionMoneyEdit)
{
    m_baseTransactionID = 0;
    m_commissionTransactionID = 0;
    m_basePoolID = id;
    m_commissionPoolID = 0;
    m_transactionPoolType = trType;
    if(m_transactionPoolType == HACC_TAG_ID_COMMISSION)
    {
        QSqlQuery qp = HACC_DB->query(QString("select "
                                     "transaction_pools_tags.tag_id, "
                                     "transaction_pool.id "
                                     "from transactions "
                                     "left join  transactions_commisions on transactions_commisions.id=transactions.id "
                                     "left join  transaction_pool on transaction_pool.id=transactions_commisions.base_pool_id "
                                     "left join transaction_pools_tags on transaction_pools_tags.transaction_pool_id = transaction_pool.id "
                                     "where transactions.pool_id=? and transaction_pools_tags.tag_id in (%0, %1, %2)")
                                     .arg(HACC_TAG_ID_INCOMING)
                                     .arg(HACC_TAG_ID_OUTGOING)
                                     .arg(HACC_TAG_ID_TRANSFER),
                                     QVariantList() << id);
        if(HACC_QUERY_DATA_AVIALABLE(qp))
        {
            //! \todo Добавить действие, если запрос не вернет данных
            m_basePoolID          = HACC_DB_2_DBID(qp, 1);
            m_transactionPoolType = HACC_DB_2_TYPE(qp, 0);
        }
    }

    QSqlQuery q = HACC_DB->query("select "
                           /*0*/ "base_tp.date_time as tr_date_time, "
                           /*1*/ "base_tp.source_account_id as base_tp_source_account_id, "
                           /*2*/ "base_tp.destination_account_id as base_tp_destination_account_id, "
                           /*3*/ "comm_t.pool_id as comm_tp_id, "
                           /*4*/ "base_t.money as base_money, "
                           /*5*/ "transactions_commisions.commission_value, "
                           /*6*/ "transactions_commisions.commission_to_id, "
                           /*7*/ "transactions_commisions.commission_value_is_percent, "
                           /*8*/ "transactions_commisions.commission_already_in_money, "
                           /*9*/ "transactions_commisions.commission_value, "
                           /*10*/"comm_t.id as comm_t_id, "
                           /*11*/"base_t.id as base_t_id "
                                 "from transaction_pool base_tp "
                                 "left join transactions base_t on base_t.pool_id = base_tp.id "
                                 "left join transactions_commisions on transactions_commisions.base_pool_id = base_tp.id "
                                 "left join transactions comm_t on comm_t.id = transactions_commisions.id "
                                 "where base_tp.id=?", QVariantList() << m_basePoolID);
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        init(m_transactionPoolType);
        m_baseTransactionID = HACC_DB_2_DBID(q, 11);
        m_ui->dtDateTime->setDateTime(HACC_DB_2_DATI(q, 0));
        m_ui->leMoney->setText(tools::convert::moneyToString(HACC_DB_2_MONY(q, 4)));
        bool thisHasCommission = !q.value(5).isNull();
        m_ui->gbCommission->setChecked(thisHasCommission);
        if(thisHasCommission)
        {
            m_commissionTransactionID = HACC_DB_2_DBID(q, 10);
            m_commissionPoolID = HACC_DB_2_DBID(q, 3);
            m_ui->leCommission->setText(tools::convert::moneyToString(HACC_DB_2_MONY(q, 9)));
            m_ui->cbCommisionInMoney->setChecked(HACC_DB_2_BOOL(q, 8));
            m_ui->pwCommissionTo->setID(HACC_DB_2_DBID(q, 6));
            m_ui->cbPercent->setChecked(HACC_DB_2_BOOL(q, 7));
        }
        m_ui->pwAccountFrom->setID(HACC_DB_2_DBID(q, 1));
        m_ui->pwAccountTo->setID(HACC_DB_2_DBID(q, 2));
    }
}

FTransactionMoneyEdit::~FTransactionMoneyEdit()
{
    delete m_ui;
}

void FTransactionMoneyEdit::init(const int &trType)
{
    m_ui->setupUi(this);
    m_ui->pwCommissionTo->setSelfFilter(hacc::model::ctAll);
    switch(trType)
    {
        case HACC_TAG_ID_TRANSFER:
        {
            m_ui->pwAccountFrom->setSelfFilter(hacc::model::ctSelf);
            m_ui->pwAccountTo->setSelfFilter(hacc::model::ctSelf);
        }
        break;
        case HACC_TAG_ID_INCOMING:
        {
            m_ui->pwAccountFrom->setSelfFilter(hacc::model::ctOther);
            m_ui->pwAccountTo->setSelfFilter(hacc::model::ctSelf);
        }
        break;
        case HACC_TAG_ID_OUTGOING:
        {
            m_ui->pwAccountFrom->setSelfFilter(hacc::model::ctSelf);
            m_ui->pwAccountTo->setSelfFilter(hacc::model::ctOther);
        }
        break;
    default: break;
    }


}

hacc::TDBID FTransactionMoneyEdit::sourceAccountID()
{
    return m_ui->pwAccountFrom->id();
}

hacc::TDBID FTransactionMoneyEdit::destinationAccountID()
{
    return m_ui->pwAccountTo->id();
}

hacc::TMoney FTransactionMoneyEdit::money()
{
    return tools::convert::stringToMoney(m_ui->leMoney->text());
}

QDateTime FTransactionMoneyEdit::datetime()
{
    return m_ui->dtDateTime->dateTime();
}

hacc::TMoney FTransactionMoneyEdit::commission()
{
    return tools::convert::stringToMoney(m_ui->leCommission->text());
}

bool FTransactionMoneyEdit::hasCommission()
{
    return m_ui->gbCommission->isChecked();
}

bool FTransactionMoneyEdit::commissionInPercents()
{
    return m_ui->cbPercent->isChecked();
}

bool FTransactionMoneyEdit::commissionAlreadyInMoney()
{
    return m_ui->cbCommisionInMoney->isChecked();
}

hacc::TDBID FTransactionMoneyEdit::commissionTo()
{
    return m_ui->pwCommissionTo->id();
}

hacc::TDBID FTransactionMoneyEdit::basePoolID()
{
    return m_basePoolID;
}

hacc::TDBID FTransactionMoneyEdit::commissionPoolID()
{
    return m_commissionPoolID;
}

int FTransactionMoneyEdit::transactionPoolType()
{
    return m_transactionPoolType;
}

hacc::TDBID FTransactionMoneyEdit::commissionTransactionID()
{
    return m_commissionTransactionID;
}

hacc::TDBID FTransactionMoneyEdit::baseTransactionID()
{
    return m_baseTransactionID;
}

}
}
