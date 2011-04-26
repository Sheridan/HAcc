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

//! Отображение указателей строк грида на их id
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
    QString m_searchText;                   //!< Текст для поиска его в текстовых аолях таблиц (like ...)
    void appendItem(WItem *i);              //!< Добавление строки грида
    void removeItem(WItem *i);              //!< Удаление строки грида
    void removeItem(const hacc::TDBID &id); //!< Удаление строки грида по ее ID
    WItem *item(const hacc::TDBID &id);     //!< Возвращает строку грида

private:
    TItemsMap    m_items;        //!< Строки грида
    QVBoxLayout *m_vblContainer;

protected slots:
    void cleanItems();                               //!< Очистка грида
    virtual void itemRemoved(const hacc::TDBID &id);

public slots:
    //! Обновление грида
    /**
      @param createdID - Идентификатор новой записи. Если установлен, то только одна, новая запись добавляется в грид
    */
    virtual void refresh(const hacc::TDBID &createdID = 0) = 0;
    void setSearchText(const QString &text);                   //!< Установка текста для поиска

signals:
    void clicked(const hacc::TDBID & /*id*/);
    void doubleClicked(const hacc::TDBID & /*id*/);
};

}
}
}

//! Подвязка сигналов сущностей "создан", "удален" для отработки.
/** Макрос вставлять в конструктор потомков WContainer */
#define HACC_CONTAINER_CONNECT_CREATED_REMOVED(_bases) \
    connect(_bases, SIGNAL(created(const hacc::TDBID &)), this, SLOT(refresh(const hacc::TDBID &))); \
    connect(_bases, SIGNAL(removed(const hacc::TDBID &)), this, SLOT(itemRemoved(const hacc::TDBID &)));

#endif // WCONTAINER_H
