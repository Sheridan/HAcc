#include "wthingselectbutton.h"
#include "wthingselectpopup.h"
#include "st.h"

namespace ui
{
namespace selector
{

WThingSelectButton::WThingSelectButton(QWidget *parent) : base::WSelectorButton(parent)
{
    m_layout = new QHBoxLayout();

    m_thingIcon = new ui::icons::WIcon(16, this);
    m_thingName = new QLabel(this);
    m_manufacturerIcon = new ui::icons::WIcon(16, this);
    m_manufacturerName = new QLabel(this);

    m_layout->addWidget(m_thingIcon);
    m_layout->addWidget(m_thingName);
    m_layout->addWidget(m_manufacturerIcon);
    m_layout->addWidget(m_manufacturerName);

    setID(1);

    setLayout(m_layout);

    connect(HACC_THINGS, SIGNAL(created(const hacc::TDBID &)), this, SLOT(thingCreated(const hacc::TDBID &)));
}

WThingSelectButton::~WThingSelectButton()
{
    delete m_thingName;
    delete m_thingIcon;
    delete m_manufacturerName;
    delete m_manufacturerIcon;
    delete m_layout;
}

void WThingSelectButton::idChanged()
{
    QSqlQuery q = HACC_DB->query("select "
                                 "things.name, "
                                 "things.icon_id, "
                                 "manufacturers.name, "
                                 "manufacturers.icon_id "
                                 "from things "
                                 "left join manufacturers on manufacturers.id=things.manufacturer_id "
                                 "where things.id=?",
                                 QVariantList() << id());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setThingData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
        setManufacturergData(HACC_DB_2_DBID(q, 3), HACC_DB_2_STRG(q, 2));
    }
}

base::WSelectorPopup * WThingSelectButton::constructPopup()
{
    return new WThingSelectPopup(this);
}

void WThingSelectButton::setThingData(const hacc::TDBID &iconID, const QString &name)
{
    m_thingName->setText(name);
    m_thingIcon->setIcon(iconID);
}

void WThingSelectButton::setManufacturergData(const hacc::TDBID &iconID, const QString &name)
{
    m_manufacturerName->setText(name);
    m_manufacturerIcon->setIcon(iconID);
}

void WThingSelectButton::thingCreated(const hacc::TDBID &thingID)
{
    setID(thingID);
}

}
}
