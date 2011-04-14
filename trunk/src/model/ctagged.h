#ifndef CTAGGED_H
#define CTAGGED_H

#include <QString>
#include <QStringList>
#include <QMap>
#include "hacc_types.h"

namespace hacc
{
namespace model
{
/** Теги записи
  @param hacc::TDBID Идентификатор тега
  @param QString Имя тега
  */
typedef QMap<hacc::TDBID, QString> TItemTags;
/** Теги записей таблицы
  @param hacc::TDBID Идентификатор строки таблицы
  @param TItemTags Теги этой строки
  */
typedef QMap<hacc::TDBID, TItemTags> TTableTags;
typedef QMapIterator<hacc::TDBID, QString> TItemTagsIterator; //!< Итератор тегов записи

//! Метки для сущностей
/*!
  Класс расширяет функционал отдельных синглтонов-сущностей возможностью работы с метками к записям соответствующих таблиц
  Таблица, которой управляет класс - зависит от синглтона, к которому он прикручен и указывается в конструкторе
  @see db::CDatabase::createDatabase()
*/
class CTagged
{
public:
    CTagged(const QString &table, const QString &column);
    ~CTagged();
    //! @name Управление тегами
    //! @{
    TItemTags & tags(const hacc::TDBID &columnID);                                                   //!< Список тегов записи
    void attachTag  (const hacc::TDBID   &tagID  , const hacc::TDBID &columnID, const bool &attach); //!< Прикрепление тега к записи
    void attachTag  (const hacc::TDBID   &tagID  , const hacc::TDBID &columnID);                     //!< Прикрепление тега к записи
    void detachTag  (const hacc::TDBID   &tagID  , const hacc::TDBID &columnID);                     //!< Открепление тега от записи
    bool retachTag  (const hacc::TDBID   &tagID  , const hacc::TDBID &columnID);                     //!< Переключение тега (если откреплен - прикрепить и наоборот)
    void setTags    (const hacc::TIDList &newTags, const hacc::TDBID &columnID);                     //!< Замена тегов записи новым списком
    bool tagAttached(const hacc::TDBID   &tagID  , const hacc::TDBID &columnID);                     //!< Проверка - прикреплен ли тег?
    void detachTags (const hacc::TDBID &columnID);                                                   //!< Удаление всех тегов записи
    //! @}
    const QString &tagTable  () const;                                 //!< Имя управляемой таблицы
    const QString &itemColumn() const;                                 //!< Имя столбца идентификатора записи таблицы
    const QString &selectSelfTagsQuery() const;                        //!< Текст SQL запрса для выборки только "своих" тегов
    virtual bool checkSpetialPurposeTag(const hacc::TDBID &tagID) = 0; //!< Проверка тега на причастность к "специальным" тегам
    QString whereTagsInPurposeTags();                                  //!< Возвращает where часть sql запроса для выборки специальных тегов
    virtual QString purposeTagsIDString() = 0;                         //!< Должна вернуть ID специальных тегов, перечисленных через запятую. @see whereTagsInPurposeTags()
    virtual bool    hasPurposeTags() = 0;                              //!< Есть ли для сущности специальныеметки

private:
    QString m_table;               //!< Имя управляемой таблицы
    QString m_column;              //!< Имя столбца идентификатора записи таблицы
    QString m_selectSelfTagsQuery; //!< Текст SQL запрса для выборки только "своих" тегов
    QString m_purposeTagsIDString; //!< Текст SQL запрса для выборки специальных тегов
    TTableTags m_tagsMap;          //!< Кеш тегов, для того чтобы слишком часто не нырять в БД.

protected:
    virtual void tagAttachEvent(const hacc::TDBID &tagID, const hacc::TDBID &columnID); //!< Метка прикреплена
    virtual void tagDetachEvent(const hacc::TDBID &tagID, const hacc::TDBID &columnID); //!< Метка откреплена
};

}
}

#endif // CTAGGED_H
