#include "csingletone.h"

CSingletone *singletone_instance = NULL;

CSingletone::CSingletone()
{
    singletone_instance = this;
    HACC_DEBUG_CLASS_INFO("new CSingletone [" << singletone_instance << "]");

    m_application = NULL;
}

CSingletone::~CSingletone()
{
    db()->close();

    destroy_window();
    destroy_icons();
    destroy_dbIcons();
    destroy_tags();
    destroy_accounts();
    destroy_valuables();
    destroy_movements();
    destroy_currencyes();
    destroy_contractors();
    destroy_things();
    destroy_transactions();
    destroy_manufacturers();
    destroy_transactionsPools();
    destroy_enumeratedThingTypes();
    destroy_db();
    destroy_options();
    delete m_application;
    HACC_DEBUG_CLASS_INFO("delete CSingletone [" << singletone_instance << "]");
}

CSingletone *CSingletone::instance()
{
    if(singletone_instance)
    {
        HACC_DEBUG_CLASS_INFO("->CSingletone [" << singletone_instance << "]");
        return singletone_instance;
    }
    return new CSingletone();
}

void CSingletone::run(int & argc, char ** argv)
{
    m_application = new CApplication(argc, argv);
    init_options();
    init_db();
    init_tags();
    init_accounts();
    init_valuables();
    init_movements();
    init_currencyes();
    init_contractors();
    init_things();
    init_transactions();
    init_manufacturers();
    init_transactionsPools();
    init_enumeratedThingTypes();
    init_dbIcons();
    init_icons();
    init_window();
}

CApplication *CSingletone::application()
{
    HACC_DEBUG_CLASS_INFO("->CApplication [" << m_application << "]");
    return m_application;
}

CSingletone::CSingletone(const CSingletone&) {}
CSingletone & CSingletone::operator=(const CSingletone&)
{
    return *this;
}
