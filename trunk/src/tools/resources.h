/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef RESOURCES_H
#define RESOURCES_H

#include <QString>

namespace tools
{
//! Ресурсы приложения
namespace resources
{

QString & readTextResource(const QString &name); //!< Читает, сохраняя в кеше и возвращает текстовый ресурс.

}
}
#endif // RESOURCES_H
