#include "ccontractor.h"
#include "st.h"

namespace hacc
{
namespace model
{

CContractor::CContractor() : base::CBase()
{
    HACC_MODEL_BASE_EVENTS_INITIALIZE(HACC_CONTRACTORS);
}

base::CBases *CContractor::worker() { return HACC_CONTRACTORS; }

QAction *CContractor::addAccountAction() { return HACC_ACCOUNTS   ->addAction     (id(), this, SLOT(addAccount())); }
QAction *CContractor::editAction()       { return HACC_CONTRACTORS->editAction    (id(), this, SLOT(edit())      ); }
QAction *CContractor::removeAction()     { return HACC_CONTRACTORS->removeAction  (id(), this, SLOT(remove())    ); }
QAction *CContractor::tagsEditAction()   { return HACC_CONTRACTORS->tagsEditAction(id(), this, SLOT(tagsEdit())  ); }

void CContractor::addAccount() { HACC_ACCOUNTS   ->add     (id()); }
void CContractor::edit      () { HACC_CONTRACTORS->edit    (id()); }
void CContractor::remove    () { HACC_CONTRACTORS->remove  (id()); }
void CContractor::tagsEdit  () { HACC_CONTRACTORS->tagsEdit(id()); }


}
}
