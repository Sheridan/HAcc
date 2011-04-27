/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WTRANSACTIONPOOLITEM_He
#define WTRANSACTIONPOOLITEM_He

#include "witem.h"
#include "ctransactionpool.h"

#include "ccontractor.h"
#include "ccontractoraccountdestination.h"
#include "ccontractoraccountsource.h"
#include <QVBoxLayout>

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedTransactionPoolItem : public ui::item::base::WItem,
        public hacc::model::CTransactionPool,
        public hacc::model::composite::CContractorAccountSource,
        public hacc::model::composite::CContractorAccountDestination
{
public:
    WExpandedTransactionPoolItem(const hacc::TDBID &poolID,
                                 const hacc::TDBID &accountSourceID,
                                 const hacc::TDBID &accountDestinationID,
                                 const hacc::TDBID &contractorSourceID,
                                 const hacc::TDBID &contractorDestinationID);
    ~WExpandedTransactionPoolItem();
    void setTransactionPoolData(const QDateTime &datetime, const uint &transactionsCount,
                                const hacc::TMoney &transactionsSumm, const int &transactionPoolType);
    void setSourceContractorData     (const hacc::TDBID &iconID, const QString &name);
    void setSourceAccountData        (const hacc::TDBID &iconID, const QString &name);
    void setDestinationContractorData(const hacc::TDBID &iconID, const QString &name);
    void setDestinationAccountData   (const hacc::TDBID &iconID, const QString &name);
    hacc::TDBID itemID();

private:
    void assignActions();

private slots:
    void transactionPoolUpdated();
    void sourceContractorUpdated();
    void sourceAccountUpdated();
    void destinationContractorUpdated();
    void destinationAccountUpdated();
};

}
}
}
#endif // WTRANSACTIONPOOLITEM_He
