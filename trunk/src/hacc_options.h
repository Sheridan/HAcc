#ifndef HACC_OPTIONS_H
#define HACC_OPTIONS_H

#include "st.h"

#define HACC_OPTION_PATH(_section, _key) #_section, #_key
#define HACC_OPTION_DB_PATH(_key)                   #_key

// Опции из БД
//! @name Валюта по умолчанию
//! @{
#define HACC_O_DEFAULT_CURRENCY_PATH     HACC_OPTION_DB_PATH(currency)
#define HACC_O_DEFAULT_CURRENCY          (HACC_OPTIONS->dbValue(HACC_O_DEFAULT_CURRENCY_PATH, 0).toUInt())
#define HACC_O_DEFAULT_CURRENCY_SET(_id) HACC_OPTIONS->setDBValue(HACC_O_DEFAULT_CURRENCY_PATH, _id);
//! @}

//! @name Количество предопределенных иконок
//! @{
#define HACC_O_PREDECLARED_ICONS_PATH        HACC_OPTION_DB_PATH(predeclaredicons)
#define HACC_O_PREDECLARED_ICONS             (HACC_OPTIONS->dbValue(HACC_O_PREDECLARED_ICONS_PATH, 0).toUInt())
#define HACC_O_PREDECLARED_ICONS_SET(_count) HACC_OPTIONS->setDBValue(HACC_O_PREDECLARED_ICONS_PATH, _count);
//! @}

// Опции из QSettings
//! @name MDI или нет?
//! @{
#define HACC_O_MDI_PATH      HACC_OPTION_PATH(view, mdi)
#define HACC_O_MDI           (HACC_OPTIONS->sectionValue(HACC_O_MDI_PATH, false).toBool())
#define HACC_O_MDI_SET(_mdi) HACC_OPTIONS->setSectionValue(HACC_O_MDI_PATH, _mdi);
//! @}

#endif // HACC_OPTIONS_H
