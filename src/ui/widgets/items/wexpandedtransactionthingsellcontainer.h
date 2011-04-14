#ifndef WTRANSACTIONTHINGSELLCONTAINER_He
#define WTRANSACTIONTHINGSELLCONTAINER_He

#include "wcontainer.h"
#include "hacc_types.h"

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedTransactionThingSellContainer : public ui::item::base::WContainer
{
public:
    WExpandedTransactionThingSellContainer(const hacc::TDBID &parentPool, QWidget *parent = 0);
    ~WExpandedTransactionThingSellContainer();
private:
    void appendTransaction(const hacc::TDBID &transactionID  , const hacc::TMoney &buyMoney    , const hacc::TMoney &sellMoney,
                           const hacc::TDBID &thingID        , const QString &thingName        , const hacc::TDBID &thingIconID,
                           const hacc::TDBID &manufactiurerID, const QString &manufactiurerName, const hacc::TDBID &manufactiurerIconID,
                           const hacc::TDBID &ownerID        , const QString &ownerName        , const hacc::TDBID &ownerIconID,
                           const hacc::TDBID &valuableID     , const QString &serial);
    /*
    void setTransactionData(const hacc::TMoney &buyMoney, const hacc::TMoney &sellMoney);
    void setOwnerData   (const hacc::TDBID &iconID, const QString &name);
    void setValuableData(const QString &serial);
    void setThingData(const QString &thingName, const hacc::TDBID &thingIconId);
    void setManufacturerData(const QString &manufactiurerName, const hacc::TDBID &manufactiurerIconID);
      */
    hacc::TDBID m_parentPool;

public slots:
    void refresh(const hacc::TDBID &createdID = 0);
};

}
}
}
#endif // WTRANSACTIONTHINGSELLCONTAINER_He
