#include <QFile>
#include "cdatabase.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlDriver>
#include "st.h"
#include "hacc_db_defines.h"

namespace db
{

CDatabase::CDatabase(const QString &sessionName)
{
    m_sessionName = sessionName + "_hacc_database";
    QString dbfile = HACC_OPTIONS->sectionValue("db", "file", "").toString();
    if(QFile::exists(dbfile))
    {
        open(dbfile);
    }
}

                CDatabase::~CDatabase() { close();}
const QString & CDatabase::dbFileName() { return m_fileName; }
           bool CDatabase::isOpen    () { return m_db.isOpen(); }

/**
  Открывает БД, создавая если надо
  @param filename Путь и имя файла БД
  @param create   Создать новую?
  @return Получилось?
  */
bool CDatabase::open(const QString &filename, bool create)
{
    close();
    m_fileName = filename;
    m_db = QSqlDatabase::addDatabase("QSQLITE", m_sessionName);
    m_db.setDatabaseName(m_fileName);
    if (!m_db.open() || m_db.lastError().isValid())
    {
        QMessageBox::critical(HACC_WINDOW, QObject::tr("Open error"),
                              lastErrorToLogDescription(m_db.lastError(), QString("Connect to %1").arg(m_fileName), QVariantList()));
        return false;
    }
    if(create) { createDatabase(); }
    HACC_OPTIONS->setSectionValue("db", "file", m_fileName);
    HACC_DEBUG("Opened database:" << m_fileName);
    emit stateChange(true);
    emit opened();
    return true;
}
/**
  Проверяет - открыта ли БД, и если открыта - закрывает ее, выбрасывая необходимые сигналы
  */
void CDatabase::close()
{
    if(isOpen())
    {
        emit stateChange(false);
        emit closed();
        m_db.close();
        QSqlDatabase::removeDatabase(m_sessionName);
    }
}

/**
  @param parameters Параметры запроса
  @return Строку, где в {} заключен каждый параметр запроса
  */
QString CDatabase::parametresToString(const QVariantList &parameters)
{
        QString valuesList;
        foreach(QVariant value, parameters)
        {
            switch(value.type())
            {
            case QVariant::ByteArray:
                valuesList += QString("{ByateArray: %1}").arg(value.toByteArray().capacity());
                break;
            default:
                valuesList += QString("{%1}").arg(value.toString());
            }
        }
        return valuesList;
}

/**
  @param sql Строка запроса
  @return Строку с более читабельным запросом
  */
QString CDatabase::readableSql(QString sql)
{
        return sql
              .replace("from" , "\nfrom" , Qt::CaseInsensitive)
              .replace("where", "\nwhere", Qt::CaseInsensitive)
              .replace("order", "\norder", Qt::CaseInsensitive)
              .replace("group", "\ngroup", Qt::CaseInsensitive)
              .replace("left" , "\nleft" , Qt::CaseInsensitive)
              .replace("right", "\nright", Qt::CaseInsensitive)
              .replace("inner", "\ninner", Qt::CaseInsensitive)
              .replace("outer", "\nouter", Qt::CaseInsensitive)
              ;
}

/**
  @param sqlError Описание ошибки
  @param sql Строка запроса
  @param parameters Параметры запроса
  @return Строку с тектом ошибки, запросом и параметрами запроса, приведенную к читабельному виду
  @see readableSql()
  @see parametresToString()
  */
QString CDatabase::lastErrorToLogDescription(const QSqlError& sqlError, const QString& sql, const QVariantList &parameters)
{
        QStringList result;
        result.append(QObject::tr("#: %1").arg(sqlError.number()));
        switch(sqlError.type())
        {
                case QSqlError::NoError:                result.append(QObject::tr("No error occurred."));          break;
                case QSqlError::ConnectionError:        result.append(QObject::tr("Connection error."));           break;
                case QSqlError::StatementError:         result.append(QObject::tr("SQL statement syntax error.")); break;
                case QSqlError::TransactionError:       result.append(QObject::tr("Transaction failed error."));   break;
                case QSqlError::UnknownError:           result.append(QObject::tr("Unknown error."));              break;
        }
        result.append(QObject::tr("Database text:"));
        result.append(sqlError.databaseText());
        result.append(QObject::tr("Database driver text:"));
        result.append(sqlError.driverText());
        if(!sql.isEmpty())
        {
                result.append("SQL: ");
                result.append(readableSql(sql));
        }
        if(!parameters.isEmpty())
        {
                result.append(QObject::tr("Parametres:"));
                result.append(parametresToString(parameters));
        }
        return result.join("\n");
}
/**
  Базовый метод исполнения запроса. Обеспечивает транзакции, подготавливает и исполняет запрос, возвращает результат.
  @param sql Строка запроса
  @param parameters Параметры запроса
  @param isExec Это select или еще что?
  @see lastErrorToLogDescription()
  @see query()
  @see exec()
  @return QSqlQuery с результатом запроса
  */
QSqlQuery CDatabase::execQuery(const QString &sql, const QVariantList &parameters, bool isExec)
{
    QSqlQuery q(m_db);
    if(isOpen())
    {
        q.prepare(sql);
        int _pos = 0;
        foreach(QVariant value, parameters)
        {
            q.bindValue(_pos, value);
            _pos++;
        }
        bool transactionActive = false;
        if(isExec)
        {
                transactionActive = m_db.driver()->beginTransaction();
        }
        if(!q.exec() || q.lastError().isValid())
        {
            QMessageBox::critical(HACC_WINDOW, QObject::tr("Sql error"), lastErrorToLogDescription(q.lastError(), sql, parameters));
            if(isExec && transactionActive)
            {
                m_db.driver()->rollbackTransaction();
            }
        }
        else
        {
            if(isExec && transactionActive)
            {
                m_db.driver()->commitTransaction();
            }
        }
    }
    return q;
}

/**
  @param sql Строка запроса
  @param parameters Параметры запроса
  @return QSqlQuery с результатом запроса
  */
QSqlQuery CDatabase::query(const QString &sql, const QVariantList &parameters)
{
    HACC_DEBUG_SQL("<--db: " << sql << parametresToString(parameters));
    return execQuery(sql, parameters, false);
}

/**
  @param sql Строка запроса
  @param parameters Параметры запроса
  @return Выполнился запрос или нет?
  */
bool CDatabase::exec(const QString &sql, const QVariantList &parameters)
{
    HACC_DEBUG_SQL("-->db: " << sql << parametresToString(parameters));
    return !execQuery(sql, parameters, true).lastError().isValid();
}

/**
  @param sql Строка запроса
  @param defaultValue Значение по умолчанию
  @param parameters Параметры запроса
  @return QVariant со значением или значение по умолчанию
  */
QVariant CDatabase::queryCell(const QString &sql, const QVariant & defaultValue, const QVariantList &parameters)
{
    QSqlQuery q = query(sql, parameters);
    if(q.next()) { return q.value(0); }
    return defaultValue;
}

/**
  Для получения имени сущности из таблиц. Справедоиво для таблиц, в которых есть столбцы name и id
  @param table Таблица.
  @param id Идентификатор записи
  @return Строку с именем
  */
QString CDatabase::rowName(const QString &table, const hacc::TDBID &id)
{
    return queryCell(QString("select name from %1 where id=?").arg(table),
                     QVariant(""),
                     QVariantList() << id)
            .toString();
}

/**
  @param table Таблица.
  @return Количество записей в таблице
  */
int CDatabase::tableRecordsCount(const QString &table)
{
    return queryCell(QString("select count(*) from %1").arg(table), QVariant(0)).toInt();
}

/**
  Критерий отбора записей должен быть таким, чтобы результатом была единственная запись.
  @param table Таблица
  @param where Критерий отбора записей
  @param parameters Параметры запроса
  @return Идентификатор записи
  */
hacc::TDBID CDatabase::rowID(const QString &table, const QString &where, const QVariantList &parameters)
{
    return queryCell(QString("select id from %1 where %2").arg(table).arg(where), QVariant(0), parameters).toUInt();
}

/**
  @param table Таблица
  @return Следующий уникальный идентификатор для заданной таблицы
  */
hacc::TDBID CDatabase::nextID(const QString &table)
{
    return (queryCell(QString("select max(id) from %1").arg(table), QVariant(0)).toUInt()) + 1;
}

/**
  @param table Таблица
  @param where Критерий отбора записей
  @param parameters Параметры запроса
  @return Список идентификаторов записей
  */
hacc::TIDList CDatabase::listID(const QString &table, const QString &where, const QVariantList &parameters)
{
    hacc::TIDList list;
    QSqlQuery q = query(QString("select id from %1 %2")
                        .arg(table)
                        .arg(where.isEmpty() ? "" : " where " + where),
                        parameters);
    while(q.next())
    {
        list.append(HACC_DB_2_DBID(q, 0));
    }
    return list;
}

/**
  Создает базу данных, заполняет начальными данными некоторые таблицы, генерирует базовые записи
  В режиме отладки также генерирует несколько сущностей для более удобного тестирования
  \todo Обеспечить версионность БД и возможность конвертирования из более ранней версии в более позднююю
  */
void CDatabase::createDatabase()
{
//######################################################################################################
//## Счета контрагентов
//######################################################################################################
    HACC_DB_CREATE_TABLE_BEGIN(accounts)
            HACC_DB_ID_FIELD                                           HACC_DB_FIELD_DELIMITER
            HACC_DB_NAME_FIELD                                         HACC_DB_FIELD_DELIMITER
            HACC_DB_ICON_FIELD                                         HACC_DB_FIELD_DELIMITER
            HACC_DB_CURRENCY_FIELD                                     HACC_DB_FIELD_DELIMITER
            HACC_DB_ID(contractor_id)
    HACC_DB_CREATE_TABLE_END;
    HACC_DB_CREATE_INDEX(accounts, contractor_id);

//######################################################################################################
//## Контрагенты
//######################################################################################################
    HACC_DB_CREATE_TABLE_BEGIN(contractors)
            HACC_DB_ID_FIELD                                            HACC_DB_FIELD_DELIMITER
            HACC_DB_UNIQUE_NAME_FIELD                                   HACC_DB_FIELD_DELIMITER
            HACC_DB_ICON_FIELD                                          HACC_DB_FIELD_DELIMITER
            HACC_DB_BOOL(own_account)
    HACC_DB_CREATE_TABLE_END;
    HACC_DB_CREATE_INDEX(contractors, own_account);
    HACC_DB_CREATE_UNIQNAME_ID_INDEX(contractors);

//######################################################################################################
//## Производители
//######################################################################################################
    HACC_DB_CREATE_TABLE_BEGIN(manufacturers)
            HACC_DB_ID_FIELD                                            HACC_DB_FIELD_DELIMITER
            HACC_DB_UNIQUE_NAME_FIELD                                   HACC_DB_FIELD_DELIMITER
            HACC_DB_ICON_FIELD                                          HACC_DB_FIELD_DELIMITER
            HACC_DB_FULL_DESCRIPTION
    HACC_DB_CREATE_TABLE_END;
    HACC_DB_CREATE_UNIQNAME_ID_INDEX(manufacturers);

//######################################################################################################
//## Вещи (Объекты, услуги, расходники...)
//######################################################################################################
    HACC_DB_CREATE_TABLE_BEGIN(things)
            HACC_DB_ID_FIELD                                            HACC_DB_FIELD_DELIMITER
            HACC_DB_NAME_FIELD                                          HACC_DB_FIELD_DELIMITER
            HACC_DB_ICON_FIELD                                          HACC_DB_FIELD_DELIMITER
            HACC_DB_ID(manufacturer_id)                                 HACC_DB_FIELD_DELIMITER
            HACC_DB_ID(enumerated_type_id)                              HACC_DB_FIELD_DELIMITER
            HACC_DB_INTEGER(expiration_period) HACC_DB_FIELD_DEFAULT(0) HACC_DB_FIELD_DELIMITER
            HACC_DB_INTEGER(guarantee_period)  HACC_DB_FIELD_DEFAULT(0) HACC_DB_FIELD_DELIMITER
            HACC_DB_FULL_DESCRIPTION
    HACC_DB_CREATE_TABLE_END;
    HACC_DB_CREATE_INDEX(things, manufacturer_id);
    HACC_DB_CREATE_INDEX(things, enumerated_type_id);

//######################################################################################################
//## перечисляемые типы вещей
//######################################################################################################
    HACC_DB_CREATE_TABLE_BEGIN(thing_enumerated_types)
            HACC_DB_ID_FIELD                                            HACC_DB_FIELD_DELIMITER
            HACC_DB_UNIQUE_NAME_FIELD                                   HACC_DB_FIELD_DELIMITER
            HACC_DB_INTEGER(precision) HACC_DB_FIELD_DEFAULT(2)
    HACC_DB_CREATE_TABLE_END;
    HACC_DB_CREATE_UNIQNAME_ID_INDEX(thing_enumerated_types);

//######################################################################################################
//## Ценности, основные средства
//######################################################################################################
    HACC_DB_CREATE_TABLE_BEGIN(valuables)
            HACC_DB_ID_FIELD                                            HACC_DB_FIELD_DELIMITER
            HACC_DB_ID(transaction_id)                                  HACC_DB_FIELD_DELIMITER // транзакция, которой купили вещь
            HACC_DB_ID(owner_id)     HACC_DB_FIELD_DEFAULT(0)           HACC_DB_FIELD_DELIMITER // contractors.id - Владелец, первоначально тот, кто купил
            HACC_DB_ID(recipient_id) HACC_DB_FIELD_DEFAULT(0)           HACC_DB_FIELD_DELIMITER // contractors.id - тот у кого эта вещь сейчас, отданая "на время"
            HACC_DB_TEXT(serial_number)                                 HACC_DB_FIELD_DELIMITER // серийный номер
            HACC_DB_FULL_DESCRIPTION
    HACC_DB_CREATE_TABLE_END;
    HACC_DB_CREATE_INDEX(valuables, transaction_id);
    HACC_DB_CREATE_INDEX(valuables, owner_id);
    HACC_DB_CREATE_INDEX(valuables, recipient_id);

//######################################################################################################
//## Теги
//######################################################################################################
    HACC_DB_CREATE_TABLE_BEGIN(tags)
            HACC_DB_ID_FIELD                                            HACC_DB_FIELD_DELIMITER
            HACC_DB_UNIQUE_NAME_FIELD
    HACC_DB_CREATE_TABLE_END;
    HACC_DB_CREATE_UNIQNAME_ID_INDEX(tags);

//######################################################################################################
//## Иконки для сущностей
//######################################################################################################
    HACC_DB_CREATE_TABLE_BEGIN(icons)
            HACC_DB_ID_FIELD                                            HACC_DB_FIELD_DELIMITER
            HACC_DB_BLOB(icon) HACC_DB_FIELD_NOT_NULL
    HACC_DB_CREATE_TABLE_END;

//######################################################################################################
//## Пулы транзакций
//######################################################################################################
    HACC_DB_CREATE_TABLE_BEGIN(transactions_pool)
            HACC_DB_ID_FIELD                                            HACC_DB_FIELD_DELIMITER
            HACC_DB_DATETIME(date_time) HACC_DB_FIELD_NOT_NULL          HACC_DB_FIELD_DELIMITER
            HACC_DB_ID(source_account_id)                               HACC_DB_FIELD_DELIMITER
            HACC_DB_ID(destination_account_id)
    HACC_DB_CREATE_TABLE_END;
    HACC_DB_CREATE_INDEX(transactions_pool, source_account_id);
    HACC_DB_CREATE_INDEX(transactions_pool, destination_account_id);

//######################################################################################################
//## Транзакции
//######################################################################################################
//############ Основные записи транзакции #######################
    HACC_DB_CREATE_TABLE_BEGIN(transactions)
            HACC_DB_ID_FIELD                                            HACC_DB_FIELD_DELIMITER // transactions_things.id или tratransactions_commisions.id
            HACC_DB_ID(pool_id)                                         HACC_DB_FIELD_DELIMITER
            HACC_DB_MONEY(money)
    HACC_DB_CREATE_TABLE_END;
    HACC_DB_CREATE_INDEX(transactions, pool_id);
    HACC_DB_CREATE_INDEX_2(transactions, id, pool_id);

//############ Входящие вещевые записи транзакции #######################
    HACC_DB_CREATE_TABLE_BEGIN(transactions_things)
            HACC_DB_ID_FIELD                                            HACC_DB_FIELD_DELIMITER
            HACC_DB_ID(thing_id)                                        HACC_DB_FIELD_DELIMITER // вещь, купленая или принятая в дар транзакцией
            HACC_DB_REAL(amount) HACC_DB_FIELD_DEFAULT(0)
    HACC_DB_CREATE_TABLE_END;
    HACC_DB_CREATE_INDEX(transactions_things, thing_id);
    HACC_DB_CREATE_INDEX_2(transactions_things, id, thing_id);

//############ Исходящие вещевые записи транзакции #######################
    HACC_DB_CREATE_TABLE_BEGIN(transactions_valuables)
            HACC_DB_ID_FIELD                                            HACC_DB_FIELD_DELIMITER
            HACC_DB_ID(valuable_id)                                                             // Ценность, проданная или подаренная
    HACC_DB_CREATE_TABLE_END;
    HACC_DB_CREATE_INDEX(transactions_valuables, id);
    HACC_DB_CREATE_INDEX(transactions_valuables, valuable_id);
    HACC_DB_CREATE_INDEX_2(transactions_valuables, id, valuable_id);

//############ Коммиссия к транзакции #######################
    HACC_DB_CREATE_TABLE_BEGIN(transactions_commisions)
            HACC_DB_ID_FIELD                                            HACC_DB_FIELD_DELIMITER
            HACC_DB_ID(base_pool_id)                                    HACC_DB_FIELD_DELIMITER // pool id
            HACC_DB_ID(commission_to_id)                                HACC_DB_FIELD_DELIMITER // account id
            HACC_DB_BOOL(commission_value_is_percent)                   HACC_DB_FIELD_DELIMITER
            HACC_DB_BOOL(commission_already_in_money)                   HACC_DB_FIELD_DELIMITER
            HACC_DB_MONEY(commission_value)
    HACC_DB_CREATE_TABLE_END;
    HACC_DB_CREATE_INDEX(transactions_commisions, base_pool_id);
    HACC_DB_CREATE_INDEX(transactions_commisions, commission_to_id);
    HACC_DB_CREATE_INDEX_2(transactions_commisions, id, base_pool_id);
    HACC_DB_CREATE_INDEX_2(transactions_commisions, id, commission_to_id);

//######################################################################################################
//## Перемещения вещей
//######################################################################################################
    HACC_DB_CREATE_TABLE_BEGIN(movements)
            HACC_DB_ID_FIELD                                            HACC_DB_FIELD_DELIMITER
            HACC_DB_DATETIME(date_time) HACC_DB_FIELD_NOT_NULL          HACC_DB_FIELD_DELIMITER
            HACC_DB_ID(valuable_id)                                     HACC_DB_FIELD_DELIMITER
            HACC_DB_ID(source_contractor_id)                            HACC_DB_FIELD_DELIMITER
            HACC_DB_ID(destination_contractor_id)
    HACC_DB_CREATE_TABLE_END;
    HACC_DB_CREATE_INDEX(movements, valuable_id);
    HACC_DB_CREATE_INDEX(movements, source_contractor_id);
    HACC_DB_CREATE_INDEX(movements, destination_contractor_id);
    HACC_DB_CREATE_INDEX_2(movements, id, valuable_id);
    HACC_DB_CREATE_INDEX_2(movements, id, source_contractor_id);
    HACC_DB_CREATE_INDEX_2(movements, id, destination_contractor_id);

//######################################################################################################
//## Валюты
//######################################################################################################
    HACC_DB_CREATE_TABLE_BEGIN(currencyes)
            HACC_DB_ID_FIELD                                            HACC_DB_FIELD_DELIMITER
            HACC_DB_UNIQUE_NAME_FIELD                                   HACC_DB_FIELD_DELIMITER
            HACC_DB_TEXT(reduction)                                     HACC_DB_FIELD_DELIMITER
            HACC_DB_BOOL(show_reduction_before_value)
    HACC_DB_CREATE_TABLE_END;
    HACC_DB_CREATE_UNIQNAME_ID_INDEX(currencyes);

    exec("create table db_options (name text not null primary key, value text not null);");

    HACC_DB_CREATE_TAGS_TABLE(thing);
    HACC_DB_CREATE_TAGS_TABLE(account);
    HACC_DB_CREATE_TAGS_TABLE(movement);
    HACC_DB_CREATE_TAGS_TABLE(valuable);
    HACC_DB_CREATE_TAGS_TABLE(contractor);
    HACC_DB_CREATE_TAGS_TABLE(transaction);
    HACC_DB_CREATE_TAGS_TABLE(manufacturer);
    HACC_DB_CREATE_TAGS_TABLE(transactions_pool);

    HACC_DB_ICONS->add(":/main/icons/item-empty.png" ); // id: 1
    HACC_DB_ICONS->add(":/items/account.png"         ); // id: 2
    HACC_DB_ICONS->add(":/items/contractor.png"      ); // id: 3
    HACC_DB_ICONS->add(":/items/icon.png"            ); // id: 4
    HACC_DB_ICONS->add(":/items/tag.png"             ); // id: 5
    HACC_DB_ICONS->add(":/items/transaction.png"     ); // id: 6
    HACC_DB_ICONS->add(":/items/thing.png"           ); // id: 7
    HACC_DB_ICONS->add(":/items/transaction-pool.png"); // id: 8
    HACC_DB_ICONS->add(":/items/contractor-self.png" ); // id: 9
    HACC_DB_ICONS->add(":/items/enumerated.png"      ); // id: 10
    HACC_DB_ICONS->add(":/items/manufacturer.png"    ); // id: 11
    HACC_DB_ICONS->add(":/items/valuable.png"        ); // id: 12
    HACC_DB_ICONS->add(":/items/money.png"           ); // id: 13
    HACC_DB_ICONS->add(":/items/gift.png"            ); // id: 14
    HACC_DB_ICONS->add(":/items/movement.png"        ); // id: 15
    HACC_DB_ICONS->add(":/items/currency.png"        ); // id: 16
    HACC_DB_ICONS->add(":/usefull/bag-1.png"         ); // id: 17
    HACC_DB_ICONS->add(":/usefull/card-0.png"        ); // id: 18
    HACC_DB_ICONS->add(":/usefull/card-1.png"        ); // id: 19
    HACC_DB_ICONS->add(":/usefull/card-2.png"        ); // id: 20
    HACC_DB_ICONS->add(":/usefull/card-3.png"        ); // id: 21
    HACC_DB_ICONS->add(":/usefull/coins-0.png"       ); // id: 22
    HACC_DB_ICONS->add(":/usefull/coins-1.png"       ); // id: 23
    HACC_DB_ICONS->add(":/usefull/coins-2.png"       ); // id: 24
    HACC_DB_ICONS->add(":/usefull/coins-3.png"       ); // id: 25
    HACC_DB_ICONS->add(":/usefull/money-0.png"       ); // id: 26
    HACC_DB_ICONS->add(":/usefull/money-coin-0.png"  ); // id: 27
    HACC_DB_ICONS->add(":/usefull/contractor-0.png"  ); // id: 28
    HACC_DB_ICONS->add(":/usefull/contractor-1.png"  ); // id: 29
    HACC_DB_ICONS->add(":/usefull/contractor-2.png"  ); // id: 30

    // predeclared tags
    int i=0;
    foreach(QString tag, QStringList()
         /* 1*/ << tr("Service")     // Специальный тег для вещей
         /* 2*/ << tr("Object")      // Специальный тег для вещей
         /* 3*/ << tr("Expendable")  // Специальный тег для вещей
         /* 4*/ << tr("Write off")   // Специальный тег для основных средств и их перемещений
         /* 5*/ << tr("Buying")      // Специальный тег для транзакций и пула транзакций
         /* 6*/ << tr("Selling")     // Специальный тег для транзакций и пула транзакций
         /* 7*/ << tr("Transfer")    // Специальный тег для транзакций и пула транзакций
         /* 8*/ << tr("Commission")  // Специальный тег для транзакций и пула транзакций
         /*10*/ << tr("Gift from me")// Специальный тег для транзакций и пула транзакций
         /*11*/ << tr("Incoming")    // Специальный тег для транзакций и пула транзакций
         /*12*/ << tr("Tax")         // Специальный тег для транзакций и пула транзакций
         /*13*/ << tr("Outgoing")    // Специальный тег для транзакций и пула транзакций
         << tr("Home")     << tr("Work")      << tr("Car")    << tr("Food")
         << tr("Pets")     << tr("Family")    << tr("Travel") << tr("Phone")
         << tr("Music")    << tr("Video")     << tr("Book")   << tr("Computer")
         << tr("Software") << tr("Hardware")  << tr("Audio")  << tr("Gadget"))
    {
        i++;
        exec("insert into tags (id,name) values (?,?)", QVariantList() << i << tag);
    }

    exec("insert into thing_enumerated_types (id,name,precision) values ( 1,?,0)", QVariantList() << tr("n/a"));          // Специальный тип перечисления
    exec("insert into thing_enumerated_types (id,name,precision) values ( 2,?,0)", QVariantList() << tr("item(s)"));      // Специальный тип перечисления
    exec("insert into thing_enumerated_types (id,name,precision) values ( 3,?,0)", QVariantList() << tr("times"));        // Специальный тип перечисления
    exec("insert into thing_enumerated_types (id,name,precision) values ( 4,?,3)", QVariantList() << tr("litre(s)"));
    exec("insert into thing_enumerated_types (id,name,precision) values ( 5,?,3)", QVariantList() << tr("kilogram(s)"));
    exec("insert into thing_enumerated_types (id,name,precision) values ( 6,?,3)", QVariantList() << tr("m3"));
    exec("insert into thing_enumerated_types (id,name,precision) values ( 7,?,5)", QVariantList() << tr("kWh"));
    exec("insert into thing_enumerated_types (id,name,precision) values ( 8,?,3)", QVariantList() << tr("kilometer(es)"));
    exec("insert into thing_enumerated_types (id,name,precision) values ( 9,?,2)", QVariantList() << tr("metre(s)"));
    exec("insert into thing_enumerated_types (id,name,precision) values (19,?,0)", QVariantList() << tr("byte(s)"));
    exec("insert into thing_enumerated_types (id,name,precision) values (11,?,0)", QVariantList() << tr("count"));

    exec("insert into currencyes (id,name,reduction,show_reduction_before_value) values (1,?,?,?)", QVariantList() << tr("American dollar") << "$"  << true );
    exec("insert into currencyes (id,name,reduction,show_reduction_before_value) values (2,?,?,?)", QVariantList() << tr("Euro")            << "€"  << false);
    exec("insert into currencyes (id,name,reduction,show_reduction_before_value) values (3,?,?,?)", QVariantList() << tr("Russian ruble")   << "р." << false);

    int contractorID, accountID, manufacturerID, thingID; contractorID = accountID = manufacturerID = thingID = 0;
    HDB_APPEND_MANUFACTURER_FULL(tr("Unknown manufacturer"), tr("Some unknown manufacturer"), 11);
    HDB_APPEND_THING(tr("Unknown thing"), 7, 1, HACC_TAG_ID_OBJECT);

    // ничто
    HDB_APPEND_CONTRACTOR(tr("Nothing"), 1, false);
    HDB_APPEND_ACCOUNT(tr("Nowhere")   , 1);

    // собственный акк
    HDB_APPEND_CONTRACTOR(tr("Family"), 9, true);
    HDB_APPEND_ACCOUNT(tr("Cash money")        , 13);
    HDB_APPEND_ACCOUNT(tr("Husband Bank Card") , 19);
    HDB_APPEND_ACCOUNT(tr("Wife Bank Card")    , 21);

    exec("insert into db_options (name, value) values (?,?)", QVariantList() << "database version" << HACC_DATABASE_VERSION);

    #ifdef HACC_DEBUG_DB
        contractorID = accountID = manufacturerID = thingID = 100;

        HDB_APPEND_CONTRACTOR(tr("Wife"), 30, true);
        HDB_APPEND_ACCOUNT(tr("Money"), 13);
        HDB_APPEND_ACCOUNT(tr("Card") , 18);
        HDB_APPEND_ACCOUNT(tr("Nest") , 17);

        HDB_APPEND_CONTRACTOR(tr("Vistotch"), 29, false);
        HDB_APPEND_ACCOUNT(tr("Base account"), 24);

        HDB_APPEND_CONTRACTOR(tr("Sigma"), 3, false);
        HDB_APPEND_ACCOUNT(tr("Account"), 23);

        HDB_APPEND_CONTRACTOR(tr("Consultant+"), 29, false);
        HDB_APPEND_ACCOUNT(tr("Account"), 24);

        HDB_APPEND_CONTRACTOR(tr("OPT-Torg"), 30, false);
        HDB_APPEND_ACCOUNT(tr("Account"), 26);

        HDB_APPEND_MANUFACTURER(tr("Ural Metall"), 11);
        HDB_APPEND_THING(tr("Hammer"), 11, 2, HACC_TAG_ID_OBJECT    );
        HDB_APPEND_THING(tr("Pliers"), 11, 2, HACC_TAG_ID_OBJECT    );
        HDB_APPEND_THING(tr("Nails") , 11, 5, HACC_TAG_ID_EXPENDABLE);
        HDB_APPEND_THING(tr("Chain") , 11, 9, HACC_TAG_ID_EXPENDABLE);

        HDB_APPEND_MANUFACTURER(tr("Transcend"), 5);
        HDB_APPEND_THING(tr("Flash card"), 5, 2, HACC_TAG_ID_OBJECT);
        HDB_APPEND_THING(tr("USB hub")   , 8, 2, HACC_TAG_ID_OBJECT);

        HDB_APPEND_MANUFACTURER(tr("Silicon Image"), 5);
        HDB_APPEND_THING(tr("Flash card"), 12, 2, HACC_TAG_ID_OBJECT);
        HDB_APPEND_THING(tr("USB hub")   ,  8, 2, HACC_TAG_ID_OBJECT);

        HDB_APPEND_MANUFACTURER(tr("Sigma"), 12);
        HDB_APPEND_THING(tr("Toner Fill")      , 5 , 3, HACC_TAG_ID_SERVICE);
        HDB_APPEND_THING(tr("HDD restore")     , 8 , 3, HACC_TAG_ID_SERVICE);
        HDB_APPEND_THING(tr("Printer flushing"), 15, 3, HACC_TAG_ID_SERVICE);

    #endif
}

}
