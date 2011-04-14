#include "ccurrency.h"
#include "st.h"

namespace hacc
{
namespace model
{

CCurrency::CCurrency() : base::CBase()
{
    HACC_MODEL_BASE_EVENTS_INITIALIZE(HACC_CURRENCYES);
}

base::CBases *CCurrency::worker() { return HACC_CURRENCYES; }

QAction *CCurrency::editAction    () { return HACC_CURRENCYES->editAction    (id(), this, SLOT(edit())    ); }
QAction *CCurrency::removeAction  () { return HACC_CURRENCYES->removeAction  (id(), this, SLOT(remove())  ); }

void CCurrency::edit()     { HACC_CURRENCYES->edit    (id()); }
void CCurrency::remove()   { HACC_CURRENCYES->remove  (id()); }

}
}
