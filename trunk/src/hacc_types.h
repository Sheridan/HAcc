#ifndef HACC_TYPES_H
#define HACC_TYPES_H

#include <QList>

namespace hacc
{
    typedef unsigned int TDBID;           //!< Идентификатор записи БД
    typedef QList<hacc::TDBID> TIDList;   //!< Список идентификаторов БД

    typedef double TMoney;                //!< Деньги
    typedef double TAmount;               //!< Количество

    //! Деньги + коммисия для транзакций денежных переводов
    struct SMoneyCommission
    {
        TMoney money;
        TMoney commission;
    };
}

//! @defgroup db2thisconvrters Конвертеры из записей БД
//! @{
/** Конвертируют данные из записей бд в используемые тут сущности.
  Также крайне желательно имена макросов делать одинаковой длинны для того чтобы в коде было все ровно и красиво.
  */
#define HACC_DB_2_DBID(_q, _i) (static_cast<hacc::TDBID  >(_q.value(_i).toUInt    ())) //!< ID
#define HACC_DB_2_DATI(_q, _i) (                           _q.value(_i).toDateTime() ) //!< Date and time
#define HACC_DB_2_STRG(_q, _i) (                           _q.value(_i).toString  () ) //!< String
#define HACC_DB_2_MONY(_q, _i) (static_cast<hacc::TMoney >(_q.value(_i).toDouble  ())) //!< Money
#define HACC_DB_2_AMNT(_q, _i) (static_cast<hacc::TAmount>(_q.value(_i).toDouble  ())) //!< Amount
#define HACC_DB_2_TYPE(_q, _i) (                           _q.value(_i).toUInt    () ) //!< Some type
#define HACC_DB_2_INTR(_q, _i) (                           _q.value(_i).toInt     () ) //!< Some integer
#define HACC_DB_2_BOOL(_q, _i) (                           _q.value(_i).toBool    () ) //!< Bool
#define HACC_DB_2_PERD(_q, _i) HACC_DB_2_INTR(_q, _i)                                  //!< Period
#define HACC_DB_2_PREC(_q, _i) HACC_DB_2_INTR(_q, _i)                                  //!< Precission
//! @}

#endif // HACC_TYPES_H
