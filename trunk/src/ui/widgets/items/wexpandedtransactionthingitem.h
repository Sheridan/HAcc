#ifndef WEXPANDEDTRANSACTIONTHINGITEM_H
#define WEXPANDEDTRANSACTIONTHINGITEM_H

#include "witem.h"
#include "ctransaction.h"
#include "cthing.h"
#include "cmanufacturer.h"

namespace ui
{
//! Грид
namespace item
{
//! Грид с раскрывающимися строками
namespace expanded
{

class WExpandedTransactionThingItem :
        public ui::item::base::WItem,
        public hacc::model::CTransaction,
        public hacc::model::CThing,
        public hacc::model::CManufacturer
{
public:
    WExpandedTransactionThingItem(const int &columns,
                                  const hacc::TDBID &transactionID,
                                  const hacc::TDBID &thingID,
                                  const hacc::TDBID &manufactiurerID);
    ~WExpandedTransactionThingItem();
    void setThingData(const QString &thingName, const hacc::TDBID &thingIconID);
    void setManufacturerData(const QString &manufactiurerName, const hacc::TDBID &manufactiurerIconID);
    hacc::TDBID itemID();

private:
    void buildExpanderUIEvent();

protected:
    void assignActions();

private:
    void thingUpdated();
    void manufacturerUpdated();
};

}
}
}
#endif // WEXPANDEDTRANSACTIONTHINGITEM_H
