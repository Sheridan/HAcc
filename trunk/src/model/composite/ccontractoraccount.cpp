#include "ccontractoraccount.h"
namespace hacc
{
namespace model
{
namespace composite
{

CContractorAccount::CContractorAccount()
    : hacc::model::CContractor(),
      hacc::model::CAccount()
{
}

void CContractorAccount::setContractorID(const hacc::TDBID &id) { hacc::model::CContractor::setID(id); }
void CContractorAccount::setAccountID   (const hacc::TDBID &id) { hacc::model::CAccount::setID   (id); }

hacc::TDBID CContractorAccount::contractorID() { return hacc::model::CContractor::id(); }
hacc::TDBID CContractorAccount::accountID   () { return hacc::model::CAccount::   id(); }

QAction *CContractorAccount::contractorEditAction    () { return hacc::model::CContractor::editAction(); }
QAction *CContractorAccount::contractorRemoveAction  () { return hacc::model::CContractor::removeAction(); }
QAction *CContractorAccount::contractorTagsEditAction() { return hacc::model::CContractor::tagsEditAction(); }

QAction *CContractorAccount::accountEditAction    () { return hacc::model::CAccount::editAction(); }
QAction *CContractorAccount::accountRemoveAction  () { return hacc::model::CAccount::removeAction(); }
QAction *CContractorAccount::accountTagsEditAction() { return hacc::model::CAccount::tagsEditAction(); }

}
}
}
