/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CMANUFACTURER_H
#define CMANUFACTURER_H

#include "cbase.h"

namespace hacc
{
namespace model
{

//! Сущность. Производитель
class CManufacturer : public base::CBase
{
    Q_OBJECT
    HACC_MODEL_BASE_EVENTS_DECLARE(manufacturer)
public:
    CManufacturer();
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
#endif // CMANUFACTURER_H
