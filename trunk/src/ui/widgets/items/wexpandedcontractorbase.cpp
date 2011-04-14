#include "wexpandedcontractorbase.h"
#include <QComboBox>
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

WExpandedContractorBase::WExpandedContractorBase(QWidget *parent) : ui::item::base::WBase(parent)
{
    m_cbContractorFilter = NULL;
}

WExpandedContractorBase::~WExpandedContractorBase()
{
    delete m_cbContractorFilter;
}

void WExpandedContractorBase::constructControls(QToolBar *tb)
{
    m_cbContractorFilter = new QComboBox();
    m_cbContractorFilter->addItems(QStringList() << tr("All accounts") << tr("Self accounts") << tr("Other accounts"));
    connect(m_cbContractorFilter, SIGNAL(activated(int)), this, SLOT(setContainerAccountFilter(int)));

    tb->addAction(HACC_CONTRACTORS->addAction());
    tb->addAction(HACC_CONTRACTORS->addSelfAction());
    tb->addSeparator();
    tb->addWidget(m_cbContractorFilter);
}

void WExpandedContractorBase::setContainerAccountFilter(int filter)
{
    static_cast<WExpandedContractorContainer *>(container())->setAccountsFilter(filter);
}

base::WContainer *WExpandedContractorBase::buidContainer()
{
    return new WExpandedContractorContainer(this);
}

void WExpandedContractorBase::constructHeader(base::WHeader *header)
{
    header->setLabels(1,1,QStringList() << tr("Name"));
}

}
}
}
