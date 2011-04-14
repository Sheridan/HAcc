#ifndef WACCOUNTITEM_He
#define WACCOUNTITEM_He

#include "witem.h"
#include "caccount.h"

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedAccountContainer;
class WExpandedAccountItem : public ui::item::base::WItem,
                     public hacc::model::CAccount
{
public:
    WExpandedAccountItem(const hacc::TDBID &id);
    ~WExpandedAccountItem();
    void setAccountData(const hacc::TDBID &iconId, const QString &name);
    hacc::TDBID itemID();

private:
    QVBoxLayout *m_baseLayout;
    void buildExpanderUIEvent();
    void assignActions();

private slots:
    void accountUpdated();
};

}
}
}
#endif // WACCOUNTITEM_He
