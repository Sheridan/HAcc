#ifndef WTHINGCONTAINER_He
#define WTHINGCONTAINER_He

#include "wcontainer.h"

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedThingItem;
class WExpandedThingContainer : public ui::item::base::WContainer
{
public:
    WExpandedThingContainer(QWidget *parent = 0);
    ~WExpandedThingContainer();

private:
    void appendThing(const hacc::TDBID &thingID, const hacc::TDBID &thingIconID,
                     const QString &thingName, const hacc::TDBID &manufacturerID,
                     const hacc::TDBID &manufacturerIconID, const QString &manufacturerName);

public slots:
    void refresh(const hacc::TDBID &createdID = 0);
};

}
}
}
#endif // WTHINGCONTAINER_He
