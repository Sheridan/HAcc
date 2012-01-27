/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CTRANSACTION_H
#define CTRANSACTION_H

#include "cbase.h"

namespace hacc
{
namespace model
{

//! Сущность. Транзакция.
class CTransaction : public base::CBase
{
    Q_OBJECT
    HACC_MODEL_BASE_EVENTS_DECLARE(transaction)
public:
    CTransaction();
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
#endif // CTRANSACTION_H
