#include "cthings.h"
#include "icons.h"
#include "st.h"
#include "fthingedit.h"
#include "titemtagsedit.h"
#include "ttagcontainer.h"
#include "cthing.h"

namespace hacc
{
namespace model
{

CThings::CThings()
    : base::CBases(),
      hacc::model::CTagged(HACC_TAG_TABLE_NAME(thing), HACC_TAG_TABLE_ID_NAME(thing))
{}

CThings::~CThings()
{}

QAction * CThings::addAction()
{
    return CBases::addAction(0, this, SLOT(add()));
}

void CThings::add()
{
    ui::form::FThingEdit *dialog = new ui::form::FThingEdit();
    if(dialog->exec() == QDialog::Accepted)
    {
        hacc::TDBID newID = nextID();
        HACC_DB->exec("insert into things "
                      "("
                      "id,"
                      "name,"
                      "description,"
                      "icon_id,"
                      "image,"
                      "enumerated_type_id,"
                      "manufacturer_id,"
                      "expiration_period,"
                      "guarantee_period"
                      ") "
                      "values (?,?,?,?,?,?,?,?,?)",
                      QVariantList()
                      << newID
                      << dialog->name()
                      << dialog->description()
                      << dialog->iconId()
                      << (dialog->hasImage() ? QVariant(dialog->pixmapData()) : QVariant(QVariant::ByteArray))
                      << dialog->enumeratedTypeThingId()
                      << dialog->manufacturerId()
                      << dialog->expiration()
                      << dialog->guarantee());
        attachTag(HACC_TAG_ID_SERVICE   , newID, dialog->thingType() == HACC_TAG_ID_SERVICE   );
        attachTag(HACC_TAG_ID_OBJECT    , newID, dialog->thingType() == HACC_TAG_ID_OBJECT    );
        attachTag(HACC_TAG_ID_EXPENDABLE, newID, dialog->thingType() == HACC_TAG_ID_EXPENDABLE);
        emit created(newID);
    }
    delete dialog;
}

void CThings::remove(const hacc::TDBID & id)
{
    if(id > 0)
    {
        if(QMessageBox::question(
                HACC_WINDOW,
                tr("Thing remove"),
                tr("You sure you want to delete '%1' thing? "
                   "This set this things in transactions to 'Unknown thing' "
                   "and remove copies of this thing out of the values").arg(HACC_DB->rowName("things", id)),
                QMessageBox::Yes | QMessageBox::No)
            == QMessageBox::Yes)
        {
            HACC_DB->exec("delete from things where id=?", QVariantList() << id);
            HACC_TRANSACTIONS->cleanAfterThingRemove(id);
            HACC_VALUABLES->thingRemoved(id);
            emit removed(id);
        }
    }
}

void CThings::edit(const hacc::TDBID & id)
{
    if(id > 0)
    {
        ui::form::FThingEdit *dialog = new ui::form::FThingEdit(id);
        if(dialog->exec() == QDialog::Accepted)
        {
            HACC_DB->exec("update things set "
                          "name=?,"
                          "description=?,"
                          "icon_id=?,"
                          "image=?,"
                          "enumerated_type_id=?,"
                          "manufacturer_id=?,"
                          "expiration_period=?,"
                          "guarantee_period=? "
                          "where id=?",
                          QVariantList()
                          << dialog->name()
                          << dialog->description()
                          << dialog->iconId()
                          << (dialog->hasImage() ? QVariant(dialog->pixmapData()) : QVariant(QVariant::ByteArray))
                          << dialog->enumeratedTypeThingId()
                          << dialog->manufacturerId()
                          << dialog->expiration()
                          << dialog->guarantee()
                          << id);
            attachTag(HACC_TAG_ID_SERVICE   , id, dialog->thingType() == HACC_TAG_ID_SERVICE   );
            attachTag(HACC_TAG_ID_OBJECT    , id, dialog->thingType() == HACC_TAG_ID_OBJECT    );
            attachTag(HACC_TAG_ID_EXPENDABLE, id, dialog->thingType() == HACC_TAG_ID_EXPENDABLE);
            HACC_VALUABLES->thingUpdated(id);
            emit updated(id);
        }
        delete dialog;
    }
}

void CThings::removeEnumeratedType(const hacc::TDBID & etId)
{
    hacc::TIDList list = HACC_DB->listID("things", "enumerated_type_id=?", QVariantList() << etId);
    HACC_DB->exec("update things set enumerated_type_id=1 where enumerated_type_id=?", QVariantList() << etId);
    foreach(hacc::TDBID id, list)
    {
        emit updated(id);
    }
}

void CThings::removeManufacturer(const hacc::TDBID & mId)
{
    hacc::TIDList list = HACC_DB->listID("things", "manufacturer_id=?", QVariantList() << mId);
    HACC_DB->exec("update things set manufacturer_id=1 where manufacturer_id=?", QVariantList() << mId);
    foreach(hacc::TDBID id, list)
    {
        emit updated(id);
    }
}

QString CThings::thingName(const hacc::TDBID & id)
{
    return HACC_DB->rowName("things", id);
}

void CThings::tagsEdit(const hacc::TDBID & id)
{
    ui::form::TItemTagsEdit< ui::tag::TTagContainer < CThing, CThings > > *dialog =
            new ui::form::TItemTagsEdit< ui::tag::TTagContainer < CThing, CThings > >(id);
    if(dialog->exec() == QDialog::Accepted)
    {
    }
    delete dialog;
}

bool CThings::checkSpetialPurposeTag(const hacc::TDBID &tagID)
{
    switch(tagID)
    {
        case HACC_TAG_ID_SERVICE   :
        case HACC_TAG_ID_OBJECT    :
        case HACC_TAG_ID_EXPENDABLE:
            return true;
    }
    return false;
}

QString CThings::purposeTagsIDString()
{
    return QString("%0,%1,%2")
            .arg(HACC_TAG_ID_SERVICE   )
            .arg(HACC_TAG_ID_OBJECT    )
            .arg(HACC_TAG_ID_EXPENDABLE);
}

       bool CThings::hasPurposeTags() { return true; }
hacc::TDBID CThings::maxDBID       () { return HACC_DB->nextID("things"); }


QAction * CThings::generateAction(base::EActionsTypes atype, QObject *reciever, const char * method)
{
    switch(atype)
    {
        HACC_GENERATE_ACTION_CASE(base::atAdd     , tools::icons::iThing, tools::icons::oNew   , tr("New thing")   , tr("Add new thing"));
        HACC_GENERATE_ACTION_CASE(base::atEdit    , tools::icons::iThing, tools::icons::oEdit  , tr("Edit thing")  , tr("Edit thing"   ));
        HACC_GENERATE_ACTION_CASE(base::atRemove  , tools::icons::iThing, tools::icons::oRemove, tr("Delete thing"), tr("Delete thing" ));
        HACC_GENERATE_ACTION_CASE(base::atTagsEdit, tools::icons::iThing, tools::icons::oTag   , tr("Edit tags")   , tr("Edit tags"    ));
        default: break;
    }
    return new QAction("Somewhere bug", 0);
}



/*

  ----------------- выборка вещей по типам --------------
select
things.id,
things.name,
tags.name
from things
left join things_tags on things_tags.thing_id=things.id
left join tags on tags.id=things_tags.tag_id
where tags.name not null and tags.id=?

*/
}
}
