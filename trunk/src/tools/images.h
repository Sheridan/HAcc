/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef IMAGES_H
#define IMAGES_H
#include <QPixmap>
#include <QByteArray>

namespace tools
{
//! Картинки
namespace images
{

QPixmap    byteArray2Pixmap(const QByteArray &array ); //!< Конвертирует raw в пиксмап
QByteArray pixmap2ByteArray(const QPixmap    &pixmap); //!< Конвертирует пиксмап в raw
QByteArray pixmap2ByteArray(const QPixmap    *pixmap); //!< Конвертирует пиксмап в raw

}
}
#endif // IMAGES_H
