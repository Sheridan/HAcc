#ifndef WSIMPLEVALUABLEITEM_H
#define WSIMPLEVALUABLEITEM_H

#include "witem.h"
#include "cthing.h"
#include "cvaluable.h"
#include "cmanufacturer.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleValuableItem :
        public ui::item::base::WItem,
        public hacc::model::CThing,
        public hacc::model::CManufacturer,
        public hacc::model::CValuable
{
public:
    explicit WSimpleValuableItem(const hacc::TDBID &thingID, const hacc::TDBID &manufacturerID, const hacc::TDBID &valuableID);
    ~WSimpleValuableItem();
    void setThingData       (const hacc::TDBID &iconID, const QString &name);
    void setManufacturerData(const hacc::TDBID &iconID, const QString &name);
    void setValuableData    (const QString &serial);
    hacc::TDBID itemID();
private:
    void thingUpdated();
    void manufacturerUpdated();
    void valuableUpdated();
    void assignActions();
};

}
}
}
#endif // WSIMPLEVALUABLEITEM_H
