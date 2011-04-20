#include "cmanufacturers.h"
#include "fmanufactureredit.h"
#include "titemtagsedit.h"
#include "ttagcontainer.h"
#include "cmanufacturer.h"
#include "icons.h"
#include "st.h"

namespace hacc
{
namespace model
{

CManufacturers::CManufacturers()
    : base::CBases(),
      hacc::model::CTagged(HACC_TAG_TABLE_NAME(manufacturer), HACC_TAG_TABLE_ID_NAME(manufacturer))
{}

CManufacturers::~CManufacturers()
{}

QAction * CManufacturers::addAction()
{
    return CBases::addAction(0, this, SLOT(add()));
}

void CManufacturers::add()
{
    ui::form::FManufacturerEdit *dialog = new ui::form::FManufacturerEdit();
    if(dialog->exec() == QDialog::Accepted)
    {
        hacc::TDBID newID = nextID();
        HACC_DB->exec("insert into manufacturers (id, name, description, icon_id, image) values (?,?,?,?,?)",
                      QVariantList()
                      << newID
                      << dialog->name()
                      << dialog->description()
                      << dialog->iconID()
                      << (dialog->hasImage() ? QVariant(dialog->pixmapData()) : QVariant(QVariant::ByteArray)));
        emit created(newID);
    }
    delete dialog;
}

void CManufacturers::remove(const hacc::TDBID & id)
{
    if(id > 0)
    {
        if(QMessageBox::question(
                HACC_WINDOW,
                tr("Manufacturer remove"),
                tr("You sure you want to delete '%1' manufacturer?").arg(HACC_DB->rowName("manufacturers", id)),
                QMessageBox::Yes | QMessageBox::No)
            == QMessageBox::Yes)
        {
            HACC_DB->exec("delete from manufacturers where id=?", QVariantList() << id);
            HACC_THINGS->removeManufacturer(id);
            emit removed(id);
        }
    }
}

void CManufacturers::edit(const hacc::TDBID & id)
{
    if(id > 0)
    {
        ui::form::FManufacturerEdit *dialog = new ui::form::FManufacturerEdit(id);
        if(dialog->exec() == QDialog::Accepted)
        {
            HACC_DB->exec("update manufacturers set name=?, description=?, icon_id=?, image=? where id=?",
                          QVariantList()
                          << dialog->name()
                          << dialog->description()
                          << dialog->iconID()
                          << (dialog->hasImage() ? QVariant(dialog->pixmapData()) : QVariant(QVariant::ByteArray))
                          << id);
            emit updated(id);
        }
        delete dialog;
    }
}

QString CManufacturers::manufacturerName(const hacc::TDBID & id)
{
    return HACC_DB->rowName("manufacturers", id);
}

void CManufacturers::tagsEdit(const hacc::TDBID & id)
{
    ui::form::TItemTagsEdit< ui::tag::TTagContainer < CManufacturer, CManufacturers > > *dialog =
            new ui::form::TItemTagsEdit< ui::tag::TTagContainer < CManufacturer, CManufacturers > >(id);
    if(dialog->exec() == QDialog::Accepted)
    {
    }
    delete dialog;
}

bool CManufacturers::checkSpetialPurposeTag(const hacc::TDBID &tagID)
{
    Q_UNUSED(tagID);
    return false;
}

    QString CManufacturers::purposeTagsIDString() { return ""; }
       bool CManufacturers::hasPurposeTags     () { return false; }
hacc::TDBID CManufacturers::maxDBID            () { return HACC_DB->nextID("manufacturers"); }

QAction * CManufacturers::generateAction(base::EActionsTypes atype, QObject *reciever, const char * method)
{
    switch(atype)
    {
        HACC_GENERATE_ACTION_CASE(base::atAdd     , tools::icons::iManufacturer, tools::icons::oNew   , tr("New manufacturer")   , tr("Add new manufacturer"));
        HACC_GENERATE_ACTION_CASE(base::atEdit    , tools::icons::iManufacturer, tools::icons::oEdit  , tr("Edit manufacturer")  , tr("Edit manufacturer"   ));
        HACC_GENERATE_ACTION_CASE(base::atRemove  , tools::icons::iManufacturer, tools::icons::oRemove, tr("Delete manufacturer"), tr("Delete manufacturer" ));
        HACC_GENERATE_ACTION_CASE(base::atTagsEdit, tools::icons::iManufacturer, tools::icons::oTag   , tr("Edit tags")          , tr("Edit tags"       ));
        default: break;
    }
    return new QAction("Somewhere bug", 0);
}

}
}
