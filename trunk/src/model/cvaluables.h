/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CVALUABLES_H
#define CVALUABLES_H

#include "cbases.h"
#include "ctagged.h"

namespace hacc
{
namespace model
{

//! Синглон основных средств
/*!
 Управляет основными средствами. Непосредственно управляет таблицами
     - valuables
 @see CValuable
*/
class CValuables :
        public base::CBases,
        public hacc::model::CTagged
{
    Q_OBJECT
public:
    CValuables();
    ~CValuables();
    void remove(const hacc::TDBID & id);
    void remove(const hacc::TIDList & idList);
    void edit(const hacc::TDBID & id);
    void tagsEdit(const hacc::TDBID & id);
    bool checkSpecialPurposeTag(const hacc::TDBID &tagID);
    QString purposeTagsIDString();
    bool    hasPurposeTags();
    hacc::TDBID addTransactionValuable(const hacc::TDBID & transactionID, const hacc::TDBID &ownerContractor);
    void transactionRemoved(const hacc::TDBID & transactionID);
    void thingUpdated(const hacc::TDBID & thingID);
    void thingRemoved(const hacc::TDBID & thingID);
    void changeValuableOwner(const hacc::TDBID & id, const hacc::TDBID & contractorID);  //!< Смена владельца ценности
    hacc::TIDList listVithoutMoving(const QString &where, const QVariantList &parameters); //!< Список идентификаторов ценностей без перемещений

public slots:
    void add();

private:
    QAction * generateAction(base::EActionsTypes atype, QObject *reciever, const char * method);
    hacc::TDBID maxDBID();
    QString idToSerial(const hacc::TDBID & valuableID); //!< Генерирует виртуальный серийный номер из идентификатора записи
    void execRemove(const QString &where, const QVariantList &parameters = QVariantList());
};

}
}
#endif // CVALUABLES_H
