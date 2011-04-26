#ifndef WITEM_H
#define WITEM_H

#include <QTabWidget>
#include "wstyledwidget.h"
#include "wiconbutton.h"
#include "wresizer.h"
#include "citemlabels.h"
#include "ttagcontainer.h"
#include "witemdescription.h"

namespace ui
{
namespace item
{
namespace base
{

class WContainer;
class WBase;

//! Элемент грида
class WItem :
        public ui::widget::WStyledWidget,
        public CItemLabels
{
    Q_OBJECT
public:
    WItem(const int &columns, const int &rows, const bool &expandingAllowed = false);
    ~WItem();
    ui::widget::WIconButton *expandButton();
    virtual hacc::TDBID itemID() = 0;
    void setAlternateBackground(bool alternate);  //!< Установка альтернативного цвета подложки. Для полосатости.
    void setHeightDelta(int delta);               //!< Установка дельты высоты развернутой строки
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void updateGeometry();

private:
    QGridLayout             *m_layout;
    ui::widget::WIconButton *m_button;            //!< Кнопка разорачивания строки
    void mousePressEvent ( QMouseEvent * ev );
    void mouseDoubleClickEvent(QMouseEvent * ev);
    QSize m_sizeHint;
    bool  m_expandingAllowed;                     //!< Разворачивание строки разрешено?
    int   m_heightDelta;                          //!< Дельта высоты развернутой строки. @see m_resizer

    ui::widget::WResizer *m_resizer;              //!< Плашка изменения высоты развернутой строки. @see m_heightDelta

    bool m_firstOpen;                             //!< Это первое открытие?
    bool m_expanderOpen;                          //!< Строка развернута?

    void changeStyle();                           //!< Смена стиля строки при раскрытии/сворачивании
    void constructExpander();                     //!< Создание контролов в расширителе, если еще они не созданы
    bool expanderConstructed();                   //!< Созданы ли контролы расширителя?


protected:
    void initializeItem();
    virtual void assignActions();
    void resizeEvent(QResizeEvent *e);

    virtual void buildExpanderUIEvent();        //!< Для создания гуя в дочерних классах
    bool expanded();                            //!< Строка развернута?

signals:
    void clicked(const hacc::TDBID & /*id*/);
    void doubleClicked(const hacc::TDBID & /*id*/);

private slots:
    void switchExpand();                         //!< Переключатель развернутости строки


    // tabs
protected:
    void appendContainer(WBase *containerBase, const QIcon& icon, const QString &label); //!< Добавление таба-грида
    WBase *expandingContainerBase();                                                     //!< Грид из таба

    template <typename TContainerTags> void appendTagsTab();                             //!< Добавление таба-списка тегов
    void refreshTags();                                                                  //!< Обновление списка тегов

    void appendDescriptionTab();                                                         //!< Добавление таба с описанием (текст+картинка)
    void setDescription(const QString &text);                                            //!< Присваивание текста описания
    void setImage(const QPixmap &pixmap);                                                //!< Присваивание картинки описания

private:
    QTabWidget                   *m_tabs;          //!< Табвиджет, собсно
    ui::tag::base::WTagContainer *m_tags;          //!< Таб-теги
    ui::widget::WItemDescription *m_description;   //!< Таб-описание
    WBase                        *m_containerBase; //!< Таб-грид
};

//! Инициализатор. Вставлять макрос в конструктор каждого верхнего потомка WItem
#define HACC_INIT_ITEM initializeItem();

}
}
}

#include "st.h"
namespace ui
{
namespace item
{
namespace base
{

template <typename TContainerTags> void WItem::appendTagsTab()
{
    m_tags = new TContainerTags(this);
    m_tags->setItemID(itemID());
    m_tags->refresh();
    m_tabs->addTab(m_tags, HACC_ICONS->icon(tools::icons::iTag), tr("Tags"));
}

}
}
}
#endif // WITEM_H
