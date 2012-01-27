/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CCURRENCY_H
#define CCURRENCY_H

#include "cbase.h"

namespace hacc
{
namespace model
{

//! Сущность. Валюта
class CCurrency : public base::CBase
{
    Q_OBJECT
    HACC_MODEL_BASE_EVENTS_DECLARE(currency)
public:
    CCurrency();
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
};

}
}
#endif // CCURRENCY_H
