#ifndef WTRANSACTIONTHINGBUYCONTAINER_He
#define WTRANSACTIONTHINGBUYCONTAINER_He

#include "wcontainer.h"
#include "hacc_types.h"

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedTransactionThingBuyContainer : public ui::item::base::WContainer
{
public:
    WExpandedTransactionThingBuyContainer(const hacc::TDBID &parentPool, QWidget *parent = 0);
    ~WExpandedTransactionThingBuyContainer();
private:
    void appendTransaction(const hacc::TDBID &transactionID  , const hacc::TMoney &money       , const hacc::TAmount &amount,
                           const hacc::TDBID &thingID        , const QString &thingName        , const hacc::TDBID &thingIconID,
                           const int &precision              , const QString &enumeratedThingTypeName          ,
                           const hacc::TDBID &anufactiurerID, const QString &manufactiurerName, const hacc::TDBID &manufactiurerIconID);
    hacc::TDBID m_parentPool;

public slots:
    void refresh(const hacc::TDBID &createdID = 0);
};

}
}
}
#endif // WTRANSACTIONTHINGBUYCONTAINER_He
