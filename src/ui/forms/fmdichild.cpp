#include "fmdichild.h"
#include <QIcon>
#include "wcontainer.h"
#include <QCloseEvent>
//#include "ui_defines.h"

namespace ui
{
namespace form
{

//HACC_STD_TRANSLATE_UI(FMDIChild, QMdiSubWindow)

FMDIChild::FMDIChild(const QString &title, const QIcon &icon, QWidget *parent) : QMdiSubWindow(parent)
{
    setWindowTitle(title);
    setWindowIcon(icon);
//    setAttribute(Qt::WA_DeleteOnClose);
    m_containerBase = NULL;
    m_index = -1;
}

FMDIChild::~FMDIChild()
{
    delete m_containerBase;
}

void FMDIChild::setIndex(const int &index)
{
    m_index = index;
}

void FMDIChild::init()
{
    m_containerBase = constructContainerBase();
    m_containerBase->buildUi();
    m_containerBase->container()->refresh();
    setWidget(m_containerBase);
}

void FMDIChild::closeEvent ( QCloseEvent * closeEvent )
{
    emit closing(m_index);
    closeEvent->accept();
}

}
}
