#include "ccontractoraccountdestination.h"
namespace hacc
{
namespace model
{
namespace composite
{

CContractorAccountDestination::CContractorAccountDestination() : CContractorAccount()
{
}

void CContractorAccountDestination::contractorUpdated() { destinationContractorUpdated(); }
void CContractorAccountDestination::contractorRemoved() { destinationContractorRemoved(); }
void CContractorAccountDestination::accountUpdated   () { destinationAccountUpdated   (); }
void CContractorAccountDestination::accountRemoved   () { destinationAccountRemoved   (); }

void CContractorAccountDestination::destinationContractorUpdated() {}
void CContractorAccountDestination::destinationContractorRemoved() {}
void CContractorAccountDestination::destinationAccountUpdated   () {}
void CContractorAccountDestination::destinationAccountRemoved   () {}

}
}
}
