/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
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
#include "dprogress.h"
#include "hacc_debug.h"

//! Объявляет и реализует обычный синглтон
/**
  Не забыть добавтиь в конструктор и деструктор CSingletone init_?() и destroy_?() методы.
  Автоматически создает объект при первом обращении. Далее использует уже существующий
  */
#define HACC_SIMPLE_ST(_class, _variable) \
private:\
    _class *m_##_variable; \
    void init_##_variable()    { m_##_variable = NULL;                     } \
    void destroy_##_variable() { HACC_DEBUG_CLASS_INFO("delete " #_class); delete m_##_variable; init_##_variable(); } \
public: \
    _class *_variable () \
    { \
        if(!m_##_variable) \
        { \
            m_##_variable = new _class(); \
            HACC_DEBUG_CLASS_INFO("new " #_class); \
        } \
        HACC_DEBUG_CLASS_INFO("->" #_class << " [" << m_##_variable << "]"); \
        return m_##_variable; \
    }

//! Объявляет и реализует преинициализированный синглтон
/**
  Не забыть добавтиь в конструктор и деструктор CSingletone init_?() и destroy_?() методы.
  Создает объект при вызове конструктора CSingletone. Его и использует впоследствии.
  */
#define HACC_PRECREATED_ST(_class, _variable) \
    _class *m_##_variable; \
    void init_##_variable()    { m_##_variable = new _class(); } \
    void destroy_##_variable() { delete m_##_variable;         } \
public: \
    _class *_variable () \
    { \
        HACC_DEBUG_CLASS_INFO("->" #_class << " [" << m_##_variable << "]"); \
        return m_##_variable; \
    }

//! Синглтон приложения.
/**
  Обеспечивает доступ к синглтонам сущностей и прочим синглтонам.
*/
class CSingletone
{
    //! @name Объекты-синглтоны
    //! @{
    HACC_SIMPLE_ST(tools::db::CDatabase              , db                  )
    HACC_SIMPLE_ST(tools::icons::CDBIconsCache       , dbIcons             )
    HACC_SIMPLE_ST(tools::icons::CIconsCache         , icons               )
    HACC_SIMPLE_ST(ui::form::FMainWindow             , window              )
    HACC_SIMPLE_ST(ui::form::DProgress               , progress            )
    HACC_SIMPLE_ST(hacc::model::CTags                , tags                )
    HACC_SIMPLE_ST(hacc::model::CThings              , things              )
    HACC_SIMPLE_ST(hacc::model::CAccounts            , accounts            )
    HACC_SIMPLE_ST(hacc::model::CValuables           , valuables           )
    HACC_SIMPLE_ST(hacc::model::CMovements           , movements           )
    HACC_SIMPLE_ST(hacc::model::CCurrencyes          , currencyes          )
    HACC_SIMPLE_ST(hacc::model::CContractors         , contractors         )
    HACC_SIMPLE_ST(hacc::model::CTransactions        , transactions        )
    HACC_SIMPLE_ST(hacc::model::CManufacturers       , manufacturers       )
    HACC_SIMPLE_ST(hacc::model::CTransactionPools    , transactionsPools   )
    HACC_SIMPLE_ST(hacc::model::CEnumeratedThingTypes, enumeratedThingTypes)
    HACC_PRECREATED_ST(tools::options::COptions      , options             )
    //! @}

private:
    CApplication *m_application;
    CSingletone(const CSingletone&);
    CSingletone& operator=(const CSingletone&);

public:
    CSingletone();
    ~CSingletone();
    void run(int & argc, char ** argv); //!< Обработка коммандной строки
    CApplication *application();

    static CSingletone *instance();                //!< Экземпляр синглтона.
};
#endif

