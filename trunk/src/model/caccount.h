/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CACCOUNT_H
#define CACCOUNT_H

#include "cbase.h"

namespace hacc
{
namespace model
{

//! Сущность. Счет
class CAccount : public base::CBase
{
    Q_OBJECT
    HACC_MODEL_BASE_EVENTS_DECLARE(account);
public:
    CAccount();
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
#endif // CACCOUNT_H
