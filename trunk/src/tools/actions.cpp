#include "actions.h"

namespace tools
{
namespace actions
{

QAction * constructAction(const QIcon & icon, const QString &caption, const QString &toolTip)
{
    QAction *a = new QAction(icon, caption, NULL);
    a->setToolTip(toolTip);
    return a;
}

QAction * constructAction(const QIcon & icon, const QString &caption, const QString &toolTip, const QObject * receiver, const char * method)
{
    QAction *a = constructAction(icon, caption, toolTip);
    QObject::connect(a, SIGNAL(triggered()), receiver, method);
    return a;
}

}
}
