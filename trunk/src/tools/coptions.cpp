#include "coptions.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QHeaderView>
#include "doptions.h"
#include "hacc_options.h"
#include "st.h"

namespace tools
{
namespace options
{

COptions::COptions() : QSettings()
{}

COptions::~COptions()
{
    sync();
}

QVariant COptions::sectionValue ( const QString & section, const QString & key, const QVariant & defaultValue )
{
    beginGroup ( section );
    QVariant result = value ( key, defaultValue );
    endGroup();
    return result;
}

void COptions::setSectionValue ( const QString & section, const QString & key, const QVariant & value )
{
    beginGroup ( section );
    setValue ( key, value );
    endGroup();
    sync();
    emit optionChanged(section, key, value);
}

QString COptions::text(const QString & section, const QString & key, const QString & value)
{
    return QString(QByteArray::fromBase64(sectionValue(section, key, QString(value.toUtf8().toBase64())).toString().toUtf8()));
}

void COptions::setText(const QString & section, const QString & key, const QString & value)
{
    setSectionValue(section, key, value.toUtf8().toBase64());
}

void COptions::restoreState(QWidget *widget)
{
    beginGroup ( "Widgets" );
    widget->resize(value(QString("%1_size").arg(widget->objectName()), widget->size()).toSize());
    widget->move(value(QString("%1_position").arg(widget->objectName()),
                       QPoint(
                               (QApplication::desktop ()->width()/2)-(widget->size().width()/2),
                               (QApplication::desktop ()->height()/2)-(widget->size().height()/2)
                               )
                       ).toPoint());
    widget->restoreGeometry(value(QString("%1_size").arg(widget->objectName()), QByteArray()).toByteArray());
    endGroup();
}

void COptions::saveState(QWidget *widget)
{
    beginGroup ( "Widgets" );
    setValue(QString("%1_size").arg(widget->objectName()), widget->size());
    setValue(QString("%1_position").arg(widget->objectName()), widget->pos());
    setValue(QString("%1_geometry").arg(widget->objectName()), widget->saveGeometry());
    endGroup();
}

void COptions::restoreState(QMainWindow *mw)
{
    restoreState(static_cast<QWidget *>(mw));
    beginGroup ( "Windows" );
    mw->restoreState(value(QString("%1_state").arg(mw->objectName()), QByteArray()).toByteArray());
    endGroup();
}

void COptions::saveState(QMainWindow *mw)
{
    beginGroup ( "Windows" );
    setValue(QString("%1_state").arg(mw->objectName()), mw->saveState());
    endGroup();
    saveState(static_cast<QWidget *>(mw));
}

void COptions::restoreState(QTableWidget *tw)
{
    restoreState(static_cast<QWidget *>(tw));
    beginGroup ( "Tables" );
    tw->horizontalHeader()->restoreState(value(QString("%1_%2_hh_state").arg(tw->parent()->objectName()).arg(tw->objectName()), QByteArray()).toByteArray());
    tw->verticalHeader()->restoreState(value(QString("%1_%2_vh_state").arg(tw->parent()->objectName()).arg(tw->objectName()), QByteArray()).toByteArray());
    endGroup();
}

void COptions::saveState(QTableWidget *tw)
{
    beginGroup ( "Tables" );
    setValue(QString("%1_%2_hh_state").arg(tw->parent()->objectName()).arg(tw->objectName()), tw->horizontalHeader()->saveState());
    setValue(QString("%1_%2_vh_state").arg(tw->parent()->objectName()).arg(tw->objectName()), tw->verticalHeader()->saveState());
    endGroup();
    saveState(static_cast<QWidget *>(tw));
}

QStringList COptions::sectionKeys(const QString & section)
{
    beginGroup ( section );
    QStringList keys = childKeys();
    endGroup();
    return keys;
}

void COptions::removeSectionValue(const QString &section, const QString & key)
{
    beginGroup ( section );
    remove ( key );
    endGroup();
}


void COptions::removeSection(const QString & section)
{
    beginGroup ( section );
    foreach(QString key, childKeys()) { remove ( key ); }
    endGroup();
}

void COptions::checkFirstStart()
{
    if(HACC_O_DEFAULT_CURRENCY == 0)
    {
        ui::form::DOptions dialog;
        dialog.exec();
    }
}

void COptions::setDBValue(const QString & key, const QVariant & value)
{
    QSqlQuery q = HACC_DB->query("select value from db_options where name=?", QVariantList() << key);
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        HACC_DB->exec("update db_options set value=? where name=?", QVariantList() << value << key);
    }
    else
    {
        HACC_DB->exec("insert into db_options (name, value) values (?,?)", QVariantList() << key << value);
    }
}

QVariant COptions::dbValue(const QString & key, const QVariant & defaultValue)
{
    QSqlQuery q = HACC_DB->query("select value from db_options where name=?", QVariantList() << key);
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        return q.value(0);
    }
    return defaultValue;
}

void COptions::removeDBValue(const QString & key)
{
    HACC_DB->exec("delete from db_options where name=?", QVariantList() << key);
}

}
}
