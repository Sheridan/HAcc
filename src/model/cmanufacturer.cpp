#include "cmanufacturer.h"
#include "st.h"

namespace hacc
{
namespace model
{

CManufacturer::CManufacturer() : base::CBase()
{
    HACC_MODEL_BASE_EVENTS_INITIALIZE(HACC_MANUFACTURERS);
}

base::CBases *CManufacturer::worker() { return HACC_MANUFACTURERS; }

QAction *CManufacturer::editAction    () { return HACC_MANUFACTURERS->editAction    (id(), this, SLOT(edit())    ); }
QAction *CManufacturer::removeAction  () { return HACC_MANUFACTURERS->removeAction  (id(), this, SLOT(remove())  ); }
QAction *CManufacturer::tagsEditAction() { return HACC_MANUFACTURERS->tagsEditAction(id(), this, SLOT(tagsEdit())); }


void CManufacturer::edit    () { HACC_MANUFACTURERS->edit    (id()); }
void CManufacturer::remove  () { HACC_MANUFACTURERS->remove  (id()); }
void CManufacturer::tagsEdit() { HACC_MANUFACTURERS->tagsEdit(id()); }


}
}
