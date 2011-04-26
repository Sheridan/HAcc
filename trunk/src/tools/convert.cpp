#include "convert.h"
#include <QRegExp>

namespace tools
{
namespace convert
{

QString moneyToString (const hacc::TMoney  &money)                        { return QString::number(money ,'f', 2);         }
QString amountToString(const hacc::TAmount &amount, const int &precision) { return QString::number(amount,'f', precision); }

QString datetimeToString    (const QDateTime &datetime) { return datetime.toString("dd.MM.yyyy HH:mm"); }
QString datetimeToDateString(const QDateTime &datetime) { return datetime.toString("dd.MM.yyyy"      ); }
QString datetimeToTimeString(const QDateTime &datetime) { return datetime.toString(           "HH:mm"); }

hacc::TMoney stringToMoney(QString string)
{
    return static_cast<hacc::TMoney>
            (
                string.replace(",", ".")
                      .replace(QRegExp("[^\\.0-9]*") ,"")
                      .toDouble()
            );
}

hacc::TAmount stringToAmount(QString string)
{
    return static_cast<hacc::TAmount>
            (
                string.replace(",", ".")
                      .replace(QRegExp("[^\\.0-9]*") ,"")
                      .toDouble()
            );
}


}
}
