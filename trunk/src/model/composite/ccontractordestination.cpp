#include "ccontractordestination.h"
namespace hacc
{
namespace model
{
namespace composite
{

CContractorDestination::CContractorDestination()
    : hacc::model::CContractor()
{
}

void CContractorDestination::setDestinationContractorID(const hacc::TDBID &id) { setID(id); }
hacc::TDBID CContractorDestination::destinationContractorID() { return id(); }

QAction *CContractorDestination::destinationContractorEditAction    () { return editAction(); }
QAction *CContractorDestination::destinationCcontractorRemoveAction () { return removeAction(); }
QAction *CContractorDestination::destinationContractorTagsEditAction() { return tagsEditAction(); }

void CContractorDestination::destinationContractorUpdated() { contractorUpdated(); }
void CContractorDestination::destinationContractorRemoved() { contractorRemoved(); }

}
}
}
