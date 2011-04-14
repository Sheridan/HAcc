
#include "st.h"
#include "capplication.h"
#include "resources.h"

CApplication::CApplication(int & argc, char ** argv) : QApplication(argc, argv)
{
    setAuthor();
}

CApplication::~CApplication()
{}

void CApplication::setAuthor()
{
    setOrganizationDomain("http://www.sheridan-home.ru/");
    setOrganizationName  ("sheridan");
    setApplicationName   ("hacc");
}

void CApplication::refreshStyleSheets()
{
    setStyleSheet(tools::resources::readTextResource(":/qss/default.qss"));
}

int CApplication::run()
{
    refreshStyleSheets();
    HACC_WINDOW->show();
    return exec();
}



