#include "ctransactionpool.h"
#include "st.h"


namespace hacc
{
namespace model
{

CTransactionPool::CTransactionPool() : base::CBase()
{
    HACC_MODEL_BASE_EVENTS_INITIALIZE(HACC_TRANSACTIONS_POOLS);
}

base::CBases *CTransactionPool::worker() { return HACC_TRANSACTIONS_POOLS; }

QAction *CTransactionPool::addAction     () { return HACC_TRANSACTIONS      ->addAction     (id(), this, SLOT(add())     ); }
QAction *CTransactionPool::editAction    () { return HACC_TRANSACTIONS_POOLS->editAction    (id(), this, SLOT(edit())    ); }
QAction *CTransactionPool::removeAction  () { return HACC_TRANSACTIONS_POOLS->removeAction  (id(), this, SLOT(remove())  ); }
QAction *CTransactionPool::addSellAction () { return HACC_TRANSACTIONS      ->addSellAction (id(), this, SLOT(addSell()) ); }
QAction *CTransactionPool::tagsEditAction() { return HACC_TRANSACTIONS_POOLS->tagsEditAction(id(), this, SLOT(tagsEdit())); }

void CTransactionPool::add     () { HACC_TRANSACTIONS      ->addThingBuyTransaction (id()); }
void CTransactionPool::addSell () { HACC_TRANSACTIONS      ->addThingSellTransaction(id()); }
void CTransactionPool::edit    () { HACC_TRANSACTIONS_POOLS->edit    (id()); }
void CTransactionPool::remove  () { HACC_TRANSACTIONS_POOLS->remove  (id()); }
void CTransactionPool::tagsEdit() { HACC_TRANSACTIONS_POOLS->tagsEdit(id()); }


}
}
