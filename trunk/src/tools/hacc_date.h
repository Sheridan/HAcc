#ifndef HACC_DATE_H
#define HACC_DATE_H

namespace tools
{
//! Работа с датой
namespace date
{

enum ETimePeriods
{
    tpDays   = 0,
    tpWeeks  = 1,
    tpMonths = 2,
    tpYears  = 3
};

struct STimePeriod
{
    int days;
    ETimePeriods period;
};

int daysFrom(const int &number, const ETimePeriods &period);
int daysFrom(const int &number, const int &period);
STimePeriod daysTo(const int &days);

}
}
#endif // HACC_DATE_H
