#include "cvaluables.h"
#include "titemtagsedit.h"
#include "icons.h"
#include "st.h"

#include "ttagcontainer.h"
#include "cvaluable.h"

namespace hacc
{
namespace model
{

CValuables::CValuables()
    : base::CBases(),
      hacc::model::CTagged(HACC_TAG_TABLE_NAME(valuable), HACC_TAG_TABLE_ID_NAME(valuable))
{}

CValuables::~CValuables()
{}

void CValuables::add()
{}

hacc::TDBID CValuables::addTransactionValuable(const hacc::TDBID & transactionID, const hacc::TDBID &ownerContractor)
{
    hacc::TDBID newID = nextID();
    HACC_DB->exec("insert into valuables (id,transaction_id,owner_id,serial_number) values (?,?,?,?)",
                  QVariantList() << newID << transactionID << ownerContractor << idToSerial(newID));
    emit created(newID);
    return newID;
}

void CValuables::transactionRemoved(const hacc::TDBID & transactionID)
{
    execRemove("transaction_id=?", QVariantList() << transactionID);
}

void CValuables::thingUpdated(const hacc::TDBID & thingID)
{
    QSqlQuery q = HACC_DB->query("select "
                                 "transactions_things.id "
                                 "from transactions_things "
                                 "where transactions_things.thing_id=?",
                                 QVariantList() << thingID);
    while(q.next())
    {
        hacc::TDBID transactionID = HACC_DB_2_DBID(q, 0);
        QSqlQuery inq = HACC_DB->query("select id from valuables where transaction_id=?",
                                     QVariantList() << transactionID);
        hacc::TDBID valID = HACC_QUERY_DATA_AVIALABLE(inq) ? HACC_DB_2_DBID(inq, 0) : 0;
        if(HACC_THINGS->tagAttached(HACC_TAG_ID_OBJECT, thingID))
        {
            if(!valID)
            {
                hacc::TDBID newID = nextID();
                HACC_DB->exec("insert into valuables (id,transaction_id,serial_number) values (?,?,?)",
                              QVariantList() << newID << transactionID << idToSerial(newID));
                emit created(newID);
            }
        }
        else
        {
            if(valID)
            {
                 execRemove("transaction_id=?", QVariantList() << transactionID);
            }
        }
    }
}

void CValuables::thingRemoved(const hacc::TDBID & thingID)
{
    QSqlQuery q = HACC_DB->query("select "
                                 "transactions_things.id "
                                 "from transactions_things "
                                 "where transactions_things.thing_id=?",
                                 QVariantList() << thingID);
    while(q.next())
    {
        execRemove("transaction_id=?", QVariantList() << HACC_DB_2_DBID(q, 0));
    }
}

void CValuables::execRemove(const QString &where, const QVariantList &parameters)
{
    hacc::TIDList idList = HACC_DB->listID("valuables", where, parameters);
    HACC_DB->exec("delete from valuables where " + where, parameters);
    foreach(hacc::TDBID id, idList)
    {
        //! \todo проследить, чтобы удалились перемещения
        detachTags(id);
        emit removed(id);
    }
}

/**
 * Смена владельца ценности
 * @param id Идентификатор ценности
 * @param contractorID идентификатор контрагента - нового владельца
*/
void CValuables::changeValuableOwner(const hacc::TDBID & id, const hacc::TDBID & contractorID)
{
    HACC_DB->exec("update valuables set owner_id=? where id=?",
                  QVariantList() << contractorID << id);
}

void CValuables::remove(const hacc::TDBID & id)
{
    //! \todo Реализовать списание ценности
//    if(id > 0)
//    {
//        QSqlQuery q = HACC_DB->query("select name from accounts where id=?", QVariantList() << id);
//        q.next();
//        if(QMessageBox::question(
//                HACC_WINDOW,
//                tr("Account remove"),
//                tr("You sure you want to delete '%1' account?").arg(HACC_DB_2_STRG(q, 0)),
//                QMessageBox::Yes | QMessageBox::No)
//            == QMessageBox::Yes)
//        {
//            HACC_DB->exec("delete from accounts where id=?", QVariantList() << id);
//            emit removed(id);
//        }
//    }
}


void CValuables::edit(const hacc::TDBID & id)
{
    //! \todo Реализовать редактирование ценности
//    if(id > 0)
//    {
//        ui::form::FAccountEdit *dialog = new ui::form::FAccountEdit(id);
//        if(dialog->exec() == QDialog::Accepted)
//        {
//            HACC_DB->exec("update accounts set name=?, icon_id=? where id=?", QVariantList()
//                          << dialog->name()
//                          << dialog->iconID()
//                          << id);
//            emit updated(id);
//        }
//        delete dialog;
//    }
}

QString CValuables::idToSerial(const hacc::TDBID & valuableID)
{
    return tr("virtual.") + QString::fromUtf8(QString::number(valuableID).toUtf8().toHex());
}

/** Вычисляет и возвращает список идентификаторов ценностей без
  * дополнительных передвижений. То есть:
  *     - для объектов - максимум одно передвижение(покупка)
  *     - для сервиса и расходников - максимум два передвижения (покупка+списание)
  */
hacc::TIDList CValuables::listVithoutMoving(const QString &where, const QVariantList &parameters)
{
    hacc::TIDList list;
    hacc::TDBID thingID;
    int moves;
    QSqlQuery q = HACC_DB->query("select "
                                 "valuables.id , "
                                 "count(movements.id) as moves, "
                                 "transactions_things.thing_id "
                                 "from valuables "
                                 "left join movements on movements.valuable_id=valuables.id "
                                 "left join transactions_things on transactions_things.id = valuables.transaction_id "
                                 "where " + where + " "
                                 "group by valuables.id", parameters);
    while(q.next())
    {
        thingID = HACC_DB_2_DBID(q, 2);
        moves   = HACC_DB_2_INTR(q, 1);
        if(
                ( HACC_THINGS->tagAttached(HACC_TAG_ID_OBJECT    , thingID)  && moves == 1) ||
                ((HACC_THINGS->tagAttached(HACC_TAG_ID_SERVICE   , thingID)                 ||
                  HACC_THINGS->tagAttached(HACC_TAG_ID_EXPENDABLE, thingID)) && moves == 2)
          )
        {
            list.append(HACC_DB_2_DBID(q, 0));
        }
    }
    return list;
}

void CValuables::tagsEdit(const hacc::TDBID & id)
{
    ui::form::TItemTagsEdit< ui::tag::TTagContainer<CValuable, CValuables> > *dialog =
            new ui::form::TItemTagsEdit< ui::tag::TTagContainer<CValuable, CValuables> >(id);
    if(dialog->exec() == QDialog::Accepted)
    {
    }
    delete dialog;
}

bool CValuables::checkSpetialPurposeTag(const hacc::TDBID &tagID)
{
    switch(tagID)
    {
        case HACC_TAG_ID_WRITE_OFF:
            return true;
    }
    return false;
}

QString CValuables::purposeTagsIDString()
{
    return QString("%0")
            .arg(HACC_TAG_ID_WRITE_OFF    );
}

       bool CValuables::hasPurposeTags() { return true; }
hacc::TDBID CValuables::maxDBID       () { return HACC_DB->nextID("valuables"); }

QAction * CValuables::generateAction(base::EActionsTypes atype, QObject *reciever, const char * method)
{
    switch(atype)
    {
        HACC_GENERATE_ACTION_CASE(base::atAdd     , tools::icons::iValuable, tools::icons::oNew   , tr("New valuable")   , tr("Add new valuable"));
        HACC_GENERATE_ACTION_CASE(base::atEdit    , tools::icons::iValuable, tools::icons::oEdit  , tr("Edit valuable")  , tr("Edit valuable"   ));
        HACC_GENERATE_ACTION_CASE(base::atRemove  , tools::icons::iValuable, tools::icons::oRemove, tr("Delete valuable"), tr("Delete valuable" ));
        HACC_GENERATE_ACTION_CASE(base::atTagsEdit, tools::icons::iValuable, tools::icons::oTag   , tr("Edit tags")      , tr("Edit tags"       ));
        default: break;
    }
    return new QAction("Somewhere bug", 0);
}


}
}
