/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CTRANSACTIONPOOLS_H
#define CTRANSACTIONPOOLS_H

#include "cbases.h"
#include "ctagged.h"
#include <QDateTime>

namespace hacc
{
namespace model
{
//! Синглон пула транзакций
/*!
 Управляет пулами транзакций. Непосредственно управляет таблицами
     - transaction_pool
 @see CTransactionPool
*/
class CTransactionPools :
        public base::CBases,
        public hacc::model::CTagged
{
    Q_OBJECT
public:
    CTransactionPools();
    ~CTransactionPools();
    void remove(const hacc::TDBID & id);
    void edit(const hacc::TDBID & id);
    void tagsEdit(const hacc::TDBID & id);
    bool checkSpecialPurposeTag(const hacc::TDBID &tagID);
    QString purposeTagsIDString();
    bool    hasPurposeTags();
    //! @ingroup singletoneQActionsGenerators
    //! @{
    QAction *addAction();
    QAction *addTransactionSellAction();
    QAction *addTransactionBuyAction();
    QAction *addTransactionMoneyIncomingAction();
    QAction *addTransactionMoneyOutgoingAction();
    QAction *addTransactionLocalAction();
    //! @}

public slots:
    void add();
    void addTransactionSell();
    void addTransactionBuy();
    void addTransactionMoneyIncoming();
    void addTransactionMoneyOutgoing();
    void addTransactionLocal();

private:
    QAction * generateAction(base::EActionsTypes atype, QObject *reciever, const char * method);
    hacc::TDBID maxDBID();
    hacc::TDBID execAddTransactionPool(const int &transactionPoolType, const QDateTime &datetime,
                                       const hacc::TDBID &source     , const hacc::TDBID &destination);
    void execCreateTransactionPoolMoney(const int &transactionPoolType);
    void execCreateTransactionPoolThing(const int &transactionPoolType);


private slots:
    void transactionUpdate(const hacc::TDBID &transactionId);
};

}
}
#endif // CTRANSACTIONPOOLS_H
