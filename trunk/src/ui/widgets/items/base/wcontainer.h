#ifndef WCONTAINER_H
#define WCONTAINER_H

#include "wabstractscrollarea.h"
#include "hacc_types.h"
#include <QMap>

namespace ui
{
namespace item
{
namespace base
{

class WItem;
typedef QMap<hacc::TDBID, WItem *> TItemsMap;
//! Контейнер грида.
/**
  Реализуетотображение списка элементов со скроллом.
  */
class WContainer : public ui::widget::WAbstractScrollArea
{
    Q_OBJECT
public:
    explicit WContainer(QWidget *parent = 0);
    virtual ~WContainer();
    int contentHeight();

protected:
    QString m_searchText;
    void appendItem(WItem *i);
    void removeItem(WItem *i);
    void removeItem(const hacc::TDBID &id);
    WItem *item(const hacc::TDBID &id);
//    void resizeEvent ( QResizeEvent * event );

private:
    TItemsMap    m_items;
    QVBoxLayout *m_vblContainer;

protected slots:
    void cleanItems();
    virtual void itemRemoved(const hacc::TDBID &id);

public slots:
    virtual void refresh(const hacc::TDBID &createdID = 0) = 0;
    void setSearchText(const QString &text);

signals:
    void clicked(const hacc::TDBID & /*id*/);
    void doubleClicked(const hacc::TDBID & /*id*/);
};

}
}
}

#define HACC_CONTAINER_CONNECT_CREATED_REMOVED(_bases) \
    connect(_bases, SIGNAL(created(const hacc::TDBID &)), this, SLOT(refresh(const hacc::TDBID &))); \
    connect(_bases, SIGNAL(removed(const hacc::TDBID &)), this, SLOT(refresh(const hacc::TDBID &)));

#endif // WCONTAINER_H
