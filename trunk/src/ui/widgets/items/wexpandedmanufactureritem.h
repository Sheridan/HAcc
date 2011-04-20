#ifndef WMANUFACTURERITEM_He
#define WMANUFACTURERITEM_He

#include "witem.h"
#include "wimage.h"
#include "cmanufacturer.h"

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedManufacturerItem : public ui::item::base::WItem,
                          public hacc::model::CManufacturer
{
public:
    explicit WExpandedManufacturerItem(const hacc::TDBID &id);
    ~WExpandedManufacturerItem();
    void setManufacturerData(const hacc::TDBID &manufacturerIconID, const QString &manufacturerName);
    hacc::TDBID itemID();

private:
    void buildExpanderUIEvent();
    void setMoreData(const QString &description, const QVariant &logo);
    void assignActions();

private:
    void manufacturerUpdated();
};

}
}
}
#endif // WMANUFACTURERITEM_He
