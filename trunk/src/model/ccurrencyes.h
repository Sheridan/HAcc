/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CCURRENCYES_H
#define CCURRENCYES_H

#include <QString>
#include "cbases.h"
#include "ctagged.h"

namespace hacc
{
namespace model
{

//! Синглон валют
/*!
 Управляет валютами. Непосредственно управляет таблицами
     - currencyes
 @see CCurrency
*/
class CCurrencyes :
        public base::CBases
{
    Q_OBJECT
public:
    CCurrencyes();
    ~CCurrencyes();
    void remove(const hacc::TDBID & id);
    void edit(const hacc::TDBID & id);
    void execAddCurrency(const QString &name, const QString &reduction,
                         const bool &reductionBeforeNumber, const hacc::TDBID iconID);
    //! @ingroup singletoneQActionsGenerators
    //! @{
    QAction * addAction();
    //! @}

public slots:
    void add();

private:
    QAction * generateAction(base::EActionsTypes atype, QObject *reciever, const char * method);
    hacc::TDBID maxDBID();
};

}
}
#endif // CCURRENCYES_H
