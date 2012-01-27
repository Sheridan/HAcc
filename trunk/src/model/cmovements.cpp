#include "cmovements.h"
#include "titemtagsedit.h"
#include "icons.h"
#include "convert.h"
#include "st.h"

#include "ttagcontainer.h"
#include "cmovement.h"

namespace hacc
{
namespace model
{

CMovements::CMovements()
    : base::CBases(),
      hacc::model::CTagged(HACC_TAG_TABLE_NAME(movement), HACC_TAG_TABLE_ID_NAME(movement))
{}

CMovements::~CMovements()
{}

QAction *CMovements::addTransactionGiveGiftAction     () { return constructAction(base::atTransactionGiveGift     , 0, this, SLOT(addTransactionGiveGift  ())   ); }
QAction *CMovements::addTransactionAcceptGiftAction   () { return constructAction(base::atTransactionAcceptGift   , 0, this, SLOT(addTransactionAcceptGift())   ); }

void CMovements::add()
{}

void CMovements::thingRemoved(const hacc::TDBID & thingID)
{
    //! \todo Реализовать действие при удалении вещи
//    QSqlQuery q = HACC_DB->query("select "
//                                 "transactions_things.id "
//                                 "from transactions_things "
//                                 "where transactions_things.thing_id=?",
//                                 QVariantList() << thingID);
//    while(q.next())
//    {
//        remove("transaction_id=?", QVariantList() << q.value(0).toUInt());
//    }
}

void CMovements::remove(const hacc::TDBID & id)
{
    //! \todo Реализовать удаление перемещения. А надо ли?
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

void CMovements::remove(const hacc::TIDList & idList)
{
    HACC_DB->exec("delete from movements where id in (" + tools::convert::idListToString(idList) + ")");
    foreach(hacc::TDBID id, idList)
    {
        //! \todo проследить, чтобы удалились перемещения
        detachTags(id);
        emit removed(id);
    }
}

void CMovements::removeValuableMovements(const hacc::TIDList & idListValuables)
{
    remove(HACC_DB->listID("movements", "valuable_id in (" + tools::convert::idListToString(idListValuables) + ")"));
}

void CMovements::execRemove(const QString &where, const QVariantList &parameters)
{
    remove(HACC_DB->listID("movements", where, parameters));
}


void CMovements::edit(const hacc::TDBID & id)
{
    //! \todo Реализовать редактирование перемещения. Надо ли?
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

void CMovements::execMoveGift(const int &movementType)
{
    //! \todo Реализовать перемещение подарка
//    ui::form::FTransactionGiftEdit *dialog = new ui::form::FTransactionGiftEdit(tpType);
//    if(dialog->exec() == QDialog::Accepted)
//    {
//        hacc::TDBID srcAcc = HACC_DB->rowID("accounts", "contractor_id=?", QVariantList() << dialog->source());
//        hacc::TDBID dstAcc = HACC_DB->rowID("accounts", "contractor_id=?", QVariantList() << dialog->destination());
//        hacc::TDBID newID = execAddTransactionPool(tpType, dialog->datetime(), srcAcc, dstAcc);
//        HACC_TRANSACTIONS->addGiftTransaction(tType, newID, dialog->thing(), dialog->valuable());
//    }
//    delete dialog;
}


void CMovements::addTransactionGiveGift     () { execMoveGift (HACC_TAG_ID_GIFT_GIVE  ); }
void CMovements::addTransactionAcceptGift   () { execMoveGift (HACC_TAG_ID_GIFT_ACCEPT); }

hacc::TDBID CMovements::moveThing(const hacc::TDBID &sourceContractor, const hacc::TDBID &destinationContractor,
                           const hacc::TDBID &valuable, const QDateTime &datetime,
                           const int &movementType)
{
    hacc::TDBID newID = nextID();
    HACC_DB->exec("insert into movements (id,date_time,valuable_id,source_contractor_id,destination_contractor_id) values (?,?,?,?,?)",
                  QVariantList()
                  << newID
                  << datetime
                  << valuable
                  << sourceContractor
                  << destinationContractor);
    attachTag(movementType, newID);
    emit created(newID);
    return newID;
}

void CMovements::writeOff(const hacc::TDBID &owner, const hacc::TDBID &valuable, const QDateTime &datetime)
{
    hacc::TDBID newID = nextID();
    HACC_DB->exec("insert into movements (id,date_time,valuable_id,source_contractor_id,destination_contractor_id) values (?,?,?,?,?)",
                  QVariantList() << newID << datetime << valuable << owner << 1);
    attachTag(HACC_TAG_ID_WRITE_OFF , newID);
    HACC_VALUABLES->attachTag(HACC_TAG_ID_WRITE_OFF, valuable);
    emit created(newID);
}

void CMovements::tagsEdit(const hacc::TDBID & id)
{
    ui::form::TItemTagsEdit< ui::tag::TTagContainer<CMovement, CMovements> > *dialog =
            new ui::form::TItemTagsEdit< ui::tag::TTagContainer<CMovement, CMovements> >(id);
    if(dialog->exec() == QDialog::Accepted)
    {}
    delete dialog;
}

bool CMovements::checkSpecialPurposeTag(const hacc::TDBID &tagID)
{
    switch(tagID)
    {
        case HACC_TAG_ID_BUYING     :
        case HACC_TAG_ID_SELLING    :
        case HACC_TAG_ID_GIFT_ACCEPT:
        case HACC_TAG_ID_GIFT_GIVE  :
        case HACC_TAG_ID_WRITE_OFF  :
            return true;
    }
    return false;
}

QString CMovements::purposeTagsIDString()
{
    return QString("%0,%1,%2,%3,%4")
            .arg(HACC_TAG_ID_BUYING     )
            .arg(HACC_TAG_ID_SELLING    )
            .arg(HACC_TAG_ID_GIFT_ACCEPT)
            .arg(HACC_TAG_ID_GIFT_GIVE  )
            .arg(HACC_TAG_ID_WRITE_OFF  );
}

       bool CMovements::hasPurposeTags() { return true; }
hacc::TDBID CMovements::maxDBID       () { return HACC_DB->nextID("movements"); }

QAction * CMovements::generateAction(base::EActionsTypes atype, QObject *reciever, const char * method)
{
    switch(atype)
    {
        HACC_GENERATE_ACTION_CASE(base::atAdd                  , tools::icons::iMovement, tools::icons::oIncoming, tr("New movement")   , tr("Add movement"    ));
        HACC_GENERATE_ACTION_CASE(base::atEdit                 , tools::icons::iMovement, tools::icons::oEdit    , tr("Edit movement")  , tr("Edit movement"   ));
        HACC_GENERATE_ACTION_CASE(base::atRemove               , tools::icons::iMovement, tools::icons::oRemove  , tr("Delete movement"), tr("Delete movement" ));
        HACC_GENERATE_ACTION_CASE(base::atTagsEdit             , tools::icons::iMovement, tools::icons::oTag     , tr("Edit tags")      , tr("Edit tags"       ));
        HACC_GENERATE_ACTION_CASE(base::atTransactionGiveGift  , tools::icons::iGift    , tools::icons::oOutgoing, tr("Give gift")      , tr("Give gift"       ));
        HACC_GENERATE_ACTION_CASE(base::atTransactionAcceptGift, tools::icons::iGift    , tools::icons::oIncoming, tr("Accept gift")    , tr("Accept gift"     ));
        default: break;
    }
    return new QAction("Somewhere bug", 0);
}


}
}
