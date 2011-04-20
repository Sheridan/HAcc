#ifndef WCONTRACTORCONTAINER_He
#define WCONTRACTORCONTAINER_He

#include "wcontainer.h"
#include "hacc_types.h"
#include "ccontractors.h"

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedContractorItem;
class WExpandedContractorContainer : public ui::item::base::WContainer
{
public:
    WExpandedContractorContainer(QWidget *parent = 0);
    ~WExpandedContractorContainer();
private:
    WExpandedContractorItem *contractorItem(const hacc::TDBID &id);
    void appendContractor(const hacc::TDBID &id, const hacc::TDBID &iconID, const QString &name);
    hacc::model::EContractorFilter m_contractorFilter;

public slots:
    void refresh(const hacc::TDBID &createdID = 0);
    void setAccountsFilter(int filter);
};

}
}
}
#endif // WCONTRACTORCONTAINER_He
