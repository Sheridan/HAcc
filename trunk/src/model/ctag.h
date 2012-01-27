/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CTAG_H
#define CTAG_H

#include "cbase.h"

namespace hacc
{
namespace model
{

//! Сущность. Метка
class CTag : public base::CBase
{
    Q_OBJECT
    HACC_MODEL_BASE_EVENTS_DECLARE(tag)
public:
    CTag();
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
#endif // CTAG_H
