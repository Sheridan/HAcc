#include "ccontractorsource.h"
namespace hacc
{
namespace model
{
namespace composite
{

CContractorSource::CContractorSource()
    : hacc::model::CContractor()
{
}

void CContractorSource::setSourceContractorID(const hacc::TDBID &id) { setID(id); }
hacc::TDBID CContractorSource::sourceContractorID() { return id(); }

QAction *CContractorSource::sourceContractorEditAction    () { return editAction(); }
QAction *CContractorSource::sourceContractorRemoveAction  () { return removeAction(); }
QAction *CContractorSource::sourceContractorTagsEditAction() { return tagsEditAction(); }


void CContractorSource::contractorUpdated() { sourceContractorUpdated(); }
void CContractorSource::contractorRemoved() { sourceContractorRemoved(); }

void CContractorSource::sourceContractorUpdated() { }
void CContractorSource::sourceContractorRemoved() { }

}
}
}
