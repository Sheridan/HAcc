#ifndef CACCOUNTS_H
#define CACCOUNTS_H
#include "cbases.h"
#include "ctagged.h"

namespace hacc
{
namespace model
{
//! Синглон счетов контрагентов
/*!
 Управляет счетами контрагентов. Непосредственно управляет таблицами
     - accounts
 @see CAccount
*/
class CAccounts :
        public base::CBases,
        public hacc::model::CTagged
{
    Q_OBJECT
public:
    CAccounts();
    ~CAccounts();
    void remove(const hacc::TDBID & id);
    void edit(const hacc::TDBID & id);
    void add(const hacc::TDBID & contractorID);
    void execAddAccount(const hacc::TDBID & contractorID, const QString &name, const hacc::TDBID & iconID);
    void removeContractorAccounts(const hacc::TDBID & contractorID); //!< Удаляет счета контрагента
    void tagsEdit(const hacc::TDBID & id);
    hacc::TDBID contractor(const hacc::TDBID & accountID); //!< Возвращает контрагента - владельца счета
    bool checkSpetialPurposeTag(const hacc::TDBID &tagID);
    QString purposeTagsIDString();
    bool    hasPurposeTags();

private:
    QAction * generateAction(base::EActionsTypes atype, QObject *reciever, const char * method);
    hacc::TDBID maxDBID();
};

}
}
#endif // CACCOUNTS_H
