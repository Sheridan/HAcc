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
    void appendRow(const hacc::TDBID &thingID       , const hacc::TDBID &thingIconID       , const QString &thingName,
                   const hacc::TDBID &manufacturerID, const hacc::TDBID &manufacturerIconID, const QString &manufacturerName,
                   const hacc::TDBID &valuableID    , const QString &serial);

public slots:
    void refresh(const hacc::TDBID &createdID = 0);
};

}
}
}
#endif // WSIMPLEVALUABLECONTAINER_H
