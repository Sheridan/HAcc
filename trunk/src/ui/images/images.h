#ifndef IMAGES_H
#define IMAGES_H
#include <QPixmap>
#include <QByteArray>

namespace ui
{
namespace images
{

QPixmap    byteArray2Pixmap(const QByteArray &array );
QByteArray pixmap2ByteArray(const QPixmap    &pixmap);
QByteArray pixmap2ByteArray(const QPixmap    *pixmap);

}
}
#endif // IMAGES_H
