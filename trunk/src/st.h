/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef __ST_H__
#define __ST_H__

#include "csingletone.h"
//! @defgroup singletones Синглтоны приложения
//! @{
#define HACC_SINGLETONE             CSingletone::instance()        //!< Синглтон
#define HACC_ST(_variable)          HACC_SINGLETONE->_variable()   //!< Шаблон для остальных
#define HACC_APPLICATION            HACC_SINGLETONE->application() //!< Приложение
#define HACC_OPTIONS                HACC_ST(options)               //!< Настройки приложения
#define HACC_WINDOW                 HACC_ST(window)                //!< Основное окно
#define HACC_PROGRESS               HACC_ST(progress)              //!< Окошко-прогрессбар для длительных операций
#define HACC_DB                     HACC_ST(db)                    //!< База данных
#define HACC_DB_ICONS               HACC_ST(dbIcons)               //!< Иконки из БД
#define HACC_ICONS                  HACC_ST(icons)                 //!< Иконки из ресурсов

#define HACC_TAGS                   HACC_ST(tags)                  //!< Метки
#define HACC_THINGS                 HACC_ST(things)                //!< Вещи
#define HACC_ACCOUNTS               HACC_ST(accounts)              //!< Счета
#define HACC_VALUABLES              HACC_ST(valuables)             //!< Основные средства
#define HACC_MOVEMENTS              HACC_ST(movements)             //!< Движение средств
#define HACC_CURRENCYES             HACC_ST(currencyes)            //!< Валюта
#define HACC_CONTRACTORS            HACC_ST(contractors)           //!< Контрагенты
#define HACC_TRANSACTIONS           HACC_ST(transactions)          //!< Транзакции
#define HACC_MANUFACTURERS          HACC_ST(manufacturers)         //!< Производители
#define HACC_TRANSACTIONS_POOLS     HACC_ST(transactionsPools)     //!< Пулы транзакций
#define HACC_ENUMERATED_THING_TYPES HACC_ST(enumeratedThingTypes)  //!< Перечисляемые типы
//! @}

#endif // __ST_H__
