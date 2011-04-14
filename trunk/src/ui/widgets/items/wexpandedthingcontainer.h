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
    void appendThing(const hacc::TDBID &thingId, const hacc::TDBID &thingIconId,
                     const QString &thingName, const hacc::TDBID &manId,
                     const hacc::TDBID &manIconId, const QString &manName);

public slots:
    void refresh(const hacc::TDBID &createdID = 0);
};

}
}
}
#endif // WTHINGCONTAINER_He
