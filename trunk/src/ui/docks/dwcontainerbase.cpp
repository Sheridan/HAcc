#include "dwcontainerbase.h"
#include "ui_dwcontainerbase.h"
#include "wcontainer.h"
#include <QIcon>

namespace ui
{
namespace dock
{

//HACC_STD_TRANSLATE_UI(DWContainerBase, QDockWidget)

DWContainerBase::DWContainerBase(const QString &title, const QIcon &icon, QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::DWContainerBase)
{
    ui->setupUi(this);
    setWindowTitle(title);
    setWindowIcon(icon);
    m_containerBase = NULL;
}

DWContainerBase::~DWContainerBase()
{
    delete m_containerBase;
    delete ui;
}

void DWContainerBase::init()
{
    m_containerBase = constructContainerBase();
    m_containerBase->buildUi();
    m_containerBase->container()->refresh();
    setWidget(m_containerBase);
}


}
}
