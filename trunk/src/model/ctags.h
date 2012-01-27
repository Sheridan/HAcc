/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CTAGS_H
#define CTAGS_H

#include "cbases.h"
#include <QVariantList>
#include <QStringList>

namespace hacc
{
namespace model
{

//! Синглон тегов
/*!
 Управляет тегами. Непосредственно управляет таблицами
     - tags
 @see CTagged
 @see CTag
*/
class CTags : public base::CBases
{
    Q_OBJECT
public:
    CTags();
    ~CTags();
    void remove(const hacc::TDBID & id);
    void edit(const hacc::TDBID & id);
    //! @ingroup singletoneQActionsGenerators
    //! @{
    QAction * addAction();
    //! @}
    QString tagName(const hacc::TDBID & id);
    bool checkSpecialPurposeTag(const hacc::TDBID &tagID);

public slots:
    void add();

private:
    QStringList m_tagTables;
    QAction * generateAction(base::EActionsTypes atype, QObject *reciever, const char * method);
    void eachTagTableExecute(const QString &sql, const QVariantList &parametres = QVariantList());
    hacc::TDBID maxDBID();

};

}
}
#endif // CTAGS_H
