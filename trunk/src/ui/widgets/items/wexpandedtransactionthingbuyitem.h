#ifndef WTRANSACTIONTHINGBUYITEM_He
#define WTRANSACTIONTHINGBUYITEM_He

#include "wexpandedtransactionthingitem.h"

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedTransactionThingBuyContainer;
class WExpandedTransactionThingBuyItem : public WExpandedTransactionThingItem
{
public:
    WExpandedTransactionThingBuyItem(const hacc::TDBID &transactionID, const hacc::TDBID &thingID, const hacc::TDBID &manufactiurerID);
    ~WExpandedTransactionThingBuyItem();
    void setTransactionData(const hacc::TMoney &money, const hacc::TAmount &amount,
                            const int &precision     , const QString &enumeratedThingTypeName);

private:
    void assignActions();
    void transactionUpdated();
};

}
}
}
#endif // WTRANSACTIONTHINGBUYITEM_He
