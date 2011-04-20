#ifndef CBASES_H
#define CBASES_H

#include <QObject>
#include "ciditem.h"
#include "actions.h"
#include "cbases.h"

namespace hacc
{
namespace model
{
namespace base
{

//! Базовый класс для сущностей
/*!
 Наследники этого класса отражают единственную запись БД, причем хранится только идентификатор этой записи.
 Другие поля не отображаются тут.
 Данные классы реализованы для того, чтобы была возможность отследить за изменением записей и как-то на это реагировать.
 Причем для реагирования достаточно реализовать соответствующую виртуальную функцию.
 Также наследники предоставляют действия (QAction) для своих записей. Например "Редактировать", "Удалить"
*/
class CBase :
        public QObject,
        public hacc::CIDItem
{
    Q_OBJECT
public:
    explicit CBase();
    virtual ~CBase();
    //! @defgroup recordsQActionsGenerators Генераторы QAction для сущностей
    //! @{
    //! Возвращают готовые к привязыванию к элементам управления QAction'ы
    virtual QAction *editAction()   = 0;
    virtual QAction *removeAction() = 0;
    //! @}
    virtual CBases  *worker() = 0;  //!< Синглтон сущности (для CAccount - CAccounts например)

public slots:
    virtual void edit()   = 0;
    virtual void remove() = 0;

protected slots:
    virtual void updated(const hacc::TDBID & inID) = 0; //!< Сигнал о обновлении записи
    virtual void removed(const hacc::TDBID & inID) = 0; //!< Сигнал об удалении записи

};

}
}
}

//! @name Слежение за изменениями
//! @{

//! Объявление слотов и виртуальных функций, реализация вызовов
#define HACC_MODEL_BASE_EVENTS_DECLARE(_type) \
    private slots: \
        void updated(const hacc::TDBID & inID) { if(inID == id()) { _type##Updated(); } } \
        void removed(const hacc::TDBID & inID) { if(inID == id()) { _type##Removed(); } }  \
    protected: \
        virtual void _type##Updated() {}; \
        virtual void _type##Removed() {};

//! Прикручивание слотов к сигналам.
#define HACC_MODEL_BASE_EVENTS_INITIALIZE(_bases) \
    connect(_bases, SIGNAL(updated(const hacc::TDBID &)), this, SLOT(updated(const hacc::TDBID &))); \
    connect(_bases, SIGNAL(removed(const hacc::TDBID &)), this, SLOT(removed(const hacc::TDBID &)));
//! @}
#endif // CBASES_H
