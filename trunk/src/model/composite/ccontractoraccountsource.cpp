#include "ccontractoraccountsource.h"
namespace hacc
{
namespace model
{
namespace composite
{

CContractorAccountSource::CContractorAccountSource() : CContractorAccount()
{
}

void CContractorAccountSource::contractorUpdated() { sourceContractorUpdated(); }
void CContractorAccountSource::contractorRemoved() { sourceContractorRemoved(); }
void CContractorAccountSource::accountUpdated   () { sourceAccountUpdated   (); }
void CContractorAccountSource::accountRemoved   () { sourceAccountRemoved   (); }

void CContractorAccountSource::sourceContractorUpdated() {}
void CContractorAccountSource::sourceContractorRemoved() {}
void CContractorAccountSource::sourceAccountUpdated   () {}
void CContractorAccountSource::sourceAccountRemoved   () {}

}
}
}
