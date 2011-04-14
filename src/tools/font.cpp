#include "font.h"

#include <QFontMetrics>

namespace tools
{
namespace font
{

int fontHeight(const QFont &font)
{
    QFontMetrics fm (font);
    return fm.height();
}

}
}
