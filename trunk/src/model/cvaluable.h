/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CVALUABLE_H
#define CVALUABLE_H

#include "cbase.h"

namespace hacc
{
namespace model
{

//! Сущность. Основное средство, ценность
class CValuable : public base::CBase
{
    Q_OBJECT
    HACC_MODEL_BASE_EVENTS_DECLARE(valuable);
public:
    CValuable();
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
#endif // CVALUABLE_H
