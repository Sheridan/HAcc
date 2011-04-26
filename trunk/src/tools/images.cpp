#include "images.h"
#include <QIODevice>
#include <QBuffer>

namespace tools
{
namespace images
{

QPixmap byteArray2Pixmap(const QByteArray &array)
{
    QPixmap pixmap;
    pixmap.loadFromData(array, "PNG");
    return pixmap;
}

QByteArray pixmap2ByteArray(const QPixmap &pixmap)
{
    return pixmap2ByteArray(&pixmap);
}

QByteArray pixmap2ByteArray(const QPixmap *pixmap)
{
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    pixmap->save(&buffer, "PNG");
    return bytes;
}

}
}
