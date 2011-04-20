#ifndef CDBICONSCACHE_H
#define CDBICONSCACHE_H
#include <QMap>
#include <QList>
#include <QIcon>
#include <QString>
#include "hacc_types.h"

namespace tools
{
namespace icons
{
//! Кеш иконок из БД
class CDBIconsCache : public QObject
{
    Q_OBJECT
public:
    CDBIconsCache();
    ~CDBIconsCache();
    hacc::TDBID add   (const QString &fileName);
    void remove       (const hacc::TDBID &id);
    void replace      (const hacc::TDBID &id, const QString &fileName);
    const QIcon & icon(const hacc::TDBID &id);
    void freezePredeclaredIconsCount(); //!< Заморозка количества предопределенных иконок
    const uint & predeclaredIconsCount() const;

public slots:
    void removeUnused();

private:
    QMap<hacc::TDBID, QIcon *> m_icons;
    hacc::TDBID m_maxID;
    //! Количество предопределенных иконок
    /** Предопределенные иконки нельзя удалять, их можно только заменить */
    uint        m_predeclaredIcons;
    hacc::TDBID nextID();

signals:
    void updated();
    void updated(hacc::TDBID /*iconID*/);
};

}
}
#endif // CDBICONSCACHE_H
