#include "ctag.h"
#include "st.h"
namespace hacc
{
namespace model
{

CTag::CTag() : base::CBase()
{
    HACC_MODEL_BASE_EVENTS_INITIALIZE(HACC_TAGS);
}

base::CBases *CTag::worker() { return HACC_TAGS; }

QAction *CTag::editAction  () { return HACC_TAGS->editAction  (id(), this, SLOT(edit())  ); }
QAction *CTag::removeAction() { return HACC_TAGS->removeAction(id(), this, SLOT(remove())); }

void CTag::edit  () { HACC_TAGS->edit  (id()); }
void CTag::remove() { HACC_TAGS->remove(id()); }

}
}
