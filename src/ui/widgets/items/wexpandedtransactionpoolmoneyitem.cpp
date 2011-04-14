#include "wexpandedtransactionpoolmoneyitem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

WExpandedTransactionPoolMoneyItem::WExpandedTransactionPoolMoneyItem(const hacc::TDBID &poolID,
                                                                     const hacc::TDBID &accountSourceID,
                                                                     const hacc::TDBID &accountDestinationID,
                                                                     const hacc::TDBID &contractorSourceID,
                                                                     const hacc::TDBID &contractorDestinationID)
    : WExpandedTransactionPoolItem(poolID, accountSourceID, accountDestinationID, contractorSourceID, contractorDestinationID)
{
}

WExpandedTransactionPoolMoneyItem::~WExpandedTransactionPoolMoneyItem()
{
}

void WExpandedTransactionPoolMoneyItem::buildExpanderUIEvent()
{
//    m_transactions = new ui::item::expanded::WExpandedTransactionThingBase(hacc::model::CTransactionPool::id(), this);
//    m_transactions->buildUi();
//    m_baseLayout->addWidget(m_transactions);
//    m_transactions->container()->refresh();
}

int WExpandedTransactionPoolMoneyItem::expandHeight()
{
    return 100;
}

}
}
}
