#ifndef WACCOUNTCONTAINER_He
#define WACCOUNTCONTAINER_He

#include "wcontainer.h"
#include "hacc_types.h"

namespace ui
{
namespace item
{
namespace expanded
{
class WExpandedAccountItem;
class WExpandedAccountContainer : public ui::item::base::WContainer
{
public:
    WExpandedAccountContainer(const hacc::TDBID &parentContractor, QWidget *parent = 0);
    ~WExpandedAccountContainer();

private:
    void appendAcount(const hacc::TDBID &id, const hacc::TDBID &iconId, const QString &name);
    hacc::TDBID m_parentContractor;

public slots:
    void refresh(const hacc::TDBID &createdID = 0);
};

}
}
}
#endif // WACCOUNTCONTAINER_He
