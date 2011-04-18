#include "wcurrencyelectbutton.h"
#include "wcurrencyselectpopup.h"
#include "st.h"

namespace ui
{
namespace selector
{

WCurrencyelectButton::WCurrencyelectButton(QWidget *parent) : base::WSelectorButton(parent)
{
    m_layout = new QHBoxLayout();

    m_currencyIcon = new ui::icons::WIcon(16, this);
    m_currencyName = new QLabel(this);

    m_layout->addWidget(m_currencyIcon);
    m_layout->addWidget(m_currencyName);

    setCurrencyData(1, tr("Click to select"), "-");

    setLayout(m_layout);

    connect(HACC_CURRENCYES, SIGNAL(created(const hacc::TDBID &)), this, SLOT(currencyCreated(const hacc::TDBID &)));
}

WCurrencyelectButton::~WCurrencyelectButton()
{
    delete m_currencyName;
    delete m_currencyIcon;
    delete m_layout;
}

void WCurrencyelectButton::idChanged()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id, reduction from currencyes where id=?",
                                 QVariantList() << id());
    if(q.next())
    {
        setCurrencyData(HACC_DB_2_DBID(q, 1),
                        HACC_DB_2_STRG(q, 0),
                        HACC_DB_2_STRG(q, 2));
    }
}

base::WSelectorPopup * WCurrencyelectButton::constructPopup()
{
    return new WCurrencySelectPopup(this);
}

void WCurrencyelectButton::setCurrencyData(const hacc::TDBID &iconID, const QString &name, const QString &reduction)
{
    m_currencyName->setText(QString("%0 (%1)").arg(name).arg(reduction));
    m_currencyIcon->setIcon(iconID);
}

void WCurrencyelectButton::currencyCreated(const hacc::TDBID &currencyID)
{
    setID(currencyID);
}

}
}
