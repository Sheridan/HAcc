#include "wsimplemovementcontainer.h"
#include "wsimplemovementitem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleMovementContainer::WSimpleMovementContainer(QWidget *parent)
    : ui::item::base::WContainer(parent)
{
    HACC_CONTAINER_CONNECT_CREATED_REMOVED(HACC_MOVEMENTS);
}

WSimpleMovementContainer::~WSimpleMovementContainer()
{}

void WSimpleMovementContainer::refresh(const hacc::TDBID &createdID)
{
    if(!createdID) { cleanItems(); }
    QVariantList parametres;
    QString sql = "select "
            /* 0*/ "movements.id, "
            /* 1*/ "movements.date_time, "
            /* 2*/ "movements.source_contractor_id, "
            /* 3*/ "src_c.icon_id as src_c_icon_id, "
            /* 4*/ "src_c.name as src_c_name, "
            /* 5*/ "movements.destination_contractor_id, "
            /* 6*/ "dst_c.icon_id as dst_c_icon_id, "
            /* 7*/ "dst_c.name as dst_c_name, "
            /* 8*/ "things.manufacturer_id, "
            /* 9*/ "manufacturers.icon_id as manufacturers_icon_id, "
            /*10*/ "manufacturers.name as manufacturers_name, "
            /*11*/ "transactions_things.thing_id as thing_id, "
            /*12*/ "things.icon_id as thing_icon_id, "
            /*13*/ "things.name as thing_name "
            "from movements "
            "left join contractors src_c on src_c.id=movements.source_contractor_id "
            "left join contractors dst_c on dst_c.id=movements.destination_contractor_id "
            "left join valuables on valuables.id=movements.valuable_id "
            "left join transactions_things on transactions_things.id=valuables.transaction_id "
            "left join things on things.id=transactions_things.thing_id "
            "left join manufacturers on manufacturers.id=things.manufacturer_id";
    QString where = "";
    if(!m_searchText.isEmpty())
    {
        if(!where.isEmpty()) { where += " and "; }
        where += QString( " (upper(src_c_name) like upper(\"%%%0%%\") or"
                          " (upper(dst_c_name) like upper(\"%%%0%%\") or"
                          " (upper(manufacturers_name) like upper(\"%%%0%%\") or "
                          " (upper(thing_name) like upper(\"%%%0%%\") "
                         " ) ").arg(m_searchText);
    }
    if(createdID)
    {
        if(!where.isEmpty()) { where += " and "; }
        where += " movements.id=? ";
        parametres << createdID;
    }
    if(!where.isEmpty()) { sql += " where " + where; }
    QSqlQuery q = HACC_DB->query(sql, parametres);
    while(q.next())
    {
        appendMovement(
                    HACC_DB_2_DBID(q, 0),
                    HACC_DB_2_DATI(q, 1),
                    HACC_DB_2_DBID(q, 2),
                    HACC_DB_2_DBID(q, 3),
                    HACC_DB_2_STRG(q, 4),
                    HACC_DB_2_DBID(q, 5),
                    HACC_DB_2_DBID(q, 6),
                    HACC_DB_2_STRG(q, 7),
                    HACC_DB_2_DBID(q, 8),
                    HACC_DB_2_DBID(q, 9),
                    HACC_DB_2_STRG(q, 10),
                    HACC_DB_2_DBID(q, 11),
                    HACC_DB_2_DBID(q, 12),
                    HACC_DB_2_STRG(q, 13)
                    );
    }

}

void WSimpleMovementContainer::appendMovement(const hacc::TDBID &movementID             , const QDateTime &datetime,
                                              const hacc::TDBID &sourceContractorID     , const hacc::TDBID &sourceContractorIconID     , const QString &sourceContractorName,
                                              const hacc::TDBID &destinationContractorID, const hacc::TDBID &destinationContractorIconID, const QString &destinationContractorName,
                                              const hacc::TDBID &manufacturerID         , const hacc::TDBID &manufacturerIconID         , const QString &manufacturerName,
                                              const hacc::TDBID &thingID                , const hacc::TDBID &thingIconID                , const QString &thingName)
{
    WSimpleMovementItem *i = new WSimpleMovementItem(movementID, sourceContractorID, destinationContractorID, manufacturerID, thingID);
    i->setMovementData(datetime);
    i->setSourceContractorData(sourceContractorIconID, sourceContractorName);
    i->setDestinationContractorData(destinationContractorIconID, destinationContractorName);
    i->setManufacturerData(manufacturerIconID, manufacturerName);
    i->setThingData(thingIconID, thingName);
    appendItem(i);
}

}
}
}
