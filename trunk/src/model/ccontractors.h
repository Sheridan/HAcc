/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CCONTRACTORS_H
#define CCONTRACTORS_H
#include <QString>
#include "cbases.h"
#include "ctagged.h"

namespace hacc
{
namespace model
{
//! Фильтр контрагентов
/*! Используется для фильтрования контрагентов в элементах управления */
enum EContractorFilter
{
    ctAll   = 0, //!< Все контрагенты
    ctSelf  = 1, //!< Только собственные контрагенты
    ctOther = 2  //!< Только не собственные контрагенты
};
//! Синглон контрагентов
/*!
 Управляет контрагентвми. Непосредственно управляет таблицами
     - contractors
 @see CContractor
*/
class CContractors :
        public base::CBases,
        public hacc::model::CTagged
{
    Q_OBJECT
public:
    CContractors();
    ~CContractors();
    void remove(const hacc::TDBID & id);
    void edit(const hacc::TDBID & id);
    void tagsEdit(const hacc::TDBID & id);
    //! @ingroup singletoneQActionsGenerators
    //! @{
    QAction * addAction();
    QAction * addSelfAction();
    //! @}
    bool checkSpetialPurposeTag(const hacc::TDBID &tagID);
    QString purposeTagsIDString();
    bool    hasPurposeTags();

public slots:
    void add();
    void addSelf();

private:
    QAction * generateAction(base::EActionsTypes atype, QObject *reciever, const char * method);
    void add(bool isSelf);
    hacc::TDBID maxDBID();
};

}
}
#endif // CCONTRACTORS_H
