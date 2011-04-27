/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WEXPANDEDTRANSACTIONPOOLMONEYITEM_H
#define WEXPANDEDTRANSACTIONPOOLMONEYITEM_H

#include "wexpandedtransactionpoolitem.h"

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedTransactionPoolMoneyItem : public WExpandedTransactionPoolItem
{
public:
    WExpandedTransactionPoolMoneyItem(const hacc::TDBID &poolID,
                                      const hacc::TDBID &accountSourceID,
                                      const hacc::TDBID &accountDestinationID,
                                      const hacc::TDBID &contractorSourceID,
                                      const hacc::TDBID &contractorDestinationID);
    ~WExpandedTransactionPoolMoneyItem();
private:
    QVBoxLayout *m_baseLayout;
    void buildExpanderUIEvent();
    int expandHeight();
};

}
}
}
#endif // WEXPANDEDTRANSACTIONPOOLMONEYITEM_H
