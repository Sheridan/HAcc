#include "ctransaction.h"
#include "st.h"

namespace hacc
{
namespace model
{

CTransaction::CTransaction() : base::CBase()
{
    HACC_MODEL_BASE_EVENTS_INITIALIZE(HACC_TRANSACTIONS);
}

base::CBases *CTransaction::worker() { return HACC_TRANSACTIONS; }

QAction *CTransaction::editAction    () { return HACC_TRANSACTIONS->editAction    (id(), this, SLOT(edit())    ); }
QAction *CTransaction::removeAction  () { return HACC_TRANSACTIONS->removeAction  (id(), this, SLOT(remove())  ); }
QAction *CTransaction::tagsEditAction() { return HACC_TRANSACTIONS->tagsEditAction(id(), this, SLOT(tagsEdit())); }

void CTransaction::edit     () { HACC_TRANSACTIONS->editThingBuyTransaction    (id()); }
void CTransaction::remove   () { HACC_TRANSACTIONS->removeThingTransaction  (id()); }
void CTransaction::tagsEdit () { HACC_TRANSACTIONS->tagsEdit(id()); }

}
}
