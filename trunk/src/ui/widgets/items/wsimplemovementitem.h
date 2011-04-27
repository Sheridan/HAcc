/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WSIMPLEMOVEMENTITEM_H
#define WSIMPLEMOVEMENTITEM_H

#include "witem.h"
#include "ccontractorsource.h"
#include "ccontractordestination.h"
#include "cthing.h"
#include "cmovement.h"
#include "cmanufacturer.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleMovementItem : public base::WItem,
        public hacc::model::CMovement,
        public hacc::model::composite::CContractorSource,
        public hacc::model::composite::CContractorDestination,
        public hacc::model::CManufacturer,
        public hacc::model::CThing
{
public:
    explicit WSimpleMovementItem(const hacc::TDBID &movementID,
                                 const hacc::TDBID &sourceContractorID, const hacc::TDBID &destinationContractorID,
                                 const hacc::TDBID &manufacturerID, const hacc::TDBID &thingID);
    ~WSimpleMovementItem();
    void setMovementData             (const QDateTime &datetime);
    void setSourceContractorData     (const hacc::TDBID &iconID, const QString &name);
    void setDestinationContractorData(const hacc::TDBID &iconID, const QString &name);
    void setManufacturerData         (const hacc::TDBID &iconID, const QString &name);
    void setThingData                (const hacc::TDBID &iconID, const QString &name);
    hacc::TDBID itemID();
private:
    void sourceContractorUpdated();
    void destinationContractorUpdated();
    void assignActions();
    void manufacturerUpdated();
    void thingUpdated();
};

}
}
}
#endif // WSIMPLEMOVEMENTITEM_H
