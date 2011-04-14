#ifndef WSIMPLEVALUABLECONTAINER_H
#define WSIMPLEVALUABLECONTAINER_H

#include "wcontainer.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleValuableContainer : public ui::item::base::WContainer
{
    Q_OBJECT
public:
    explicit WSimpleValuableContainer(QWidget *parent = 0);
    ~WSimpleValuableContainer();
private:
    void appendValuable(const hacc::TDBID &thingId, const hacc::TDBID &thingIconId, const QString &thingName,
                        const hacc::TDBID &manId, const hacc::TDBID &manIconId, const QString &manName,
                        const hacc::TDBID &valuableId, const QString &serial);

public slots:
    void refresh(const hacc::TDBID &createdID = 0);
};

}
}
}
#endif // WSIMPLEVALUABLECONTAINER_H
