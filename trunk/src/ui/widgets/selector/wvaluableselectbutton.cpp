#include "wvaluableselectbutton.h"
#include "wvaluableselectpopup.h"
#include "st.h"

namespace ui
{
namespace selector
{

WValuableSelectButton::WValuableSelectButton(QWidget *parent) : base::WSelectorButton(parent)
{
    m_layout = new QHBoxLayout();

    m_thingIcon = new ui::icons::WIcon(16, this);
    m_thingName = new QLabel(this);
    m_manufacturerIcon = new ui::icons::WIcon(16, this);
    m_manufacturerName = new QLabel(this);
    m_serialNumber     = new QLabel(this);

    m_layout->addWidget(m_thingIcon);
    m_layout->addWidget(m_thingName);
    m_layout->addWidget(m_manufacturerIcon);
    m_layout->addWidget(m_manufacturerName);
    m_layout->addWidget(m_serialNumber);

    setThingData       (1, tr("Click"));
    setManufacturerData(1, tr("to"));
    setValuableData    (tr("select"));

    setLayout(m_layout);

    connect(HACC_VALUABLES, SIGNAL(created(const hacc::TDBID &)), this, SLOT(valuableCreated(const hacc::TDBID &)));
}

WValuableSelectButton::~WValuableSelectButton()
{
    delete m_thingName;
    delete m_thingIcon;
    delete m_manufacturerName;
    delete m_manufacturerIcon;
    delete m_serialNumber;
    delete m_layout;
}

void WValuableSelectButton::idChanged()
{
    QSqlQuery q = HACC_DB->query("select "
                           /*0*/ "things.name, "
                           /*1*/ "things.icon_id, "
                           /*2*/ "manufacturers.name, "
                           /*3*/ "manufacturers.icon_id, "
                           /*4*/ "valuables.serial_number "
                                 "from things "
                                 "left join manufacturers on manufacturers.id=things.manufacturer_id "
                                 "left join transactions_things on transactions_things.thing_id=things.id "
                                 "left join valuables on valuables.transaction_id=transactions_things.id "
                                 "left join contractors on contractors.id=valuables.owner_id "
                                 "where "
                                 "contractors.own_account=\"true\" and "
                                 "valuables.id=?",
                                 QVariantList() << id());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setThingData       (HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
        setManufacturerData(HACC_DB_2_DBID(q, 3), HACC_DB_2_STRG(q, 2));
        setValuableData    (HACC_DB_2_STRG(q, 4));
    }
}

base::WSelectorPopup * WValuableSelectButton::constructPopup()
{
    return new WValuableSelectPopup(this);
}

void WValuableSelectButton::setThingData(const hacc::TDBID &iconID, const QString &name)
{
    m_thingName->setText(name);
    m_thingIcon->setIcon(iconID);
}

void WValuableSelectButton::setManufacturerData(const hacc::TDBID &iconID, const QString &name)
{
    m_manufacturerName->setText(name);
    m_manufacturerIcon->setIcon(iconID);
}

void WValuableSelectButton::setValuableData(const QString &serialNumber)
{
    m_serialNumber->setText(serialNumber);
}

void WValuableSelectButton::valuableCreated(const hacc::TDBID &valuableID)
{
    setID(valuableID);
}

}
}
