#ifndef CCONTRACTORSOURCE_H
#define CCONTRACTORSOURCE_H

#include "ccontractor.h"

namespace hacc
{
namespace model
{
namespace composite
{

//! Сущность. Контрагент. Покупатель.
/*!
 @see hacc::model::CContractor
*/
class CContractorSource : public hacc::model::CContractor
{
public:
    CContractorSource();
    void setSourceContractorID(const hacc::TDBID &id);
    hacc::TDBID sourceContractorID();
    //! @ingroup recordsQActionsGenerators
    //! @{
    QAction *sourceContractorEditAction();
    QAction *sourceContractorRemoveAction();
    QAction *sourceContractorTagsEditAction();
    //! @}
protected:
    virtual void sourceContractorUpdated();
    virtual void sourceContractorRemoved();
};

}
}
}
#endif // CCONTRACTORSOURCE_H
