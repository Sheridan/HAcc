#include "wtagcontainer.h"
#include "st.h"

namespace ui
{
namespace tag
{
namespace base
{

WTagContainer::WTagContainer(QWidget *parent) : ui::widget::WAbstractScrollArea(parent)
{
    m_editMode = false;
    m_baseLayout = new ui::layout::LFlowLayout(0,0,0);
    setViewportLayout(m_baseLayout);
    connect(HACC_TAGS, SIGNAL(updated(const hacc::TDBID &)), this, SLOT(tagUpdated(const hacc::TDBID &)));
    connect(HACC_TAGS, SIGNAL(created(const hacc::TDBID &)), this, SLOT(tagCreated(const hacc::TDBID &)));
    connect(HACC_TAGS, SIGNAL(removed(const hacc::TDBID &)), this, SLOT(tagRemoved(const hacc::TDBID &)));
}

WTagContainer::~WTagContainer()
{
    clear();
}

void WTagContainer::buildUi()
{}

int WTagContainer::contentHeight()
{
    return m_baseLayout->totalHeight();
}

void WTagContainer::setEditMode(bool mode)
{
    m_editMode = mode;
}

void WTagContainer::clear()
{
    foreach(WTagLabel *tag, m_tagLabels)
    {
        m_baseLayout->removeWidget(tag);
        delete tag;
    }
    m_tagLabels.clear();
}

void WTagContainer::refresh()
{
    clear();
    hacc::TDBID id;
    hacc::model::TItemTags iTags = itemTags();
    m_tagIDList = iTags.keys();
    if(m_editMode)
    {
//        QVariantList parametres;
        QString where = "";
        QString sql = "select id, name from tags ";
        if(!m_searchText.isEmpty())
        {
            where += QString( " (upper(name) like upper(\"%%%0%%\")) ").arg(m_searchText);
        }
        if(!where.isEmpty()) { sql += " where " + where; }
        QSqlQuery q = HACC_DB->query(sql);
        while(q.next())
        {
            id = HACC_DB_2_DBID(q, 0);
            appendTag(id, HACC_DB_2_STRG(q, 1), iTags.contains(id));
        }
    }
    else
    {
        hacc::model::TItemTagsIterator it(iTags);
        while (it.hasNext())
        {
            it.next();
            appendTag(it.key(), it.value(), true);
        }
    }
}

void WTagContainer::appendTag(const hacc::TDBID &id, const QString &name, const bool &attached)
{
    WTagLabel *tag = execAppendTagLabel(id, name, attached);
    if(!m_editMode || checkSpecialPurposeTag(id))
    {
        tag->enableHandCursor(false);
    }
    if(m_editMode)
    {
        connect(tag, SIGNAL(clicked(const hacc::TDBID &)), this, SLOT(tagClicked(const hacc::TDBID &)));
    }
}

void WTagContainer::tagClicked(const hacc::TDBID &tagID)
{
    if(!checkSpecialPurposeTag(tagID))
    {
        bool contains = m_tagIDList.contains(tagID);
        if(contains)
        {
            m_tagIDList.removeOne(tagID);
        }
        else
        {
            m_tagIDList.append(tagID);
        }
        m_tagLabels[tagID]->setAttached(!contains);
    }
}

hacc::TIDList & WTagContainer::selectedTags()
{
    return m_tagIDList;
}

void WTagContainer::commit()
{
    commitEvent();
}

void WTagContainer::accept()
{
    commitEvent();
    qobject_cast<QDialog *>(parent())->accept();
}

void WTagContainer::tagCreated(const hacc::TDBID &tagID)
{
    if(m_editMode)
    {
        appendTag(tagID, HACC_TAGS->tagName(tagID), false);
    }
}

void WTagContainer::tagUpdated(const hacc::TDBID &tagID)
{
    if(m_tagLabels.contains(tagID))
    {
        m_tagLabels[tagID]->setText(HACC_TAGS->tagName(tagID));
    }
}

void WTagContainer::tagRemoved(const hacc::TDBID &tagID)
{
    execRemoveTagLabel(tagID);
}

void WTagContainer::setSearchText(QString text)
{
    m_searchText = text;
    refresh();
}

void WTagContainer::tagAttachEvent(const hacc::TDBID &tagID, const hacc::TDBID &columnID)
{
    if(!m_editMode && columnID == itemID() && !m_tagLabels.contains(tagID))
    {
        WTagLabel *tag = execAppendTagLabel(tagID, HACC_TAGS->tagName(tagID), true);
        tag->enableHandCursor(false);
    }
}

void WTagContainer::tagDetachEvent(const hacc::TDBID &tagID, const hacc::TDBID &columnID)
{
    if(!m_editMode && columnID == itemID())
    {
        execRemoveTagLabel(tagID);
    }
}

WTagLabel * WTagContainer::execAppendTagLabel(const hacc::TDBID &id, const QString &name, const bool &attached)
{
    WTagLabel *tag = new WTagLabel(id, viewport());
    tag->setText(name);
    tag->setAttached(attached);
    m_tagLabels[id] = tag;
    m_baseLayout->addWidget(tag);
    return tag;
}

void WTagContainer::execRemoveTagLabel(const hacc::TDBID &id)
{
    if(m_tagLabels.contains(id))
    {
        WTagLabel *tag = m_tagLabels[id];
        m_baseLayout->removeWidget(tag);
        delete tag;
        m_tagLabels.remove(id);
    }
}

}
}
}
