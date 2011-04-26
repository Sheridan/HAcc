#include "wcontractorselectbutton.h"
#include "wcontractorselectpopup.h"
#include "st.h"

namespace ui
{
namespace selector
{

WContractorSelectButton::WContractorSelectButton(QWidget *parent) : base::WSelectorButton(parent)
{
    m_layout = new QHBoxLayout();

    m_contractorIcon = new ui::icons::WIcon(16, this);
    m_contractorName = new QLabel(this);

    m_layout->addWidget(m_contractorIcon);
    m_layout->addWidget(m_contractorName);

    setContractorData(1, tr("Click to select"));

    setLayout(m_layout);

    connect(HACC_CONTRACTORS, SIGNAL(created(const hacc::TDBID &)), this, SLOT(contractorCreated(const hacc::TDBID &)));
}

WContractorSelectButton::~WContractorSelectButton()
{
    delete m_contractorName;
    delete m_contractorIcon;
    delete m_layout;
}

void WContractorSelectButton::idChanged()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from contractors where id=?",
                                 QVariantList() << id());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setContractorData(HACC_DB_2_DBID(q, 1),
                          HACC_DB_2_STRG(q, 0));
    }
}

void WContractorSelectButton::setSelfFilter(hacc::model::EContractorFilter filter)
{
    m_filter = filter;
    init();
}

base::WSelectorPopup * WContractorSelectButton::constructPopup()
{
    return new WContractorSelectPopup(m_filter, this);
}

void WContractorSelectButton::setContractorData(const hacc::TDBID &iconID, const QString &name)
{
    m_contractorName->setText(name);
    m_contractorIcon->setIcon(iconID);
}

void WContractorSelectButton::contractorCreated(const hacc::TDBID &contractorID)
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
