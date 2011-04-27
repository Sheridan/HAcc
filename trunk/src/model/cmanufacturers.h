/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CMANUFACTURERS_H
#define CMANUFACTURERS_H

#include "cbases.h"
#include "ctagged.h"

namespace hacc
{
namespace model
{
//! Синглон пердприятий
/*!
 Управляет пердприятиями. Непосредственно управляет таблицами
     - manufacturers
 @see CManufacturer
*/
class CManufacturers : public base::CBases, public hacc::model::CTagged
{
    Q_OBJECT
public:
    CManufacturers();
    ~CManufacturers();
    void remove(const hacc::TDBID & id);
    void edit(const hacc::TDBID & id);
    void tagsEdit(const hacc::TDBID & id);
    //! @ingroup singletoneQActionsGenerators
    //! @{
    QAction * addAction();
    //! @}
    QString manufacturerName(const hacc::TDBID & id);     //!< Имя производителя
    bool checkSpetialPurposeTag(const hacc::TDBID &tagID);
    QString purposeTagsIDString();
    bool    hasPurposeTags();

public slots:
    void add();

private:
    QAction * generateAction(base::EActionsTypes atype, QObject *reciever, const char * method);
    hacc::TDBID maxDBID();
};

}
}
#endif // CMANUFACTURERS_H
