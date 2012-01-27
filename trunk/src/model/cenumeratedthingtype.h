/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CENUMERATEDTHINGTYPE_H
#define CENUMERATEDTHINGTYPE_H

#include "cbase.h"

namespace hacc
{
namespace model
{

//! Сущность. Перечисляемый тип
class CEnumeratedThingType : public base::CBase
{
    Q_OBJECT
    HACC_MODEL_BASE_EVENTS_DECLARE(enumeratedThingType)
public:
    CEnumeratedThingType();
    //! @ingroup recordsQActionsGenerators
    //! @{
    QAction *editAction();
    QAction *removeAction();
    //! @}
    base::CBases  *worker();

public slots:
    void edit();
    void remove();
};

}
}
#endif // CENUMERATEDTHINGTYPE_H
