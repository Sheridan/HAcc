#ifndef WTHINGITEM_Hs
#define WTHINGITEM_Hs

#include "witem.h"
#include "cthing.h"
#include "cmanufacturer.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleThingItem : public ui::item::base::WItem, public hacc::model::CThing, public hacc::model::CManufacturer
{
public:
    explicit WSimpleThingItem(const hacc::TDBID &thingID, const hacc::TDBID &manufacturerID);
    ~WSimpleThingItem();
    void setThingData(const hacc::TDBID &iconID, const QString &name);
    void setManufacturerData(const hacc::TDBID &iconID, const QString &name);
    hacc::TDBID itemID();
private:
    void thingUpdated();
    void manufacturerUpdated();
    void assignActions();
};

}
}
}
#endif // WTHINGITEM_Hs
