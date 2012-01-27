/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CBASE_H
#define CBASE_H

#include <QObject>
#include <QMap>
#include <QMessageBox>
#include "hacc_types.h"
#include "actions.h"
#include "special_tags_types.h"
//! Пространство проекта
namespace hacc
{
//! Модель
namespace model
{
//! База модели
namespace base
{
//! Типы действий
/*! Используется при генерировании QAction как флаги, определяющие - какое именно нужно действие */
enum EActionsTypes
{
    atAdd,                      //!< Добавление
    atEdit,                     //!< Редактирование
    atRemove,                   //!< Удаление
    atTagsEdit,                 //!< Редактирование тегов
    atContractorAddSelf,        //!< Специальный тип: собственный контрагент, "я"
    atTransactionSell,          //!< Специальный тип: транзакция продажи
    atTransactionBuy,           //!< Специальный тип: транзакция покупки
    atTransactionGiveGift,      //!< Специальный тип: дарение подарка
    atTransactionAcceptGift,    //!< Специальный тип: получение подарка
    atTransactionMoneyIncoming, //!< Специальный тип: приходящие деньги (зарплата, находка...)
    atTransactionMoneyOutgoing, //!< Специальный тип: расходы денег (потеря)
    atTransactionLocal          //!< Специальный тип: локальный трансфер между счетами
};

//! Базовый класс для синглтонов, работающих с таблицами
class CBases : public QObject
{
    Q_OBJECT
public:
    CBases();
    virtual ~CBases();
    //! @defgroup singletoneQActionsGenerators Генераторы QAction в синглтонах
    //! @{
    //! Возвращают готовые к привязыванию к элементам управления QAction'ы
    QAction * addAction     (const hacc::TDBID &id, QObject *reciever, const char * method);
    QAction * editAction    (const hacc::TDBID &id, QObject *reciever, const char * method);
    QAction * removeAction  (const hacc::TDBID &id, QObject *reciever, const char * method);
    QAction * tagsEditAction(const hacc::TDBID &id, QObject *reciever, const char * method);
    //! @}
protected:
    /**
      * Генерирует и возвращает новую QAction
      * @see constructAction()
      * @see m_actions
      */
    virtual QAction * generateAction(EActionsTypes atype, QObject *reciever, const char * method) = 0;
    QAction * constructAction(EActionsTypes atype, const hacc::TDBID &id, QObject *reciever, const char * method); //!< Конструктор действий
    hacc::TDBID nextID();               //!< Новый уникальный идентификатор
    virtual hacc::TDBID maxDBID() = 0;  //!< Должна возвратить максимальный идентификатор записи для таблицы

private:

    QMap<EActionsTypes, QMap<hacc::TDBID, QAction *> > m_actions; //!< Кеш QAction для повторного использования
    /**
      * Максимальный идентификатор записи для таблицы БД
      * @see nextID()
      * @see maxDBID()
      */
    hacc::TDBID m_maxID;

signals:
    void updated(const hacc::TDBID &); //!< Сигнал о том, что запись в таблице изменена
    void removed(const hacc::TDBID &); //!< Сигнал о том, что запись в таблице уалена
    void created(const hacc::TDBID &); //!< Сигнал о том, в таблице появилась новая запись
};

}
}
}
//! Вспомогательный макрос для switch'а генератора
#define HACC_GENERATE_ACTION_CASE(_key,_iIcon,_oIcon,_title,_ttip) case _key: return tools::actions::constructAction( HACC_ICONS->icon(_iIcon, _oIcon), _title, _ttip, reciever, method);

#endif // CBASE_H
