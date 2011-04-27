/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef HACC_DEBUG_H
#define HACC_DEBUG_H

//! Включение/отключение дебага
#ifndef QT_NO_DEBUG
    #include <QDebug>
    //#define HACC_DEBUG_FUNCTION_ENABLED
    //#define HACC_DEBUG_OBJNAMES_ENABLED
    #define HACC_DEBUG_DB
    //! Обычный, базовый дебажный вывод в консоль
    #define HACC_DEBUG(_smth) qDebug() << _smth;
#else
    #define HACC_DEBUG(_smth) // _smth
#endif

//! Выводит файл, строку, метод класса. Для трассировки например
#ifdef HACC_DEBUG_FUNCTION_ENABLED
    #define HACC_DEBUG_FUNCTION_INFO     HACC_DEBUG(__FILE__ << " : " << __LINE__ << " : " << Q_FUNC_INFO);
    #define HACC_DEBUG_CLASS_INFO(_smth) HACC_DEBUG(_smth)
#else
    #define HACC_DEBUG_FUNCTION_INFO
    #define HACC_DEBUG_CLASS_INFO(_smth)
#endif

//! Генерирует и устанавливает имена объектам
#ifdef HACC_DEBUG_OBJNAMES_ENABLED
    #define HACC_DEBUG_OBJNAME_SET(_obj)     _obj->setObjectName(QString("%1 [%2:%3:%4]").arg(#_obj).arg(__FILE__).arg(__LINE__).arg(Q_FUNC_INFO));
#else
    #define HACC_DEBUG_OBJNAME_SET(_obj)
#endif

//! Выводит SQL запросы перед их исполнением
#ifdef HACC_DEBUG_DB
    #define HACC_DEBUG_SQL(_sql) HACC_DEBUG(_sql);
#else
    #define HACC_DEBUG_SQL(_obj)
#endif

#endif // HACC_DEBUG_H
