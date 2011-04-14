#include "ccurrencyes.h"
//#include "fcontractoredit.h"
#include "st.h"
#include "icons.h"

namespace hacc
{
namespace model
{

CCurrencyes::CCurrencyes()
    : base::CBases()
{}

CCurrencyes::~CCurrencyes()
{}

QAction * CCurrencyes::addAction()
{
    return CBases::addAction(0, this, SLOT(add()));
}

void CCurrencyes::add()
{
//    ui::form::FContractorEdit *dialog =
//            new ui::form::FContractorEdit(isSelf);
//    if(dialog->exec() == QDialog::Accepted)
//    {
//        hacc::TDBID newID = nextID();
//        HACC_DB->exec("insert into contractors (id,name,icon_id,own_account) values (?,?,?,?)",
//                      QVariantList()
//                      << newID
//                      << dialog->name()
//                      << dialog->iconId()
//                      << isSelf);
//        HACC_ACCOUNTS->execAddAccount(newID, tr("Master account"), dialog->iconId());
//        emit created(newID);
//    }
//    delete dialog;
}

void CCurrencyes::remove(const hacc::TDBID & id)
{
    if(id > 0)
    {
//        QSqlQuery q = HACC_DB->query("select name from contractors where id=?", QVariantList() << id);
//        q.next();
//        if(QMessageBox::question(
//                HACC_WINDOW,
//                tr("Contractor remove"),
//                tr("You sure you want to delete '%1' contractor with her accounts?").arg(HACC_DB_2_STRG(q, 0)),
//                QMessageBox::Yes | QMessageBox::No)
//            == QMessageBox::Yes)
//        {
//            HACC_DB->exec("delete from contractors where id=?", QVariantList() << id);
//            HACC_ACCOUNTS->removeContractorAccounts(id);
//            emit removed(id);
//        }
    }
}

void CCurrencyes::edit(const hacc::TDBID & id)
{
    if(id > 0)
    {
//        ui::form::FContractorEdit *dialog = new ui::form::FContractorEdit(id);
//        if(dialog->exec() == QDialog::Accepted)
//        {
//            HACC_DB->exec("update contractors set name=?, icon_id=? where id=?", QVariantList()
//                          << dialog->name()
//                          << dialog->iconId()
//                          << id);
//            emit updated(id);
//        }
//        delete dialog;
    }
}

hacc::TDBID CCurrencyes::maxDBID() { return HACC_DB->nextID("currencyes"); }

QAction * CCurrencyes::generateAction(base::EActionsTypes atype, QObject *reciever, const char * method)
{
    switch(atype)
    {
        HACC_GENERATE_ACTION_CASE(base::atAdd   , tools::icons::iCurrency, tools::icons::oNew   , tr("New curency")   , tr("Add new curency"));
        HACC_GENERATE_ACTION_CASE(base::atEdit  , tools::icons::iCurrency, tools::icons::oEdit  , tr("Edit curency")  , tr("Edit curency"   ));
        HACC_GENERATE_ACTION_CASE(base::atRemove, tools::icons::iCurrency, tools::icons::oRemove, tr("Delete curency"), tr("Delete curency" ));
        default: break;
    }
    return new QAction("Somewhere bug", 0);
}


}
}
