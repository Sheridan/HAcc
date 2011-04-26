#include "resources.h"
#include <QFile>
#include <QTextStream>
#include <QMap>
#include "hacc_debug.h"

namespace tools
{
namespace resources
{

static QMap<QString, QString> resources; //!< Кеш текстовых ресурсов
QString & readTextResource(const QString &name)
{
    //! \todo Выяснить - а на самом ли деле быстрее взять из кеша, чем заново прочитать из ресурсов
    if(!resources.contains(name))
    {
        QFile file(name);
        QString string = "";
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            while (!in.atEnd())
            {
                string += in.readLine();
            }
        }
        resources[name] = string;
//        HACC_DEBUG(string);
    }
    return resources[name];
}

}
}
