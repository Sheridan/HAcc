/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef HACC_DATE_H
#define HACC_DATE_H

namespace tools
{
//! Работа с датой
namespace date
{

//! Ключи периодов времени
enum ETimePeriods
{
    tpDays   = 0,
    tpWeeks  = 1,
    tpMonths = 2,
    tpYears  = 3
};

//! Периоды времени
struct STimePeriod
{
    int days;
    ETimePeriods period;
};

int daysFrom(const int &number, const ETimePeriods &period); //!< Количество дней за период
int daysFrom(const int &number, const int &period);          //!< Количество дней за период
STimePeriod daysTo(const int &days);                         //!< Вычисление периода, исходя из количества дней

}
}
#endif // HACC_DATE_H
