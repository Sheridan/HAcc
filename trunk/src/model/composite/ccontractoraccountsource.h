/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CCONTRACTORACCOUNTSOURCE_H
#define CCONTRACTORACCOUNTSOURCE_H

#include "ccontractoraccount.h"

namespace hacc
{
namespace model
{
namespace composite
{

//! Сущность. Счет контрагента. С этого счета списываются деньги.
/*!
 @see CContractorAccount
*/
class CContractorAccountSource : public CContractorAccount
{
public:
    CContractorAccountSource();

private:
    void contractorUpdated();
    void contractorRemoved();
    void accountUpdated();
    void accountRemoved();

protected:
    virtual void sourceContractorUpdated();
    virtual void sourceContractorRemoved();
    virtual void sourceAccountUpdated();
    virtual void sourceAccountRemoved();
};

}
}
}
#endif // CCONTRACTORACCOUNTSOURCE_H
