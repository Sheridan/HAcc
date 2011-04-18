#ifndef CSINGLETONE_H
#define CSINGLETONE_H

#include "capplication.h"
#include "coptions.h"
#include "fmainwindow.h"
#include "cdatabase.h"
#include "ciconscache.h"
#include "cdbiconscache.h"
#include "caccounts.h"
#include "cvaluables.h"
#include "ccurrencyes.h"
#include "cthings.h"
#include "ccontractors.h"
#include "cmovements.h"
#include "ctransactions.h"
#include "cmanufacturers.h"
#include "ctransactionspools.h"
#include "cenumeratedthingtypes.h"
#include "ctags.h"
#include "hacc_debug.h"

#define HACC_SIMPLE_ST(_class, _variable) \
private:\
    _class *_##_variable; \
    void init_##_variable()    { _##_variable = NULL;                     } \
    void destroy_##_variable() { HACC_DEBUG_CLASS_INFO("delete " #_class); delete _##_variable; init_##_variable(); } \
public: \
    _class *_variable () \
    { \
        if(!_##_variable) \
        { \
            _##_variable = new _class(); \
            HACC_DEBUG_CLASS_INFO("new " #_class); \
        } \
        HACC_DEBUG_CLASS_INFO("->" #_class << " [" << _##_variable << "]"); \
        return _##_variable; \
    }

#define HACC_PRECREATED_ST(_class, _variable) \
    _class *_##_variable; \
    void init_##_variable()    { _##_variable = new _class(); } \
    void destroy_##_variable() { delete _##_variable;         } \
public: \
    _class *_variable () \
    { \
        HACC_DEBUG_CLASS_INFO("->" #_class << " [" << _##_variable << "]"); \
        return _##_variable; \
    }

//! Синглтон приложения.
/**
  Обеспечивает доступ к синглтонам сущностей и прочим синглтонам.
*/
class CSingleTone
{
    HACC_SIMPLE_ST(tools::db::CDatabase              , db);
    HACC_SIMPLE_ST(tools::icons::CDBIconsCache       , dbIcons);
    HACC_SIMPLE_ST(tools::icons::CIconsCache         , icons);
    HACC_SIMPLE_ST(ui::form::FMainWindow             , window);
    HACC_SIMPLE_ST(hacc::model::CTags                , tags);
    HACC_SIMPLE_ST(hacc::model::CThings              , things);
    HACC_SIMPLE_ST(hacc::model::CAccounts            , accounts);
    HACC_SIMPLE_ST(hacc::model::CValuables           , valuables);
    HACC_SIMPLE_ST(hacc::model::CMovements           , movements);
    HACC_SIMPLE_ST(hacc::model::CCurrencyes          , currencyes);
    HACC_SIMPLE_ST(hacc::model::CContractors         , contractors);
    HACC_SIMPLE_ST(hacc::model::CTransactions        , transactions);
    HACC_SIMPLE_ST(hacc::model::CManufacturers       , manufacturers);
    HACC_SIMPLE_ST(hacc::model::CTransactionsPools   , transactionsPools);
    HACC_SIMPLE_ST(hacc::model::CEnumeratedThingTypes, enumeratedThingTypes);
    HACC_PRECREATED_ST(options::COptions             , options);

private:
    CApplication *_application;

public:
    CSingleTone();
    ~CSingleTone();
    void setCommandLine(int & argc, char ** argv);
    CApplication *application();

    static CSingleTone *instance();
};
#endif

