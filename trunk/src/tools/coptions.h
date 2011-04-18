//    Author: Sheridan <sheridan@stavcom.ru>, (C) 2006
//    Copyright: See COPYING file that comes with this distribution
//
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

class COptions : public QSettings
{
Q_OBJECT
public:
    COptions();
    ~COptions();
    QStringList sectionKeys        (const QString & section);
    void        removeSection      (const QString & section);
    void        removeSectionValue (const QString & section, const QString & key);
    QVariant    sectionValue       (const QString & section, const QString & key, const QVariant & defaultValue = QVariant() );
    void        setSectionValue    (const QString & section, const QString & key, const QVariant & value        = QVariant() );
    QString     text               (const QString & section, const QString & key, const QString  & value        = QString () );
    void        setText            (const QString & section, const QString & key, const QString  & value);
    void        restoreState       (QWidget  *widget);
    void        restoreState       (QMainWindow  *mw);
    void        restoreState       (QTableWidget *tw);
    void        saveState          (QWidget  *widget);
    void        saveState          (QMainWindow  *mw);
    void        saveState          (QTableWidget *tw);

signals:
    void        optionChanged      (const QString & section, const QString & key, const QVariant &);
};

}
}
#endif // __COPTIONS_H__
