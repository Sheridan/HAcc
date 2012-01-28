#include "ccurrencyes.h"
#include "fcurrencyedit.h"
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
    ui::form::FCurrencyEdit *dialog =
            new ui::form::FCurrencyEdit();
    if(dialog->exec() == QDialog::Accepted)
    {
        execAddCurrency(dialog->name(), dialog->reduction(), dialog->reductionBeforeNumber(), dialog->iconID());
    }
    delete dialog;
}

void CCurrencyes::remove(const hacc::TDBID & id)
{
    if(id > 0)
    {
        //! \todo Придумать что делать, ежели есть операции с данной валютой
        QSqlQuery q = HACC_DB->query("select name from currencyes where id=?", QVariantList() << id);
        q.next();
        if(QMessageBox::question(
                HACC_WINDOW,
                tr("Currency remove"),
                tr("You sure you want to delete '%1' currency?").arg(HACC_DB_2_STRG(q, 0)),
                QMessageBox::Yes | QMessageBox::No)
            == QMessageBox::Yes)
        {
            HACC_DB->exec("delete from currencyes where id=?", QVariantList() << id);
            emit removed(id);
        }
    }
}

void CCurrencyes::edit(const hacc::TDBID & id)
{
    if(id > 0)
    {
        ui::form::FCurrencyEdit *dialog = new ui::form::FCurrencyEdit(id);
        if(dialog->exec() == QDialog::Accepted)
        {
            HACC_DB->exec("update currencyes set name=?, icon_id=?, reduction=?, show_reduction_before_value=? where id=?", QVariantList()
                          << dialog->name()
                          << dialog->iconID()
                          << dialog->reduction()
                          << dialog->reductionBeforeNumber()
                          << id);
            emit updated(id);
        }
        delete dialog;
    }
}

void CCurrencyes::execAddCurrency(const QString &name, const QString &reduction,
                                  const bool &reductionBeforeNumber, const hacc::TDBID iconID)
{
    hacc::TDBID newID = nextID();
    HACC_DB->exec("insert into currencyes (id,name,icon_id,reduction,show_reduction_before_value) values (?,?,?,?,?)",
                  QVariantList()
                  << newID
                  << name
                  << iconID
                  << reduction
                  << reductionBeforeNumber);
    HACC_ACCOUNTS->execAddAccount(1, tr("Nowhere"), 1, newID);
    emit created(newID);
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
