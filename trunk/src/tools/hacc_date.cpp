#include "hacc_date.h"

#define HACC_DAYS_IN_WEEK 7
#define HACC_DAYS_IN_MONTH 30
#define HACC_DAYS_IN_YEAR 365

namespace tools
{
namespace date
{

int daysFrom(const int &number, const ETimePeriods &period)
{
    switch(period)
    {
    case tpDays  : return number;
    case tpWeeks : return number * HACC_DAYS_IN_WEEK;
    case tpMonths: return number * HACC_DAYS_IN_MONTH;
    case tpYears : return number * HACC_DAYS_IN_YEAR;
    }
    return 0;
}

int daysFrom(const int &number, const int &period)
{
    return daysFrom(number, static_cast<ETimePeriods>(period));
}

STimePeriod daysTo(const int &days)
{
    STimePeriod period;
    if(days < HACC_DAYS_IN_WEEK)
    {
        period.days = days;
        period.period = tpDays;
    }
    else if(days >= HACC_DAYS_IN_WEEK && days < HACC_DAYS_IN_MONTH && !(days % HACC_DAYS_IN_WEEK))
    {
        period.days = days / HACC_DAYS_IN_WEEK;
        period.period = tpWeeks;
    }
    else if(days >= HACC_DAYS_IN_MONTH && days < HACC_DAYS_IN_YEAR && !(days % HACC_DAYS_IN_MONTH))
    {
        period.days = days / HACC_DAYS_IN_MONTH;
        period.period = tpMonths;
    }
    else if(days >= HACC_DAYS_IN_YEAR && !(days % HACC_DAYS_IN_YEAR))
    {
        period.days = days / HACC_DAYS_IN_YEAR;
        period.period = tpMonths;
    }
    else
    {
        period.days = days;
        period.period = tpDays;
    }
    return period;
}

}
}
