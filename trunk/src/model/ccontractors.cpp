#include "ccontractors.h"
#include "fcontractoredit.h"
#include "titemtagsedit.h"
#include "st.h"
#include "icons.h"
#include "hacc_options.h"

#include "ttagcontainer.h"
#include "ccontractor.h"

namespace hacc
{
namespace model
{

CContractors::CContractors()
    : base::CBases(),
      hacc::model::CTagged(HACC_TAG_TABLE_NAME(contractor), HACC_TAG_TABLE_ID_NAME(contractor))
{}

CContractors::~CContractors()
{}

QAction * CContractors::addAction()
{
    return CBases::addAction(0, this, SLOT(add()));
}

QAction * CContractors::addSelfAction()
{
    return constructAction(base::atContractorAddSelf, 0, this, SLOT(addSelf()));
}

void CContractors::add()
{
    add(false);
}

void CContractors::addSelf()
{
    add(true);
}

void CContractors::add(bool isSelf)
{
    ui::form::FContractorEdit *dialog =
            new ui::form::FContractorEdit(isSelf);
    if(dialog->exec() == QDialog::Accepted)
    {
        hacc::TDBID newID = nextID();
        HACC_DB->exec("insert into contractors (id,name,icon_id,own_account) values (?,?,?,?)",
                      QVariantList()
                      << newID
                      << dialog->name()
                      << dialog->iconID()
                      << isSelf);
        HACC_ACCOUNTS->execAddAccount(newID, tr("Master account"), dialog->iconID(), HACC_O_DEFAULT_CURRENCY);
        emit created(newID);
    }
    delete dialog;
}

void CContractors::remove(const hacc::TDBID & id)
{
    if(id > 0)
    {
        QSqlQuery q = HACC_DB->query("select name from contractors where id=?", QVariantList() << id);
        q.next();
        if(QMessageBox::question(
                HACC_WINDOW,
                tr("Contractor remove"),
                tr("You sure you want to delete '%1' contractor with her accounts?").arg(HACC_DB_2_STRG(q, 0)),
                QMessageBox::Yes | QMessageBox::No)
            == QMessageBox::Yes)
        {
            HACC_DB->exec("delete from contractors where id=?", QVariantList() << id);
            HACC_ACCOUNTS->removeContractorAccounts(id);
            emit removed(id);
        }
    }
}

void CContractors::edit(const hacc::TDBID & id)
{
    if(id > 0)
    {
        ui::form::FContractorEdit *dialog = new ui::form::FContractorEdit(id);
        if(dialog->exec() == QDialog::Accepted)
        {
            HACC_DB->exec("update contractors set name=?, icon_id=? where id=?", QVariantList()
                          << dialog->name()
                          << dialog->iconID()
                          << id);
            emit updated(id);
        }
        delete dialog;
    }
}

void CContractors::tagsEdit(const hacc::TDBID & id)
{
    ui::form::TItemTagsEdit< ui::tag::TTagContainer < CContractor, CContractors > > *dialog =
            new ui::form::TItemTagsEdit< ui::tag::TTagContainer < CContractor, CContractors > >(id);
    if(dialog->exec() == QDialog::Accepted)
    {}
    delete dialog;
}

bool CContractors::checkSpetialPurposeTag(const hacc::TDBID &tagID)
{
    Q_UNUSED(tagID);
    return false;
}

    QString CContractors::purposeTagsIDString() { return ""; }
       bool CContractors::hasPurposeTags     () { return false; }
hacc::TDBID CContractors::maxDBID            () { return HACC_DB->nextID("contractors"); }

QAction * CContractors::generateAction(base::EActionsTypes atype, QObject *reciever, const char * method)
{
    switch(atype)
    {
        HACC_GENERATE_ACTION_CASE(base::atAdd              , tools::icons::iContractor    , tools::icons::oNew   , tr("New contractor")      , tr("Add new contractor"      ));
        HACC_GENERATE_ACTION_CASE(base::atContractorAddSelf, tools::icons::iContractorSelf, tools::icons::oNew   , tr("New, self contractor"), tr("Add new, self contractor"));
        HACC_GENERATE_ACTION_CASE(base::atEdit             , tools::icons::iContractor    , tools::icons::oEdit  , tr("Edit contractor")     , tr("Edit contractor"         ));
        HACC_GENERATE_ACTION_CASE(base::atRemove           , tools::icons::iContractor    , tools::icons::oRemove, tr("Delete contractor")   , tr("Delete contractor"       ));
        HACC_GENERATE_ACTION_CASE(base::atTagsEdit         , tools::icons::iContractor    , tools::icons::oTag   , tr("Edit tags")           , tr("Edit tags"               ));
        default: break;
    }
    return new QAction("Somewhere bug", 0);
}


}
}
