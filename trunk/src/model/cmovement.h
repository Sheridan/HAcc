/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CMOVEMENT_H
#define CMOVEMENT_H

#include "cbase.h"

namespace hacc
{
namespace model
{

//! Сущность. Перемешение основного средства
class CMovement : public base::CBase
{
    Q_OBJECT
    HACC_MODEL_BASE_EVENTS_DECLARE(movement)
public:
    CMovement();
    //! @ingroup recordsQActionsGenerators
    //! @{
    QAction *editAction();
    QAction *removeAction();
    QAction *tagsEditAction();
    //! @}
    base::CBases  *worker();

public slots:
    void edit();
    void remove();
    void tagsEdit();
};

}
}
#endif // CMOVEMENT_H
