#include "cdbiconscache.h"
#include "images.h"
#include "st.h"
#include "hacc_options.h"

namespace tools
{
namespace icons
{

CDBIconsCache::CDBIconsCache() : QObject()
{
    m_maxID = 0;
    m_predeclaredIcons = HACC_O_PREDECLARED_ICONS;
}

CDBIconsCache::~CDBIconsCache()
{
    foreach(QIcon *icon, m_icons) { delete icon; }
    m_icons.clear();
}

hacc::TDBID CDBIconsCache::add (const QString &fileName)
{
    hacc::TDBID nID = nextID();
    QPixmap pixmap(fileName);
    HACC_DB->exec("insert into icons (id, icon) values (?,?)",
                  QVariantList()
                  << nID
                  << ui::images::pixmap2ByteArray(pixmap));
    return nID;
}

void CDBIconsCache::remove (const hacc::TDBID & id )
{
    delete m_icons.take(id);
    if(HACC_DB->exec("delete from icons where id=?", QVariantList() << id))
    {
        foreach(QString tbl, QStringList() << "accounts" << "contractors" << "manufacturers" << "things")
        {
            HACC_DB->exec(QString("update %1 set icon_id=1 where icon_id=?").arg(tbl), QVariantList() << id);
        }
        emit updated();
    }
}

void CDBIconsCache::replace(const hacc::TDBID & id, const QString &fileName)
{
    QPixmap pixmap(fileName);
    HACC_DB->exec("update icons set icon=? where id=?", QVariantList() << ui::images::pixmap2ByteArray(pixmap) << id);
    delete m_icons[id];
    m_icons[id] = new QIcon(pixmap);
    emit updated(id);
}

const QIcon & CDBIconsCache::icon( const hacc::TDBID & id )
{
    if(!m_icons.contains(id))
    {
        QSqlQuery q = HACC_DB->query("select icon from icons where id=?", QVariantList() << id);
        if(HACC_QUERY_DATA_AVIALABLE(q))
        {
            m_icons[id] = new QIcon(ui::images::byteArray2Pixmap(q.value(0).toByteArray()));
        }
        else
        {
            m_icons[id] = new QIcon(":/main/icons/item-empty.png");
        }
    }
    return *m_icons[id];
}

void CDBIconsCache::removeUnused()
{
    hacc::TIDList list = HACC_DB->listID("icons");
    hacc::TDBID iid = 0;
    foreach(QString tbl, QStringList() << "accounts" << "contractors" << "manufacturers" << "things")
    {
        QSqlQuery q = HACC_DB->query(QString("select icon_id from %0").arg(tbl));
        while(q.next())
        {
            iid = HACC_DB_2_DBID(q, 0);
            if(iid <= m_predeclaredIcons || list.contains(iid))
            {
                list.removeOne(iid);
            }
        }
    }
    foreach(iid, list)
    {
        HACC_DB->exec("delete from icons where id=?", QVariantList() << iid);
    }
    emit updated();
}

hacc::TDBID CDBIconsCache::nextID()
{
    if(!m_maxID)
    {
        m_maxID = HACC_DB->nextID("icons");
    }
    return m_maxID++;
}

void CDBIconsCache::freezePredeclaredIconsCount()
{
    m_predeclaredIcons = m_maxID;
    HACC_O_PREDECLARED_ICONS_SET(m_predeclaredIcons);
}

const uint & CDBIconsCache::predeclaredIconsCount() const
{
    return m_predeclaredIcons;
}

}
}
