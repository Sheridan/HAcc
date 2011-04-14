#ifndef WBARCONTRACTORACCOUNTITEM_Hs
#define WBARCONTRACTORACCOUNTITEM_Hs

#include "witem.h"
#include "ccontractor.h"
#include "caccount.h"
namespace ui
{
namespace item
{
namespace simple
{

class WSimpleContractorAccountItem : public base::WItem, public hacc::model::CContractor, public hacc::model::CAccount
{
public:
    explicit WSimpleContractorAccountItem(const hacc::TDBID &accountID, const hacc::TDBID &contractorID);
    ~WSimpleContractorAccountItem();
    void setContractorData(const hacc::TDBID &iconID, const QString &name);
    void setAccountData(const hacc::TDBID &iconID, const QString &name);
    hacc::TDBID itemID();
private:
    void contractorUpdated();
    void accountUpdated();
    void assignActions();
};

}
}
}
#endif // WBARCONTRACTORACCOUNTITEM_Hs
