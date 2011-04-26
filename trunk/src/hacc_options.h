#ifndef HACC_OPTIONS_H
#define HACC_OPTIONS_H

#include "st.h"

#define HACC_OPTION_PATH(_section, _value) #_section, #_value

#define HACC_O_DEFAULT_CURRENCY_PATH HACC_OPTION_PATH(defaults, currency)
#define HACC_O_DEFAULT_CURRENCY (HACC_OPTIONS->sectionValue(HACC_O_DEFAULT_CURRENCY_PATH, 0).toUInt())
#define HACC_O_DEFAULT_CURRENCY_SET(_id) HACC_OPTIONS->setSectionValue(HACC_O_DEFAULT_CURRENCY_PATH, _id);

#define HACC_O_MDI_PATH HACC_OPTION_PATH(view, mdi)
#define HACC_O_MDI (HACC_OPTIONS->sectionValue(HACC_O_MDI_PATH, false).toBool())
#define HACC_O_MDI_SET(_mdi) HACC_OPTIONS->setSectionValue(HACC_O_MDI_PATH, _mdi);

#define HACC_O_PREDECLARED_ICONS_PATH HACC_OPTION_PATH(defaults, predeclaredicons)
#define HACC_O_PREDECLARED_ICONS (HACC_OPTIONS->sectionValue(HACC_O_PREDECLARED_ICONS_PATH, 0).toUInt())
#define HACC_O_PREDECLARED_ICONS_SET(_count) HACC_OPTIONS->setSectionValue(HACC_O_PREDECLARED_ICONS_PATH, _count);

#endif // HACC_OPTIONS_H
