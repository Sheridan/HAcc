/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CTHING_H
#define CTHING_H

#include "cbase.h"

namespace hacc
{
namespace model
{

//! Сущность. Вещь. (Объект, услуга...)
class CThing : public base::CBase
{
    Q_OBJECT
    HACC_MODEL_BASE_EVENTS_DECLARE(thing)
public:
    CThing();
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
#endif // CTHING_H
