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
    void appendThing(const hacc::TDBID &thingID, const hacc::TDBID &thingIconID,
                     const QString &thingName, const hacc::TDBID &manufacturerID,
                     const hacc::TDBID &manufacturerIconID, const QString &manufacturerName);

public slots:
    void refresh(const hacc::TDBID &createdID = 0);
};

}
}
}
#endif // WTHINGCONTAINER_Hs
