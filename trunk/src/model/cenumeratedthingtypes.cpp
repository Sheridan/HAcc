#include "cenumeratedthingtypes.h"
#include "fthingenumeratedtypesedit.h"
#include "icons.h"
#include "st.h"

namespace hacc
{
namespace model
{

CEnumeratedThingTypes::CEnumeratedThingTypes() : base::CBases()
{}

CEnumeratedThingTypes::~CEnumeratedThingTypes()
{}

QAction * CEnumeratedThingTypes::addAction()
{
    return CBases::addAction(0, this, SLOT(add()));
}

void CEnumeratedThingTypes::add()
{
    ui::form::FThingEnumeratedTypesEdit *dialog = new ui::form::FThingEnumeratedTypesEdit();
    if(dialog->exec() == QDialog::Accepted)
    {
        hacc::TDBID newID = nextID();
        HACC_DB->exec("insert into thing_enumerated_types (id, name, precision) values (?,?,?)",
                      QVariantList()
                      << newID
                      << dialog->name()
                      << dialog->precision());
        emit created(newID);
    }
    delete dialog;
}

void CEnumeratedThingTypes::edit(const hacc::TDBID & id)
{
    ui::form::FThingEnumeratedTypesEdit *dialog = new ui::form::FThingEnumeratedTypesEdit(id);
    if(dialog->exec() == QDialog::Accepted)
    {
        HACC_DB->exec("update thing_enumerated_types set name=? precision=? where id=?",
                      QVariantList()
                      << dialog->name()
                      << dialog->precision()
                      << id);
        emit updated(id);
    }
    delete dialog;
}

void CEnumeratedThingTypes::remove(const hacc::TDBID & id)
{
    if(id > 0)
    {
        if(QMessageBox::question(
                HACC_WINDOW,
                tr("Thing remove"),
                tr("You sure you want to delete '%1' thing enumerate type?")
                    .arg(thingEnumerateTypeName(id)),
                QMessageBox::Yes | QMessageBox::No)
            == QMessageBox::Yes)
        {
            HACC_DB->exec("delete from thing_enumerated_types where id=?", QVariantList() << id);
            emit removed(id);
            HACC_THINGS->removeEnumeratedType(id);
        }
    }
}

QString CEnumeratedThingTypes::thingEnumerateTypeName(const hacc::TDBID & id)
{
    return HACC_DB->rowName("thing_enumerated_types", id);
}

hacc::TDBID CEnumeratedThingTypes::maxDBID() { return HACC_DB->nextID("thing_enumerated_types"); }

bool CEnumeratedThingTypes::checkSpetialEnumeratedType(const hacc::TDBID &typeID)
{
    return typeID <= 3;
}

bool CEnumeratedThingTypes::checkDivisibleEnumeratedType(const hacc::TDBID &typeID)
{
    return typeID >= 2 && typeID <=3;
}

QAction * CEnumeratedThingTypes::generateAction(base::EActionsTypes atype, QObject *reciever, const char * method)
{
    switch(atype)
    {
        HACC_GENERATE_ACTION_CASE(base::atAdd     , tools::icons::iEnumerated, tools::icons::oNew   , tr("New enumerated type")   , tr("Add new enumerated type"));
        HACC_GENERATE_ACTION_CASE(base::atEdit    , tools::icons::iEnumerated, tools::icons::oEdit  , tr("Edit enumerated type")  , tr("Edit enumerated type"   ));
        HACC_GENERATE_ACTION_CASE(base::atRemove  , tools::icons::iEnumerated, tools::icons::oRemove, tr("Delete enumerated type"), tr("Delete enumerated type" ));
        default: break;
    }
    return new QAction("Somewhere bug", 0);
}

}
}
