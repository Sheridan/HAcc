#ifndef WTAGITEM_Hs
#define WTAGITEM_Hs

#include "witem.h"
#include "ctag.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleTagItem : public ui::item::base::WItem, public hacc::model::CTag
{
public:
    WSimpleTagItem(const hacc::TDBID &tagID);
    ~WSimpleTagItem();
    void setItemData(const QString &name);
    hacc::TDBID itemID();

private:
    void tagUpdated();
    void assignActions();
};

}
}
}
#endif // WBARTAGITEM_Hs
