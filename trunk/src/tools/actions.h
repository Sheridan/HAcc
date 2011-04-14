#ifndef ACTIONS_H
#define ACTIONS_H
#include <QAction>

namespace tools
{
//! работа с действиями (QAction)
namespace actions
{

QAction * constructAction(const QIcon & icon, const QString &caption, const QString &toolTip);
QAction * constructAction(const QIcon & icon, const QString &caption, const QString &toolTip, const QObject * receiver, const char * method);

}
}
#endif // ACTIONS_H
