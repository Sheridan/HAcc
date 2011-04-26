#include "wmanufacturerselectbutton.h"
#include "wmanufacturerselectpopup.h"
#include "st.h"

namespace ui
{
namespace selector
{

WManufacturerSelectButton::WManufacturerSelectButton(QWidget *parent) : base::WSelectorButton(parent)
{
    m_layout = new QHBoxLayout();

    m_wIcon = new ui::icons::WIcon(16, this);
    m_lName = new QLabel(this);

    m_layout->addWidget(m_wIcon);
    m_layout->addWidget(m_lName);

    setID(1);

    setLayout(m_layout);

    connect(HACC_MANUFACTURERS, SIGNAL(created(const hacc::TDBID &)), this, SLOT(manufacturerCreated(const hacc::TDBID &)));
}

WManufacturerSelectButton::~WManufacturerSelectButton()
{
    delete m_lName;
    delete m_wIcon;
    delete m_layout;
}

void WManufacturerSelectButton::idChanged()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from manufacturers where id=?",
                                 QVariantList() << id());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setData(HACC_DB_2_DBID(q, 1),
                HACC_DB_2_STRG(q, 0));
    }
}

base::WSelectorPopup * WManufacturerSelectButton::constructPopup()
{
    return new WManufacturerSelectPopup(this);
}

void WManufacturerSelectButton::setData(const hacc::TDBID &iconID, const QString &name)
{
    m_lName->setText(name);
    m_wIcon->setIcon(iconID);
}

void WManufacturerSelectButton::manufacturerCreated(const hacc::TDBID &manufacturerID)
{
    setID(manufacturerID);
}

}
}
