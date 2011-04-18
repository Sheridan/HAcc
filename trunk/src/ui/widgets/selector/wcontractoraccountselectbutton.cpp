#include "wcontractoraccountselectbutton.h"
#include "wcontractoraccountselectpopup.h"
#include "st.h"
namespace ui
{
namespace selector
{

WContractorAccountSelectButton::WContractorAccountSelectButton(QWidget *parent) : base::WSelectorButton(parent)
{
    m_layout = new QHBoxLayout();

    m_contractorIcon = new ui::icons::WIcon(this);
    m_accountIcon    = new ui::icons::WIcon(this);
    m_contractorName = new QLabel(this);
    m_accountName    = new QLabel(this);
    m_contractorName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_accountName   ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    m_layout->addWidget(m_contractorIcon);
    m_layout->addWidget(m_contractorName);
    m_layout->addWidget(m_accountIcon);
    m_layout->addWidget(m_accountName);

    setData(1, tr("Click"), 1, tr("to select"));

    setLayout(m_layout);

    connect(HACC_CONTRACTORS, SIGNAL(created(const hacc::TDBID &)), this, SLOT(contractorCreated(const hacc::TDBID &)));
}

WContractorAccountSelectButton::~WContractorAccountSelectButton()
{
    delete m_contractorIcon;
    delete m_contractorName;
    delete m_accountIcon;
    delete m_accountName;
}

void WContractorAccountSelectButton::idChanged()
{
    /** \todo Отслеживать валюту счета контрагента. Продавец должен выбирать любую валюту, а счета покупателя должны
              выбираться с такойже валютой как и у продавца. Нет валюты такой в счетах - нет покупки.
    */
    QSqlQuery q = HACC_DB->query("select "
                                 "accounts.name,"
                                 "accounts.icon_id,"
                                 "contractors.name,"
                                 "contractors.icon_id "
                                 "from accounts "
                                 "left join contractors on contractors.id=accounts.contractor_id "
                                 "where accounts.id=?",
                                 QVariantList() << id());
    if(q.next())
    {
        setData(HACC_DB_2_DBID(q, 3), HACC_DB_2_STRG(q, 2), HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

void WContractorAccountSelectButton::setData(const hacc::TDBID &contractor_icon, const QString &contractor_name,
                                             const hacc::TDBID &account_icon   , const QString &account_name   )
{
    m_contractorName->setText(contractor_name);
    m_accountName   ->setText(account_name   );
    m_contractorIcon->setIcon(contractor_icon);
    m_accountIcon   ->setIcon(account_icon   );
}

void WContractorAccountSelectButton::setSelfFilter(hacc::model::EContractorFilter filter)
{
    m_filter = filter;
    init();
}

base::WSelectorPopup * WContractorAccountSelectButton::constructPopup()
{
    return new WContractorAccountSelectPopup(m_filter, this);
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
