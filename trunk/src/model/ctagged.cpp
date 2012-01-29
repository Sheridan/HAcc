#include "ctagged.h"
#include "hacc_debug.h"
#include "st.h"

namespace hacc
{
namespace model
{

CTagged::CTagged(const QString &table, const QString &column) : m_table(table), m_column(column)
{
    m_selectSelfTagsQuery = QString("select "
                                    "tags.id, "
                                    "tags.name "
                                    "from %0 "
                                    "left join tags on tags.id=%0.tag_id "
                                    "where %0.%1=?").arg(m_table).arg(m_column);
    m_purposeTagsIDString = "";
}

CTagged::~CTagged()
{
    m_tagsMap.clear();
}

TItemTags & CTagged::tags(const hacc::TDBID &columnID)
{
//    HACC_DEBUG("Tags request. Table: " << m_table << "; Column: " << m_column << "; id: " << columnID);
    if(!m_tagsMap.contains(columnID))
    {
        TItemTags & column_tags = m_tagsMap[columnID];
        QSqlQuery q = HACC_DB->query(m_selectSelfTagsQuery, QVariantList() << columnID);
        while(q.next())
        {
            column_tags[HACC_DB_2_DBID(q, 0)] = HACC_DB_2_STRG(q, 1);
        }
//        HACC_DEBUG("Tags scan. Table: " << m_table << "; Column: " << m_column << "; id: " << columnID);
    }
    return m_tagsMap[columnID];
}

void CTagged::attachTag(const hacc::TDBID &tagID, const hacc::TDBID &columnID, const bool &attach)
{
    if(attach)
    {
        attachTag(tagID, columnID);
    }
    else
    {
        detachTag(tagID, columnID);
    }

}

QString CTagged::whereTagsInPurposeTags()
{
    if (!hasPurposeTags()) { return ""; }
    if(m_purposeTagsIDString.isEmpty())
    {
        m_purposeTagsIDString = QString("%0.tag_id in (%1)").arg(m_table).arg(purposeTagsIDString());
    }
    return m_purposeTagsIDString;
}

void CTagged::attachTag(const hacc::TDBID &tagID, const hacc::TDBID &columnID)
{
    if(!tagAttached(tagID, columnID))
    {
        HACC_DB->exec(QString("insert into %0 (tag_id,%1) values (?,?)").arg(m_table).arg(m_column),
                      QVariantList() << tagID << columnID);
        tags(columnID)[tagID] = HACC_TAGS->tagName(tagID);
        tagAttachEvent(tagID, columnID);
    }
}

void CTagged::detachTag(const hacc::TDBID &tagID, const hacc::TDBID &columnID)
{
    if(tagAttached(tagID, columnID))
    {
        HACC_DB->exec(QString("delete from %0 where tag_id =? and %1=?").arg(m_table).arg(m_column),
                      QVariantList() << tagID << columnID);
        tags(columnID).remove(tagID);
        tagDetachEvent(tagID, columnID);
    }
}

void CTagged::detachTags(const hacc::TDBID &columnID)
{
    HACC_DB->exec(QString("delete from %0 where %1=?").arg(m_table).arg(m_column),
                  QVariantList() << columnID);
    tags(columnID).clear();
    m_tagsMap.remove(columnID);
}

bool CTagged::retachTag(const hacc::TDBID &tagID, const hacc::TDBID &columnID)
{
    bool attached = tags(columnID).contains(tagID);
    if(attached) { detachTag(tagID, columnID); }
    else         { attachTag(tagID, columnID); }
    return !attached;
}

void CTagged::setTags(const hacc::TIDList &newTags, const hacc::TDBID &columnID)
{
    hacc::TIDList currentTags = tags(columnID).keys();
    foreach(hacc::TDBID id, currentTags)
    {
        if(!newTags.contains(id))
        {
            detachTag(id, columnID);
        }
    }
    foreach(hacc::TDBID id, newTags)
    {
        if(!currentTags.contains(id))
        {
            attachTag(id, columnID);
        }
    }
}

bool CTagged::tagAttached(const hacc::TDBID   &tagID  , const hacc::TDBID &columnID)
{
    return tags(columnID).contains(tagID);
}

void CTagged::tagAttachEvent(const hacc::TDBID &tagID, const hacc::TDBID &columnID) { Q_UNUSED(tagID); Q_UNUSED(columnID); }
void CTagged::tagDetachEvent(const hacc::TDBID &tagID, const hacc::TDBID &columnID) { Q_UNUSED(tagID); Q_UNUSED(columnID); }

const QString &CTagged::tagTable  () const { return m_table ; }
const QString &CTagged::itemColumn() const { return m_column; }
const QString &CTagged::selectSelfTagsQuery() const { return m_selectSelfTagsQuery; }

}
}
