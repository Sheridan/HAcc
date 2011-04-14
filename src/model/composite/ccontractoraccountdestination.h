#ifndef CCONTRACTORACCOUNTDESTINATION_H
#define CCONTRACTORACCOUNTDESTINATION_H

#include "ccontractoraccount.h"

namespace hacc
{
namespace model
{
//! Сборные сущности
namespace composite
{

//! Сущность. Счет контрагента. На этот счет приходят деньги.
/*!
 @see CContractorAccount
*/
class CContractorAccountDestination : public CContractorAccount
{
public:
    CContractorAccountDestination();

private:
    void contractorUpdated();
    void contractorRemoved();
    void accountUpdated();
    void accountRemoved();

protected:
    virtual void destinationContractorUpdated();
    virtual void destinationContractorRemoved();
    virtual void destinationAccountUpdated();
    virtual void destinationAccountRemoved();
};

}
}
}
#endif // CCONTRACTORACCOUNTDESTINATION_H
