#ifndef CICONSCACHE_H
#define CICONSCACHE_H

#include <QMap>
#include <QString>
#include <QIcon>

namespace tools
{
//! Иконки приложения
namespace icons
{

//! Иконки
enum EIcons
{
    iTag,            //!< Метка
    iGift,           //!< Подарок
    iIcon,           //!< Иконка
    iMoney,          //!< Деньги
    iThing,          //!< Вещь
    iAccount,        //!< Счет
    iMovement,       //!< Перемещение
    iValuable,       //!< Ценность
    iCurrency,       //!< Валюта
    iContractor,     //!< Контрагент
    iEnumerated,     //!< Перечисляемое
    iDescription,    //!< Описание
    iTransaction,    //!< Танзакция
    iManufacturer,   //!< Производитель
    iContractorSelf, //!< Собственный контрагент
    iTransactionPool //!< Пул транзакций
};

//! Оверлеи
enum EOverlays
{
    oNew,            //!< Новое...
    oTag,            //!< Метка
    oEdit,           //!< Редактирование
    oLocal,          //!< Локальное действие
    oRemove,         //!< Удаление
    oIncoming,       //!< Входящее...
    oOutgoing,       //!< Исходящее...
    oWriteOff,       //!< Списание
    oNewWindow,      //!< Новое окно
    oCommission      //!< Коммиссия
};

//! Кеш иконок из ресурсов
class CIconsCache
{
public:
    CIconsCache();
    ~CIconsCache();
    const QIcon & icon(const EIcons &eIcon, const EOverlays &eOverlay); //!< Иконка из иконки сущности и оверлея
    const QIcon & icon(const int& tagID);                               //!< Иконка для некоторых тегов
    const QIcon & icon(const EIcons &eIcon);                            //!< Иконка сущностей
private:
    int id(const EIcons &eIcon, const EOverlays &eOverlay);             //!< Вычисление идентификатора
    QMap<int   , QIcon *> m_icons ;                                     //!< Кеш иконок с вычисленым идентификатором
    QMap<EIcons, QIcon *> m_eIcons;                                     //!< Кеш иконок сущностей
};

}
}
#endif // CICONSCACHE_H
