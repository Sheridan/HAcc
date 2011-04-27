/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WEXPANDEDTRANSACTIONPOOLTHINGITEM_H
#define WEXPANDEDTRANSACTIONPOOLTHINGITEM_H

#include "wexpandedtransactionpoolitem.h"

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedTransactionPoolThingItem : public WExpandedTransactionPoolItem
{
public:
    WExpandedTransactionPoolThingItem(const hacc::TDBID &poolID,
                                      const hacc::TDBID &accountSourceID,
                                      const hacc::TDBID &accountDestinationID,
                                      const hacc::TDBID &contractorSourceID,
                                      const hacc::TDBID &contractorDestinationID);
    ~WExpandedTransactionPoolThingItem();

private:
    void buildExpanderUIEvent();
};

}
}
}
#endif // WEXPANDEDTRANSACTIONPOOLTHINGITEM_H
