#ifndef WSIMPLEMOVEMENTCONTAINER_H
#define WSIMPLEMOVEMENTCONTAINER_H

#include "wcontainer.h"
#include "ccontractors.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleMovementContainer : public ui::item::base::WContainer
{
    Q_OBJECT
public:
    explicit WSimpleMovementContainer(QWidget *parent = 0);
    ~WSimpleMovementContainer();

private:
    void appendMovement(const hacc::TDBID &movementID             , const QDateTime   &datetime,
                        const hacc::TDBID &sourceContractorID     , const hacc::TDBID &sourceContractorIconID     , const QString &sourceContractorName,
                        const hacc::TDBID &destinationContractorID, const hacc::TDBID &destinationContractorIconID, const QString &destinationContractorName,
                        const hacc::TDBID &manufacturerID         , const hacc::TDBID &manufacturerIconID         , const QString &manufacturerName,
                        const hacc::TDBID &thingID                , const hacc::TDBID &thingIconID                , const QString &thingName);

public slots:
    void refresh(const hacc::TDBID &createdID = 0);

};

}
}
}
#endif // WSIMPLEMOVEMENTCONTAINER_H
