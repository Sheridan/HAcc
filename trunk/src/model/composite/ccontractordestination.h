/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CCONTRACTORDESTINATION_H
#define CCONTRACTORDESTINATION_H
#include "ccontractor.h"

namespace hacc
{
namespace model
{
namespace composite
{

//! Сущность. Контрагент. Продавец.
/*!
 @see hacc::model::CContractor
*/
class CContractorDestination : public hacc::model::CContractor
{
public:
    CContractorDestination();
    void setDestinationContractorID(const hacc::TDBID &id);
    hacc::TDBID destinationContractorID();
    //! @ingroup recordsQActionsGenerators
    //! @{
    QAction *destinationContractorEditAction();
    QAction *destinationCcontractorRemoveAction();
    QAction *destinationContractorTagsEditAction();
    //! @}
protected:
    virtual void destinationContractorUpdated();
    virtual void destinationContractorRemoved();
private:
    virtual void contractorUpdated();
    virtual void contractorRemoved();
};

}
}
}
#endif // CCONTRACTORDESTINATION_H
