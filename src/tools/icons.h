#ifndef CICONTOOL_H
#define CICONTOOL_H

#include <QIcon>
#include <QSize>

namespace tools
{
namespace icons
{

QIcon stratificateIcons (const QIcon &source        , const QIcon   &layer      ); //!< Накладывает одну иконку на другую
QIcon stratificateIcons (const QString &sourceFile  , const QString &layerFile  ); //!< Накладывает одну иконку на другую
QIcon stratificateIcons (const QString &sourceFile  , const QIcon   &layer      ); //!< Накладывает одну иконку на другую
QIcon stratificateIcons (const QIcon &source        , const QString &layerFile  ); //!< Накладывает одну иконку на другую
QIcon setIconOpacity    (const QIcon &icon          , const float   &opacity    ); //!< Управляет прозрачностью иконки
QIcon setIconOpacity    (const QString &iconFile    , const float   &opacity    ); //!< Управляет прозрачностью иконки

}
}

#endif // CICONTOOL_H
