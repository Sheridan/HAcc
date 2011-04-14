#include "csingletone.h"

CSingleTone *_instance = NULL;

CSingleTone::CSingleTone()
{
    _instance = this;
    HACC_DEBUG_CLASS_INFO("new CSingleTone [" << _instance << "]");

    _application = NULL;
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
    delete _application;
    HACC_DEBUG_CLASS_INFO("delete CSingleTone [" << _instance << "]");
}

CSingleTone *CSingleTone::instance()
{
    if(_instance)
    {
        HACC_DEBUG_CLASS_INFO("->CSingleTone [" << _instance << "]");
        return _instance;
    }
    return new CSingleTone();
}

void CSingleTone::setCommandLine(int & argc, char ** argv)
{
    _application = new CApplication(argc, argv);
}

CApplication *CSingleTone::application()
{
    HACC_DEBUG_CLASS_INFO("->CApplication [" << _application << "]");
    return _application;
}

