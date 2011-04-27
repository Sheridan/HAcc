/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CONVERT_H
#define CONVERT_H

#include "hacc_types.h"
#include <QString>
#include <QDateTime>

namespace tools
{
//! Конвертеры значений
namespace convert
{
QString moneyToString (const hacc::TMoney  &money);                        //!< Деньги в строку
QString amountToString(const hacc::TAmount &amount, const int &precision); //!< Количество в строку

QString datetimeToString    (const QDateTime &datetime);                   //!< Дата/время в строку
QString datetimeToDateString(const QDateTime &datetime);                   //!< Датв в строку
QString datetimeToTimeString(const QDateTime &datetime);                   //!< Время в строку

hacc::TMoney  stringToMoney (QString string);                              //!< Строка в деньги
hacc::TAmount stringToAmount(QString string);                              //!< Строка в количество
}
}
#endif // CONVERT_H
