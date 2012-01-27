#include "wexpandedtransactionpoolthingitem.h"
#include "wexpandedtransactionthingbuybase.h"
#include "wexpandedtransactionthingsellbase.h"
#include "st.h"
#include <QTabWidget>
namespace ui
{
namespace item
{
namespace expanded
{

WExpandedTransactionPoolThingItem::WExpandedTransactionPoolThingItem(const hacc::TDBID &poolID,
                                                                     const hacc::TDBID &accountSourceID,
                                                                     const hacc::TDBID &accountDestinationID,
                                                                     const hacc::TDBID &contractorSourceID,
                                                                     const hacc::TDBID &contractorDestinationID)
    : WExpandedTransactionPoolItem(poolID, accountSourceID, accountDestinationID, contractorSourceID, contractorDestinationID)
{}

WExpandedTransactionPoolThingItem::~WExpandedTransactionPoolThingItem()
{}

void WExpandedTransactionPoolThingItem::buildExpanderUIEvent()
{
    if(HACC_TRANSACTIONS_POOLS->tagAttached(HACC_TAG_ID_BUYING, itemID()))
    {
        appendContainer(new ui::item::expanded::WExpandedTransactionThingBuyBase(itemID()),
                    HACC_ICONS->icon(tools::icons::iTransaction),
                    QObject::tr("Transactions"));
    }
    if(HACC_TRANSACTIONS_POOLS->tagAttached(HACC_TAG_ID_SELLING, itemID()))
    {
        appendContainer(new ui::item::expanded::WExpandedTransactionThingSellBase(itemID()),
                    HACC_ICONS->icon(tools::icons::iTransaction),
                    QObject::tr("Transactions"));
    }
    appendTagsTab < ui::tag::TTagContainer <hacc::model::CTransactionPool, hacc::model::CTransactionPools> >();
}

}
}
}
