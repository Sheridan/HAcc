/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CENUMERATEDTHINGTYPES_H
#define CENUMERATEDTHINGTYPES_H

#include "cbases.h"

#define HACC_THING_SPECIAL_ENUMERATE_NA    1
#define HACC_THING_SPECIAL_ENUMERATE_ITEMS 2
#define HACC_THING_SPECIAL_ENUMERATE_TIMES 3
#define HACC_THING_SPECIAL_ENUMERATE_MAX HACC_THING_SPECIAL_ENUMERATE_TIMES

namespace hacc
{
namespace model
{
//! Синглтон перечисляемых типов вещей
/*!
 Например, штуки, литры.
 Управляет перечисляемыми типами. Непосредственно управляет таблицами
     - thing_enumerated_types
 @see CEnumeratedThingType
*/
class CEnumeratedThingTypes : public base::CBases
{
    Q_OBJECT
public:
    CEnumeratedThingTypes();
    ~CEnumeratedThingTypes();
    void remove(const hacc::TDBID & id);
    void edit(const hacc::TDBID & id);
    //! @ingroup singletoneQActionsGenerators
    //! @{
    QAction * addAction();
    //! @}
    QString thingEnumerateTypeName(const hacc::TDBID &id);
    bool checkSpecialEnumeratedType(const hacc::TDBID &typeID);
    bool checkDivisibleEnumeratedType(const hacc::TDBID &typeID);

public slots:
    void add();

private:
    QAction * generateAction(base::EActionsTypes atype, QObject *reciever, const char * method);
    hacc::TDBID maxDBID();
};

}
}
#endif // CENUMERATEDTHINGTYPES_H
