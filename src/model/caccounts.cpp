#include "faccountedit.h"
#include "titemtagsedit.h"
#include "caccounts.h"
#include "icons.h"
#include "st.h"

#include "ttagcontainer.h"
#include "caccount.h"

namespace hacc
{
namespace model
{

CAccounts::CAccounts()
    : base::CBases(),
      hacc::model::CTagged(HACC_TAG_TABLE_NAME(account), HACC_TAG_TABLE_ID_NAME(account))
{}

CAccounts::~CAccounts()
{}

void CAccounts::add(const hacc::TDBID & contractorID)
{
    ui::form::FAccountEdit *dialog = new ui::form::FAccountEdit();
    if(dialog->exec() == QDialog::Accepted)
    {
        execAddAccount(contractorID, dialog->name(), dialog->iconId());
    }
    delete dialog;
}

void CAccounts::execAddAccount(const hacc::TDBID & contractorID, const QString &name, const hacc::TDBID & iconID)
{
    hacc::TDBID newID = nextID();
    HACC_DB->exec("insert into accounts (id,name,icon_id,contractor_id) values (?,?,?,?)",
                  QVariantList()
                  << newID
                  << name
                  << iconID
                  << contractorID);
    emit created(newID);
}

void CAccounts::remove(const hacc::TDBID & id)
{
    if(id > 0)
    {
        QSqlQuery q = HACC_DB->query("select name from accounts where id=?", QVariantList() << id);
        q.next();
        if(QMessageBox::question(
                HACC_WINDOW,
                tr("Account remove"),
                tr("You sure you want to delete '%1' account?").arg(HACC_DB_2_STRG(q, 0)),
                QMessageBox::Yes | QMessageBox::No)
            == QMessageBox::Yes)
        {

            /** \todo Проследить за тем, чтобы транзакциии не остались без счетов при удалении счета
                как минимум - перерулить все транзакции по данному счету на Ничто.
                Или перерулить На другой счет контрагента.
                Или удалить все нахер.
                В общем надо спросить пользователя.
              */
            HACC_DB->exec("delete from accounts where id=?", QVariantList() << id);
            emit removed(id);
        }
    }
}

void CAccounts::removeContractorAccounts(const hacc::TDBID & contractorID)
{
    //! \todo тоже самое что и в remove()
    hacc::TIDList list = HACC_DB->listID("accounts", "contractor_id=?", QVariantList() << contractorID);
    HACC_DB->exec("delete from accounts where contractor_id=?", QVariantList() << contractorID);
    foreach(hacc::TDBID id, list)
    {
        emit removed(id);
    }
}

void CAccounts::edit(const hacc::TDBID & id)
{
    if(id > 0)
    {
        ui::form::FAccountEdit *dialog = new ui::form::FAccountEdit(id);
        if(dialog->exec() == QDialog::Accepted)
        {
            HACC_DB->exec("update accounts set name=?, icon_id=? where id=?", QVariantList()
                          << dialog->name()
                          << dialog->iconId()
                          << id);
            emit updated(id);
        }
        delete dialog;
    }
}

hacc::TDBID CAccounts::contractor(const hacc::TDBID & accountID)
{
    return HACC_DB->queryCell("select contractor_id from accounts where id=?", 1, QVariantList() << accountID).toUInt();
}

void CAccounts::tagsEdit(const hacc::TDBID & id)
{
    ui::form::TItemTagsEdit< ui::tag::TTagContainer<CAccount, CAccounts> > *dialog =
            new ui::form::TItemTagsEdit< ui::tag::TTagContainer<CAccount, CAccounts> >(id);
    if(dialog->exec() == QDialog::Accepted)
    {}
    delete dialog;
}

bool CAccounts::checkSpetialPurposeTag(const hacc::TDBID &tagID)
{
    Q_UNUSED(tagID);
    return false;
}

    QString CAccounts::purposeTagsIDString() { return ""; }
       bool CAccounts::hasPurposeTags     () { return false; }
hacc::TDBID CAccounts::maxDBID            () { return HACC_DB->nextID("accounts"); }

QAction * CAccounts::generateAction(base::EActionsTypes atype, QObject *reciever, const char * method)
{
    switch(atype)
    {
        HACC_GENERATE_ACTION_CASE(base::atAdd     , tools::icons::iAccount, tools::icons::oNew   , tr("New account")   , tr("Add new account"));
        HACC_GENERATE_ACTION_CASE(base::atEdit    , tools::icons::iAccount, tools::icons::oEdit  , tr("Edit account")  , tr("Edit account"   ));
        HACC_GENERATE_ACTION_CASE(base::atRemove  , tools::icons::iAccount, tools::icons::oRemove, tr("Delete account"), tr("Delete account" ));
        HACC_GENERATE_ACTION_CASE(base::atTagsEdit, tools::icons::iAccount, tools::icons::oTag   , tr("Edit tags")     , tr("Edit tags"      ));
        default: break;
    }
    return new QAction("Somewhere bug", 0);
}

}
}
