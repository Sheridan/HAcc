#ifndef CONVERT_H
#define CONVERT_H

#include "hacc_types.h"
#include <QString>
#include <QDateTime>

namespace tools
{
namespace convert
{
QString moneyToString (const hacc::TMoney  &money);
QString amountToString(const hacc::TAmount &amount, const int &precision);

QString datetimeToString    (const QDateTime &datetime);
QString datetimeToDateString(const QDateTime &datetime);
QString datetimeToTimeString(const QDateTime &datetime);

hacc::TMoney  stringToMoney (QString string);
hacc::TAmount stringToAmount(QString string);
}
}
#endif // CONVERT_H
