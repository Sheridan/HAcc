#include "csingletone.h"

CSingleTone *singletone_instance = NULL;

CSingleTone::CSingleTone()
{
    singletone_instance = this;
    HACC_DEBUG_CLASS_INFO("new CSingleTone [" << singletone_instance << "]");

    m_application = NULL;
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

CSingleTone::~CSingleTone()
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
    HACC_DEBUG_CLASS_INFO("delete CSingleTone [" << singletone_instance << "]");
}

CSingleTone *CSingleTone::instance()
{
    if(singletone_instance)
    {
        HACC_DEBUG_CLASS_INFO("->CSingleTone [" << singletone_instance << "]");
        return singletone_instance;
    }
    return new CSingleTone();
}

void CSingleTone::setCommandLine(int & argc, char ** argv)
{
    m_application = new CApplication(argc, argv);
}

CApplication *CSingleTone::application()
{
    HACC_DEBUG_CLASS_INFO("->CApplication [" << m_application << "]");
    return m_application;
}

CSingleTone::CSingleTone(const CSingleTone&) {}
CSingleTone & CSingleTone::operator=(const CSingleTone&)
{
//    Q_UNUSED(s);
    return *this;
}
