/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WTRANSACTIONTHINGSELLITEM_He
#define WTRANSACTIONTHINGSELLITEM_He

#include "ccontractor.h"
#include "cvaluable.h"
#include "wexpandedtransactionthingitem.h"

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedTransactionThingSellItem :
        public WExpandedTransactionThingItem,
        public hacc::model::CContractor,
        public hacc::model::CValuable
{
public:
    WExpandedTransactionThingSellItem(const hacc::TDBID &transactionID,
                                      const hacc::TDBID &thingID,
                                      const hacc::TDBID &manufactiurerID,
                                      const hacc::TDBID &ownerID,
                                      const hacc::TDBID &valuableID);
    ~WExpandedTransactionThingSellItem();
    void setTransactionData(const hacc::TMoney &buyMoney, const hacc::TMoney &sellMoney);
    void setOwnerData   (const hacc::TDBID &iconID, const QString &name);
    void setValuableData(const QString &serial);

private:
    void assignActions();
    void transactionUpdated();
    void contractorUpdated();
    void valuableUpdated();
};

}
}
}
#endif // WTRANSACTIONTHINGSELLITEM_He
