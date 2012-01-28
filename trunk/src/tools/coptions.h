/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef __COPTIONS_H__
#define __COPTIONS_H__
#include <QSettings>
#include <QWidget>
#include <QMainWindow>
#include <QTableWidget>

namespace tools
{
//! Настройки
namespace options
{

//! Настройки приложения
/**
Дает возможность чтото сохранить и прочитать обратно
  */
class COptions : public QSettings
{
Q_OBJECT
public:
    COptions();
    ~COptions();
    //! @name Секция-ключ-значение
    //! @{
    QStringList sectionKeys        (const QString & section);
    void        removeSection      (const QString & section);
    void        removeSectionValue (const QString & section, const QString & key);
    QVariant    sectionValue       (const QString & section, const QString & key, const QVariant & defaultValue = QVariant() );
    void        setSectionValue    (const QString & section, const QString & key, const QVariant & value        = QVariant() );
    QString     text               (const QString & section, const QString & key, const QString  & value        = QString () );
    void        setText            (const QString & section, const QString & key, const QString  & value);
    bool        exists             (const QString & section, const QString & key);
    //! @}
    //! @name Настройки, хранящиеся в БД
    //! @{
    void     setDBValue    (const QString & key, const QVariant & value);
    QVariant dbValue       (const QString & key, const QVariant & defaultValue = QVariant() );
    void     removeDBValue (const QString & key);
    //! @}
    //! @name Сохранение состояния некоторых контролов
    //! @{
    void        restoreState       (QWidget  *widget);
    void        restoreState       (QMainWindow  *mw);
//    void        restoreState       (QTableWidget *tw);
    void        saveState          (QWidget  *widget);
    void        saveState          (QMainWindow  *mw);
//    void        saveState          (QTableWidget *tw);
    bool        existsState        (QWidget *widget);
    bool        existsState        (QMainWindow *mw);
    //! @}

    void checkFirstStart(); //!< Проверка на первый запуск, вызывается после создания БД

signals:
    void        optionChanged      (const QString & section, const QString & key, const QVariant &);
};

}
}
#endif // __COPTIONS_H__
