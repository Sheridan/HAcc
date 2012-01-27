/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CTRANSACTIONS_H
#define CTRANSACTIONS_H

#include "cbases.h"
#include "ctagged.h"

namespace hacc
{
namespace model
{

//! Синглон транзакций
/*!
 Управляет транзакциями. Непосредственно управляет таблицами
     - transactions
     - transactions_things
     - transactions_valuables
     - transactions_commisions
 @see CTransaction
*/
class CTransactions :
        public base::CBases,
        public hacc::model::CTagged
{
    Q_OBJECT
public:
    CTransactions();
    ~CTransactions();
    void removeThingTransaction(const hacc::TDBID & id);                 //!< Удаление транзакции с вешью (покупка/подарок)
    void editThingBuyTransaction(const hacc::TDBID & transactionID);     //!< Редактирование транзакции покупки вещи
    void addThingBuyTransaction (const hacc::TDBID & poolId);            //!< Добавление транзакции покупки в пул
    void addThingSellTransaction(const hacc::TDBID & poolId);            //!< Добавление транзакции продажи в пул
    void tagsEdit(const hacc::TDBID & id);
    void commitThingsTransactions(const hacc::TDBID &poolID          , const int         &transactionType,
                                  const hacc::TDBID &sourceContractor, const hacc::TDBID &destinationContractor,
                                  const QDateTime   &datetime);         //!< Подтверждение транзакций при подтверждении пула
    void cleanAfterRemoveTransactionPool(const hacc::TDBID & poolId);   //!< Очистка после удаления пула транзакций
    void removeUncommitedTransactions();
    void cleanAfterThingRemove(const hacc::TDBID & thingID);
    bool checkSpecialPurposeTag(const hacc::TDBID &tagID);
    QString purposeTagsIDString();
    bool    hasPurposeTags();
    hacc::TDBID addOnlyTransactionBase(const hacc::TDBID & poolId, const hacc::TMoney &money);
    void addTransferTransaction(const int &transactionType,
                                const hacc::TDBID & basePoolID, const hacc::TDBID & commisionPoolID,
                                const hacc::TMoney &money     , const bool &hasCommission,
                                const bool &commissionInMoney , const bool &commisionInPercents,
                                const hacc::TMoney &commission, const hacc::TDBID &commissionTo);        //!< Добавление транзакции трансфера денег
    void editTransferTransaction(const hacc::TDBID & baseTransactionID, const hacc::TDBID & commisionTransactionID,
                                 const hacc::TDBID & basePoolID       , const hacc::TDBID & commisionPoolID,
                                 const hacc::TMoney &money            , const bool &hasCommission,
                                 const bool &commissionInMoney        , const bool &commisionInPercents,
                                 const hacc::TMoney &commission       , const hacc::TDBID &commissionTo); //!< Редактирование транзакции трансфера денег
    //! @ingroup singletoneQActionsGenerators
    //! @{
    QAction * addSellAction     (const hacc::TDBID &id, QObject *reciever, const char * method);
    //! @}

private:
    QAction * generateAction(base::EActionsTypes atype, QObject *reciever, const char * method);
    hacc::TDBID maxDBID();
    hacc::SMoneyCommission calculateCommissionValue(const hacc::TMoney &money, const hacc::TMoney &commission,
                                                    const bool &commisionInPercents, const bool &commissionInMoney,
                                                    const bool &hasCommission);                                           //!< Вычисление значения коммиссии за трансфер денег
    void addOnlyCommission(const hacc::TDBID & commisionPoolID, const hacc::TDBID & basePoolID,
                           const hacc::TDBID &commissionTo, const bool &commisionInPercents,
                           const bool &commissionInMoney, const hacc::TMoney &commission,
                           const hacc::TMoney &realCommission);                                                           //!< Добавление коммиссии к транзакции трансфера денег
    void removeTransaction(const hacc::TDBID & id);                                                                       //!< Удаление транзакции
    void transactionBuyValuablesAppend(const int &amount                  , const hacc::TDBID &transactionID,
                                       const hacc::TDBID &sourceContractor, const hacc::TDBID &destinationContractor,
                                       const hacc::TDBID &thingID         , const QDateTime   &datetime,
                                       const int &transactionType);                                                       //!< Создает средства и перемещения

};

}
}
#endif // CTRANSACTIONS_H
