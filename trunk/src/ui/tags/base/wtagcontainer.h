#ifndef WTAGCONTAINER_H
#define WTAGCONTAINER_H

#include "wabstractscrollarea.h"
#include "wtaglabel.h"
#include "lflowlayout.h"
#include "ctagged.h"
#include <QPushButton>
#include <QMap>

namespace ui
{
//! Отображение/редактирование тегов
namespace tag
{
//! Базовые классы для отображения/редактирования тегов
namespace base
{

//! Контейнер для тегов
class WTagContainer : public ui::widget::WAbstractScrollArea
{
    Q_OBJECT
public:
    explicit WTagContainer(QWidget *parent = 0);
    virtual ~WTagContainer();
    int contentHeight();
    void setEditMode(bool mode);
    hacc::TIDList & selectedTags();
    virtual void setItemID(const hacc::TDBID &itemID) = 0;

private:
    ui::layout::LFlowLayout *m_baseLayout;
    hacc::TIDList            m_tagIDList;
    QString                  m_searchText;
    bool                     m_editMode;
    void buildUi();
    void clear();
    QMap<hacc::TDBID, WTagLabel *> m_tagLabels;
    void appendTag(const hacc::TDBID &id, const QString &name, const bool &attached);
    WTagLabel * execAppendTagLabel(const hacc::TDBID &id, const QString &name, const bool &attached);
    void execRemoveTagLabel(const hacc::TDBID &id);


protected:
    virtual hacc::TDBID itemID() = 0;
    virtual hacc::model::TItemTags & itemTags() = 0;
    virtual void commitEvent() = 0;
    virtual bool checkSpetialPurposeTag(const hacc::TDBID &tagID) = 0;
    void tagAttachEvent(const hacc::TDBID &tagID, const hacc::TDBID &columnID);
    void tagDetachEvent(const hacc::TDBID &tagID, const hacc::TDBID &columnID);

public slots:
    void refresh();
    void commit();
    void accept();
    void setSearchText(QString text);

signals:
    void selected(const hacc::TDBID &/*iconID*/);

private slots:
    void tagClicked(const hacc::TDBID &tagID);
    void tagCreated(const hacc::TDBID &tagID);
    void tagUpdated(const hacc::TDBID &tagID);
    void tagRemoved(const hacc::TDBID &tagID);
};

}
}
}
#endif // WTAGCONTAINER_H
