#include "cvaluable.h"
#include "st.h"

namespace hacc
{
namespace model
{

CValuable::CValuable() : base::CBase()
{
    HACC_MODEL_BASE_EVENTS_INITIALIZE(HACC_VALUABLES);
}

base::CBases *CValuable::worker() { return HACC_VALUABLES; }

QAction *CValuable::editAction    () { return HACC_VALUABLES->editAction    (id(), this, SLOT(edit())    ); }
QAction *CValuable::removeAction  () { return HACC_VALUABLES->removeAction  (id(), this, SLOT(remove())  ); }
QAction *CValuable::tagsEditAction() { return HACC_VALUABLES->tagsEditAction(id(), this, SLOT(tagsEdit())); }

void CValuable::edit()     { HACC_VALUABLES->edit    (id()); }
void CValuable::remove()   { HACC_VALUABLES->remove  (id()); }
void CValuable::tagsEdit() { HACC_VALUABLES->tagsEdit(id()); }

}
}
