/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CTRANSACTIONPOOL_H
#define CTRANSACTIONPOOL_H

#include "cbase.h"

namespace hacc
{
namespace model
{

//! Сущность. Пул транзакций, чек
class CTransactionPool : public base::CBase
{
    Q_OBJECT
    HACC_MODEL_BASE_EVENTS_DECLARE(transactionPool)
public:
    CTransactionPool();
    //! @ingroup recordsQActionsGenerators
    //! @{
    QAction *addAction(); // buy
    QAction *editAction();
    QAction *removeAction();
    QAction *tagsEditAction();
    QAction *addSellAction(); // sell
    //! @}
    base::CBases  *worker();

public slots:
    void add();  // buy
    void edit();
    void remove();
    void addSell(); // sell
    void tagsEdit();
};

}
}
#endif // CTRANSACTIONPOOL_H
