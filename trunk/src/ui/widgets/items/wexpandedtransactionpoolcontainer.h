/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WTRANSACTIONPOOLCONTAINER_He
#define WTRANSACTIONPOOLCONTAINER_He

#include "wcontainer.h"
#include "hacc_types.h"
#include <QDateTime>

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedTransactionPoolItem;
class WExpandedTransactionPoolContainer : public ui::item::base::WContainer
{
public:
    WExpandedTransactionPoolContainer(QWidget *parent = 0);
    ~WExpandedTransactionPoolContainer();
private:
    WExpandedTransactionPoolItem *transactionPoolItem(const hacc::TDBID &id);
    void appendTransactionPool(const hacc::TDBID &poolID,                  const QDateTime &datetime,                const int &transactionPoolType,
                               const uint &transactionsCount,              const hacc::TMoney &transactionsSumm,
                               const hacc::TDBID &accountSourceID,         const QString &accountSourceName,         const hacc::TDBID &accountSourceIconID,
                               const hacc::TDBID &accountDestinationID,    const QString &accountDestinationName,    const hacc::TDBID &accountDestinationIconID,
                               const hacc::TDBID &contractorSourceID,      const QString &contractorSourceName,      const hacc::TDBID &contractorSourceIconID,
                               const hacc::TDBID &contractorDestinationID, const QString &contractorDestinationName, const hacc::TDBID &contractorDestinationIconID);

public slots:
    void refresh(const hacc::TDBID &createdID = 0);
};

}
}
}
#endif // WTRANSACTIONPOOLCONTAINER_He
