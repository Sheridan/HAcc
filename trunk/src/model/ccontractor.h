/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CCONTRACTOR_H
#define CCONTRACTOR_H

#include "cbase.h"
namespace hacc
{
namespace model
{
//! Сущность. Контрагент
class CContractor : public base::CBase
{
    Q_OBJECT
    HACC_MODEL_BASE_EVENTS_DECLARE(contractor)
public:
    CContractor();
    //! @ingroup recordsQActionsGenerators
    //! @{
    QAction *addAccountAction();
    QAction *editAction();
    QAction *removeAction();
    QAction *tagsEditAction();
    //! @}
    base::CBases  *worker();

public slots:
    void addAccount();
    void edit();
    void remove();
    void tagsEdit();

};

}
}
#endif // CCONTRACTOR_H
