#include "ctags.h"
#include "ftagedit.h"
#include "icons.h"
#include "st.h"

namespace hacc
{
namespace model
{

CTags::CTags() : base::CBases()
{
    m_tagTables << HACC_TAG_TABLE_NAME(thing)
                << HACC_TAG_TABLE_NAME(account)
                << HACC_TAG_TABLE_NAME(contractor)
                << HACC_TAG_TABLE_NAME(transaction)
                << HACC_TAG_TABLE_NAME(manufacturer)
                << HACC_TAG_TABLE_NAME(transactions_pool);
}

CTags::~CTags()
{}


QAction * CTags::addAction()
{
    return CBases::addAction(0, this, SLOT(add()));
}

void CTags::add()
{
    ui::form::FTagEdit *dialog = new ui::form::FTagEdit();
    if(dialog->exec() == QDialog::Accepted)
    {
        hacc::TDBID newID = nextID();
        HACC_DB->exec("insert into tags (id, name) values (?,?)",
                      QVariantList()
                      << newID
                      << dialog->name());
        emit created(newID);
    }
    delete dialog;
}

void CTags::remove(const hacc::TDBID & id)
{
    if(id > 0)
    {
        if(QMessageBox::question(
                HACC_WINDOW,
                tr("Tag remove"),
                tr("You sure you want to delete '%1' tag?").arg(tagName(id)),
                QMessageBox::Yes | QMessageBox::No)
            == QMessageBox::Yes)
        {
            HACC_DB->exec("delete from tags where id=?", QVariantList() << id);
            eachTagTableExecute("delete from %0 where tag_id=?", QVariantList() << id);
            emit removed(id);
        }
    }
}

void CTags::edit(const hacc::TDBID & id)
{
    if(id > 0)
    {
        ui::form::FTagEdit *dialog = new ui::form::FTagEdit(id);
        if(dialog->exec() == QDialog::Accepted)
        {
            HACC_DB->exec("update tags set name=? where id=?",
                          QVariantList()
                          << dialog->name()
                          << id);
            emit updated(id);
        }
        delete dialog;
    }
}

QString CTags::tagName(const hacc::TDBID & id)
{
    return HACC_DB->rowName("tags", id);
}

void CTags::eachTagTableExecute(const QString &sql, const QVariantList &parametres)
{
    foreach(QString table, m_tagTables)
    {
        HACC_DB->exec(sql.arg(table), parametres);
    }
}

bool CTags::checkSpetialPurposeTag(const hacc::TDBID &tagID)
{
    return
            HACC_ACCOUNTS          ->checkSpetialPurposeTag(tagID) ||
            HACC_CONTRACTORS       ->checkSpetialPurposeTag(tagID) ||
            HACC_MANUFACTURERS     ->checkSpetialPurposeTag(tagID) ||
            HACC_THINGS            ->checkSpetialPurposeTag(tagID) ||
            HACC_TRANSACTIONS      ->checkSpetialPurposeTag(tagID) ||
            HACC_TRANSACTIONS_POOLS->checkSpetialPurposeTag(tagID);
}


hacc::TDBID CTags::maxDBID() { return HACC_DB->nextID("tags"); }

QAction * CTags::generateAction(base::EActionsTypes atype, QObject *reciever, const char * method)
{
    switch(atype)
    {
        HACC_GENERATE_ACTION_CASE(base::atAdd     , tools::icons::iTag, tools::icons::oNew   , tr("New tag")   , tr("Add new tag"));
        HACC_GENERATE_ACTION_CASE(base::atEdit    , tools::icons::iTag, tools::icons::oEdit  , tr("Edit tag")  , tr("Edit tag"   ));
        HACC_GENERATE_ACTION_CASE(base::atRemove  , tools::icons::iTag, tools::icons::oRemove, tr("Delete tag"), tr("Delete tag" ));
        default: break;
    }
    return new QAction("Somewhere bug", 0);
}

//select
//  tags.id,
//  tags.name,
//  count(accounts_tags.tag_id) as accounts_count,
//  count(contractors_tags.tag_id) as contractors_count,
//  count(manufacturers_tags.tag_id) as manufacturers_count,
//  count(things_tags.tag_id) as things_count,
//  count(transactions_tags.tag_id) as transactions_count,
//  count(transactions_pools_tags.tag_id) as transactions_tags
//from tags
//left join accounts_tags on accounts_tags.tag_id=tags.id
//left join contractors_tags on contractors_tags.tag_id=tags.id
//left join manufacturers_tags on manufacturers_tags.tag_id=tags.id
//left join things_tags on things_tags.tag_id=tags.id
//left join transactions_tags on transactions_tags.tag_id=tags.id
//left join transactions_pools_tags on transactions_pools_tags.tag_id=tags.id
//group by tags.id

}
}
