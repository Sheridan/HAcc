#ifndef FONT_H
#define FONT_H

#include <QFont>
#include <QString>

//! Вспомогательные средства
namespace tools
{
//! Работа с шрифтом
namespace font
{
    int fontHeight(const QFont &font); //!< Вычисление высоты шрифта
}
}

#endif // FONT_H
