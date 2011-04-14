#include "cthing.h"
#include "st.h"

namespace hacc
{
namespace model
{

CThing::CThing() : base::CBase()
{
    HACC_MODEL_BASE_EVENTS_INITIALIZE(HACC_THINGS);
}

base::CBases *CThing::worker() { return HACC_THINGS; }

QAction *CThing::editAction()     { return HACC_THINGS->editAction    (id(), this, SLOT(edit())    ); }
QAction *CThing::removeAction()   { return HACC_THINGS->removeAction  (id(), this, SLOT(remove())  ); }
QAction *CThing::tagsEditAction() { return HACC_THINGS->tagsEditAction(id(), this, SLOT(tagsEdit())); }

void CThing::edit     () { HACC_THINGS->edit    (id()); }
void CThing::remove   () { HACC_THINGS->remove  (id()); }
void CThing::tagsEdit () { HACC_THINGS->tagsEdit(id()); }

}
}
