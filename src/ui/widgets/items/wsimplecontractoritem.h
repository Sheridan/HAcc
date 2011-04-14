#ifndef WSIMPLECONTRACTORITEM_H
#define WSIMPLECONTRACTORITEM_H

#include "witem.h"
#include "ccontractor.h"
#include "caccount.h"
namespace ui
{
namespace item
{
namespace simple
{

class WSimpleContractorItem : public base::WItem, public hacc::model::CContractor
{
public:
    explicit WSimpleContractorItem(const hacc::TDBID &contractorID);
    ~WSimpleContractorItem();
    void setContractorData(const hacc::TDBID &iconID, const QString &name);
    hacc::TDBID itemID();
private:
    void contractorUpdated();
    void assignActions();
};

}
}
}
#endif // WSIMPLECONTRACTORITEM_H
