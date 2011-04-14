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
 Управляет контрагентвми. Непосредственно управляет таблицами
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
    void add();
    void remove(const hacc::TDBID & id);
    void edit(const hacc::TDBID & id);
    //! @ingroup singletoneQActionsGenerators
    //! @{
    QAction * addAction();
    //! @}


private:
    QAction * generateAction(base::EActionsTypes atype, QObject *reciever, const char * method);
    hacc::TDBID maxDBID();
};

}
}
#endif // CCURRENCYES_H
