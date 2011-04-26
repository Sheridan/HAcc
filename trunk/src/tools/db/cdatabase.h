#ifndef CDATABASE_H
#define CDATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariantList>
#include "hacc_types.h"

#define HACC_DATABASE_VERSION 1
#define HACC_TAG_TABLE_NAME(_table)    #_table "s_tags "
#define HACC_TAG_TABLE_ID_NAME(_table) #_table "_id "
#define HACC_QUERY_DATA_AVIALABLE(_q) (_q.next() && _q.size())

namespace tools
{
//! Работа с БД
namespace db
{
//! Класс работы с БД
/*! SQLite. Предоставляет базовый функционал: выборки, вычисление индентификаторов,
  создание БД
  В запросах фигурирует текст запроса и параметры, передаваемые через QVariantList.
  Важно стараться передавать параметры именно так, не встраивая их в тело запроса.
 */
class CDatabase : public QObject
{
    Q_OBJECT
public:
    CDatabase(const QString &sessionName = "default");
    virtual ~CDatabase();
    bool open(const QString &filename, bool create = false);                              //!< Открывает, создает БД
    void close();                                                                         //!< Закрывает БД. Ваш К.О.
    bool isOpen();                                                                        //!< БД открыта?
    const QString & dbFileName();                                                         //!< Возвращает имя файла БД
    QSqlQuery query(const QString &sql, const QVariantList &parameters = QVariantList()); //!< Делает select запрос к БД
    bool exec(const QString &sql, const QVariantList &parameters = QVariantList());       //!< Исполняет прочие запросы к БД
    QVariant queryCell   (const QString &sql, const QVariant & defaultValue = QVariant(),
                          const QVariantList &parameters = QVariantList());               //!< Запрос единственного значения из БД
    int tableRecordsCount(const QString &table);                                          //!< Возвращает количество записей в таблице.
    hacc::TDBID rowID    (const QString &table, const QString &where,
                          const QVariantList &parameters);                                //!< Возвращает идентификатор записи
    QString rowName(const QString &table, const hacc::TDBID &id);                         //!< Возвращает имя записи. Столбец name
    hacc::TDBID nextID(const QString &table);                                             //!< Возвращает следующий уникальный идентификатор таблицы
    hacc::TIDList listID(const QString &table, const QString &where = "",
                         const QVariantList &parameters = QVariantList());                //!< Возвращает список идентификаторов

private:
    QSqlDatabase m_db;                                                                    //!< Собственно, БД
    QString m_sessionName;                                                                //!< Имя сессии БД
    QString m_fileName;                                                                   //!< Имя файла БД
    QSqlQuery execQuery(const QString &sql,
                        const QVariantList &parameters = QVariantList(),
                        bool isExec = false);                                             //!< Исполняет запросы к БД
    QString lastErrorToLogDescription(const QSqlError& sqlError, const QString& sql,
                                      const QVariantList &parameters);                    //!< Преобразует ошибку в читабельный формат и показывает
    QString readableSql(QString sql);                                                     //!< перобразует sql запрос в читабельный формат
    QString parametresToString(const QVariantList &parameters);                           //!< Конвертирует параметры запроса в строку.
    void createDatabase();                                                                //!< Создание базы данных
    void fillDatabase();                                                                  //!< Заполнение БД начальными значениями

signals:
    void stateChange(bool);                                                               //!< Сигнал смены состояния БД
    void opened();                                                                        //!< Сигнал об открытии БД
    void closed();                                                                        //!< Сигнал о закрытии БД

};

}
}
#endif // CDATABASE_H
