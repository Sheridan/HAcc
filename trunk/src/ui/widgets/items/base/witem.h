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
class WItem : public ui::widget::WStyledWidget, public CItemLabels
{
    Q_OBJECT
public:
    explicit WItem(const int &columns, const int &rows, const bool &expandingAllowed = false);
    ~WItem();
    ui::widget::WIconButton *expandButton();
    virtual hacc::TDBID itemID() = 0;
    void setAlternateBackground(bool alternate);
    void setHeightDelta(int delta);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void updateGeometry();

private:
    QGridLayout *m_layout;
    ui::widget::WIconButton *m_button;
    void mousePressEvent ( QMouseEvent * ev );
    void mouseDoubleClickEvent(QMouseEvent * ev);
    QSize m_sizeHint;
    bool m_expandingAllowed;
    int m_heightDelta;

    ui::widget::WResizer *m_resizer;

    bool m_firstOpen;
    bool m_expanderOpen;

    void changeStyle();
    void constructExpander();
    bool expanderConstructed();


protected:
    void initializeItem();
    virtual void assignActions();
    void resizeEvent(QResizeEvent *e);

    virtual void buildExpanderUIEvent();        // дети наследуют и при вызове создают гуй
    bool expanded();

signals:
    void clicked(const hacc::TDBID & /*id*/);
    void doubleClicked(const hacc::TDBID & /*id*/);

private slots:
    void switchExpand();


    // tabs
protected:
    void appendContainer(WBase *containerBase, const QIcon& icon, const QString &label);
    WBase *expandingContainerBase();

    template <typename TContainerTags> void appendTagsTab();
    void refreshTags();

    void appendDescriptionTab();
    void setDescription(const QString &text);
    void setImage(const QPixmap &pixmap);

private:
    QTabWidget                   *m_tabs;
    ui::tag::base::WTagContainer *m_tags;
    ui::widget::WItemDescription *m_description;
    WBase                        *m_containerBase;



};

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
