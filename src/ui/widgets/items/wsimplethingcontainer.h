#ifndef WTHINGCONTAINER_Hs
#define WTHINGCONTAINER_Hs

#include "wcontainer.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleThingContainer : public ui::item::base::WContainer
{
    Q_OBJECT
public:
    explicit WSimpleThingContainer(QWidget *parent = 0);
    ~WSimpleThingContainer();
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
#endif // WTHINGCONTAINER_Hs
