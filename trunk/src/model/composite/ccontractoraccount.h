/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CCONTRACTORACCOUNT_H
#define CCONTRACTORACCOUNT_H

#include "ccontractor.h"
#include "caccount.h"

namespace hacc
{
namespace model
{
namespace composite
{

//! Сущность. Счет контрагента.
/*!
 @see hacc::model::CContractor
 @see hacc::model::CAccount
*/
class CContractorAccount : public hacc::model::CContractor,
                           public hacc::model::CAccount
{
public:
    CContractorAccount();
    void setContractorID(const hacc::TDBID &id);
    void setAccountID(const hacc::TDBID &id);
    hacc::TDBID contractorID();
    hacc::TDBID accountID();

    //! @ingroup recordsQActionsGenerators
    //! @{
    QAction *contractorEditAction();
    QAction *contractorRemoveAction();
    QAction *contractorTagsEditAction();

    QAction *accountEditAction();
    QAction *accountRemoveAction();
    QAction *accountTagsEditAction();
    //! @}

};

}
}
}
#endif // CCONTRACTORACCOUNT_H
