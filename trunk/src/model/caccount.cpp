#include "caccount.h"
#include "st.h"

namespace hacc
{
namespace model
{

CAccount::CAccount() : base::CBase()
{
    HACC_MODEL_BASE_EVENTS_INITIALIZE(HACC_ACCOUNTS);
}

base::CBases *CAccount::worker() { return HACC_ACCOUNTS; }

QAction *CAccount::editAction    () { return HACC_ACCOUNTS->editAction    (id(), this, SLOT(edit())    ); }
QAction *CAccount::removeAction  () { return HACC_ACCOUNTS->removeAction  (id(), this, SLOT(remove())  ); }
QAction *CAccount::tagsEditAction() { return HACC_ACCOUNTS->tagsEditAction(id(), this, SLOT(tagsEdit())); }

void CAccount::edit()     { HACC_ACCOUNTS->edit    (id()); }
void CAccount::remove()   { HACC_ACCOUNTS->remove  (id()); }
void CAccount::tagsEdit() { HACC_ACCOUNTS->tagsEdit(id()); }

}
}
