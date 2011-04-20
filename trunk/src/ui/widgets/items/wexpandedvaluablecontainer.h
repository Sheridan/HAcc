#ifndef WEXPANDEDVALUABLECONTAINER_H
#define WEXPANDEDVALUABLECONTAINER_H

#include "wcontainer.h"
#include <QDateTime>

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedValuableItem;
class WExpandedValuableContainer : public ui::item::base::WContainer
{
public:
    WExpandedValuableContainer(QWidget *parent = 0);
    ~WExpandedValuableContainer();

private:
    void appendValuable(const hacc::TDBID &valuableID, const QString      &serial,
                        const hacc::TDBID &thingId   , const hacc::TDBID  &thingIconId, const QString   &thingName,
                        const hacc::TDBID &manId     , const hacc::TDBID  &manIconId  , const QString   &manName,
                        const hacc::TDBID &transId   , const hacc::TMoney &cost       , const QDateTime &purchaseDate);

public slots:
    void refresh(const hacc::TDBID &createdID = 0);
};

}
}
}
#endif // WEXPANDEDVALUABLECONTAINER_H
