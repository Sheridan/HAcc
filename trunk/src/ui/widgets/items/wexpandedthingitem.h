#ifndef WTHINGITEM_He
#define WTHINGITEM_He

#include "witem.h"
#include "cthing.h"
#include "cmanufacturer.h"
#include "wimage.h"
#include <QHBoxLayout>
#include <QPixmap>

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedThingContainer;
class WExpandedThingItem : public ui::item::base::WItem,
                   public hacc::model::CThing,
                   public hacc::model::CManufacturer
{
public:
    WExpandedThingItem(const hacc::TDBID &id, const hacc::TDBID &manufacturerID);
    ~WExpandedThingItem();
    void setThingData(const hacc::TDBID &iconId, const QString &name);
    void setManufacturerData(const hacc::TDBID &iconId, const QString &name);
    hacc::TDBID itemID();

private:
    void buildExpanderUIEvent();
    void setMoreData(const QString &description, const QVariant &image);
    void assignActions();

private:
    void thingUpdated();
    void manufacturerUpdated();
};

}
}
}
#endif // WTHINGITEM_He
