/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CTHINGS_H
#define CTHINGS_H

#include "cbases.h"
#include "ctagged.h"

namespace hacc
{
namespace model
{

//! Синглон вещей
/*!
 Вещь - это общее понятие для объектов, услуг и расходных материалов. Это то, что можно купить за деньги.
 Непосредственно управляет таблицами
     - things
 @see CThing
*/
class CThings :
        public base::CBases,
        public hacc::model::CTagged
{
    Q_OBJECT
public:
    CThings();
    ~CThings();
    //! @ingroup singletoneQActionsGenerators
    //! @{
    QAction * addAction();
    //! @}
    void remove(const hacc::TDBID & id);
    void edit(const hacc::TDBID & id);
    void tagsEdit(const hacc::TDBID & id);
    void removeEnumeratedType(const hacc::TDBID & enumeratedThingTypeID);
    void removeManufacturer(const hacc::TDBID & manufacturerID);
    QString thingName(const hacc::TDBID & id);
    bool checkSpecialPurposeTag(const hacc::TDBID &tagID);
    QString purposeTagsIDString();
    bool    hasPurposeTags();

public slots:
    void add();

private:
    QAction * generateAction(base::EActionsTypes atype, QObject *reciever, const char * method);
    hacc::TDBID maxDBID();
};

}
}
#endif // CTHINGS_H
