#ifndef WEXPANDEDVALUABLEITEM_H
#define WEXPANDEDVALUABLEITEM_H

#include "witem.h"
#include "cvaluable.h"
#include "cthing.h"
#include "cmanufacturer.h"
#include "ctransaction.h"
#include "wimage.h"
#include <QHBoxLayout>
#include <QPixmap>
#include <QDateTime>

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedValuableContainer;
class WExpandedValuableItem : public ui::item::base::WItem,
                   public hacc::model::CValuable,
                   public hacc::model::CThing,
                   public hacc::model::CManufacturer,
                   public  hacc::model::CTransaction
{
public:
    WExpandedValuableItem(const hacc::TDBID &valID, const hacc::TDBID &thingID,
                          const hacc::TDBID &manufacturerID, const hacc::TDBID &transactionID);
    ~WExpandedValuableItem();
    void setThingData(const hacc::TDBID &iconId, const QString &name);
    void setManufacturerData(const hacc::TDBID &iconId, const QString &name);
    void setTransactionData(const hacc::TMoney &cost, const QDateTime &purchaseDate);
    void setValuableData(const QString &serial);
    hacc::TDBID itemID();

private:
    void buildExpanderUIEvent();
    void setMoreData(const QString &description, const QVariant &image);
    void assignActions();

private:
    void thingUpdated();
    void manufacturerUpdated();
};

}
}
}
#endif // WEXPANDEDVALUABLEITEM_H
