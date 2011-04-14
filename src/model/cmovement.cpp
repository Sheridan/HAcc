#include "cmovement.h"
#include "st.h"

namespace hacc
{
namespace model
{

CMovement::CMovement() : base::CBase()
{
    HACC_MODEL_BASE_EVENTS_INITIALIZE(HACC_VALUABLES);
}

base::CBases *CMovement::worker() { return HACC_MOVEMENTS; }

QAction *CMovement::editAction    () { return HACC_MOVEMENTS->editAction    (id(), this, SLOT(edit())    ); }
QAction *CMovement::removeAction  () { return HACC_MOVEMENTS->removeAction  (id(), this, SLOT(remove())  ); }
QAction *CMovement::tagsEditAction() { return HACC_MOVEMENTS->tagsEditAction(id(), this, SLOT(tagsEdit())); }

void CMovement::edit()     { HACC_MOVEMENTS->edit    (id()); }
void CMovement::remove()   { HACC_MOVEMENTS->remove  (id()); }
void CMovement::tagsEdit() { HACC_MOVEMENTS->tagsEdit(id()); }

}
}
