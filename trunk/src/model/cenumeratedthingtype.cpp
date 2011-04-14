#include "cenumeratedthingtype.h"
#include "st.h"

namespace hacc
{
namespace model
{

CEnumeratedThingType::CEnumeratedThingType() : base::CBase()
{
    HACC_MODEL_BASE_EVENTS_INITIALIZE(HACC_ENUMERATED_THING_TYPES);
}

base::CBases *CEnumeratedThingType::worker() { return HACC_ENUMERATED_THING_TYPES; }

QAction *CEnumeratedThingType::editAction  () { return HACC_ENUMERATED_THING_TYPES->editAction  (id(), this, SLOT(edit())  ); }
QAction *CEnumeratedThingType::removeAction() { return HACC_ENUMERATED_THING_TYPES->removeAction(id(), this, SLOT(remove())); }

void CEnumeratedThingType::edit  () { HACC_ENUMERATED_THING_TYPES->edit  (id()); }
void CEnumeratedThingType::remove() { HACC_ENUMERATED_THING_TYPES->remove(id()); }

}
}
