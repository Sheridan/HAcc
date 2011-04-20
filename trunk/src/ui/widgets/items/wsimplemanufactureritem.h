#ifndef WMANUFACTURERITEM_Hs
#define WMANUFACTURERITEM_Hs

#include "witem.h"
#include "cmanufacturer.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleManufacturerItem : public ui::item::base::WItem, public hacc::model::CManufacturer
{
public:
    explicit WSimpleManufacturerItem(const hacc::TDBID &id);
    ~WSimpleManufacturerItem();
    void setItemData(const hacc::TDBID &manufacturerIconID, const QString &manufacturerName);
    hacc::TDBID itemID();
private:
    void manufacturerUpdated();
    void assignActions();
};

}
}
}
#endif // WMANUFACTURERITEM_Hs
