/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CMOVEMENTS_H
#define CMOVEMENTS_H

#include "cbases.h"
#include "ctagged.h"

namespace hacc
{
namespace model
{

//! Синглон перемещений средств
/*!
 Управляет перемещениями основных средств. Непосредственно управляет таблицами
     - movements
 @see CMovement
*/
class CMovements :
        public base::CBases,
        public hacc::model::CTagged
{
    Q_OBJECT
public:
    CMovements();
    ~CMovements();
    void remove(const hacc::TDBID & id);
    void execRemove(const QString &where, const QVariantList &parameters = QVariantList());
    void edit(const hacc::TDBID & id);
    void tagsEdit(const hacc::TDBID & id);
    bool checkSpetialPurposeTag(const hacc::TDBID &tagID);
    QString purposeTagsIDString();
    bool    hasPurposeTags();
    void thingRemoved(const hacc::TDBID & thingID);
    //! @ingroup singletoneQActionsGenerators
    //! @{
    QAction *addTransactionGiveGiftAction();
    QAction *addTransactionAcceptGiftAction();
    //! @}
    hacc::TDBID moveThing(const hacc::TDBID &sourceContractor, const hacc::TDBID &destinationContractor,
                   const hacc::TDBID &valuable, const QDateTime &datetime,
                   const int &movementType);
    void writeOff(const hacc::TDBID &owner, const hacc::TDBID &valuable, const QDateTime &datetime);


public slots:
    void add();
    void addTransactionGiveGift();
    void addTransactionAcceptGift();

private:
    QAction * generateAction(base::EActionsTypes atype, QObject *reciever, const char * method);
    hacc::TDBID maxDBID();
    void execMoveGift(const int &movementType);
};

}
}
#endif // CMOVEMENTS_H
