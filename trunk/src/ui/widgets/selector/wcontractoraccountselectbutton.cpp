#include "wcontractoraccountselectbutton.h"
#include "wcontractoraccountselectpopup.h"
#include "st.h"
namespace ui
{
namespace selector
{

WContractorAccountSelectButton::WContractorAccountSelectButton(QWidget *parent) : base::WSelectorButton(parent)
{
    m_popup = NULL;
    m_currencyID = 0;

    m_layout = new QHBoxLayout();

    m_contractorIcon = new ui::icons::WIcon(this);
    m_accountIcon    = new ui::icons::WIcon(this);
    m_currencytIcon  = new ui::icons::WIcon(this);
    m_contractorName = new QLabel(this);
    m_accountName    = new QLabel(this);
    m_currencyName   = new QLabel(this);
    m_contractorName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_accountName   ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_currencyName  ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    m_layout->addWidget(m_contractorIcon);
    m_layout->addWidget(m_contractorName);
    m_layout->addWidget(m_accountIcon);
    m_layout->addWidget(m_accountName);
    m_layout->addWidget(m_currencytIcon);
    m_layout->addWidget(m_currencyName);

    setData(1, tr("Click"), 1, tr("to"), 1, tr("select"));

    setLayout(m_layout);

    connect(HACC_CONTRACTORS, SIGNAL(created(const hacc::TDBID &)), this, SLOT(contractorCreated(const hacc::TDBID &)));
}

WContractorAccountSelectButton::~WContractorAccountSelectButton()
{
    delete m_contractorIcon;
    delete m_contractorName;
    delete m_accountIcon;
    delete m_accountName;
    delete m_currencytIcon;
    delete m_currencyName;
}

void WContractorAccountSelectButton::idChanged()
{
    QSqlQuery q = HACC_DB->query("select "
                          /* 0*/ "accounts.name, "
                          /* 1*/ "accounts.icon_id, "
                          /* 2*/ "contractors.name, "
                          /* 3*/ "contractors.icon_id, "
                          /* 4*/ "currencyes.name, "
                          /* 5*/ "currencyes.icon_id, "
                          /* 6*/ "currencyes.id "
                                 "from accounts "
                                 "left join contractors on contractors.id=accounts.contractor_id "
                                 "left join currencyes on currencyes.id=accounts.currency_id "
                                 "where accounts.id=?",
                                 QVariantList() << id());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setData(
                HACC_DB_2_DBID(q, 3),
                HACC_DB_2_STRG(q, 2),
                HACC_DB_2_DBID(q, 1),
                HACC_DB_2_STRG(q, 0),
                HACC_DB_2_DBID(q, 5),
                HACC_DB_2_STRG(q, 4)
               );
        emit currencyIDChanged(HACC_DB_2_DBID(q, 6));
    }
}

void WContractorAccountSelectButton::setData(const hacc::TDBID &contractorIconID, const QString &contractorName,
                                             const hacc::TDBID &accountIconID   , const QString &accountName   ,
                                             const hacc::TDBID &currencyIconID  , const QString &currencyName)
{
    m_contractorName->setText(contractorName  );
    m_accountName   ->setText(accountName     );
    m_currencyName  ->setText(currencyName    );
    m_contractorIcon->setIcon(contractorIconID);
    m_accountIcon   ->setIcon(accountIconID   );
    m_currencytIcon ->setIcon(currencyIconID  );
}

void WContractorAccountSelectButton::setSelfFilter(hacc::model::EContractorFilter filter)
{
    m_filter = filter;
    init();
}

void WContractorAccountSelectButton::setCurrencyFilter(const hacc::TDBID &currencyID)
{
    m_currencyID = currencyID;
    if(m_popup)
    {
        static_cast<WContractorAccountSelectPopup *>(m_popup)->setCurrencyFilter(m_currencyID);
    }
}

base::WSelectorPopup * WContractorAccountSelectButton::constructPopup()
{
    //! \todo Чегото слишком дохуя шагов setCurrencyFilter надо чтобы добраться до испонителя. Архитектуру бы подумать...
    m_popup = new WContractorAccountSelectPopup(m_filter, this);
    static_cast<WContractorAccountSelectPopup *>(m_popup)->setCurrencyFilter(m_currencyID);
    return m_popup;
}

void WContractorAccountSelectButton::contractorCreated(const hacc::TDBID &contractorID)
{
    bool isOwn = HACC_DB->queryCell("select own_account from contractors where id=?",
                                    false,
                                    QVariantList() << contractorID).toBool();
    if( ( isOwn && m_filter == hacc::model::ctSelf ) ||
        (!isOwn && m_filter == hacc::model::ctOther) )
    {
        setID(contractorID);
    }
}

}
}
