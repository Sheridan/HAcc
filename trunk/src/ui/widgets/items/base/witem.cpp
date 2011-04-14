#include "witem.h"
#include <QPixmap>
#include <QCursor>
#include <QMouseEvent>
#include <QResizeEvent>
#include "resources.h"
#include "wbase.h"
#include "st.h"
#include "hacc_debug.h"

namespace ui
{
namespace item
{
namespace base
{

WItem::WItem(const int &columns, const int &rows, const bool &expandingAllowed)
    :  ui::widget::WStyledWidget(),
      CItemLabels()
{
    m_expandingAllowed = expandingAllowed;
    m_button  = NULL;
    m_resizer = NULL;
    m_tabs    = NULL;
    m_tags    = NULL;
    m_description = NULL;
    m_containerBase = NULL;
    m_firstOpen    = true;
    m_expanderOpen = false;
    m_sizeHint     = QSize(0,0);
    m_heightDelta  = 0;

    m_layout = new QGridLayout();
    m_layout->setSizeConstraint(QLayout::SetMinimumSize);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    initialize(columns, rows, this, m_layout);
    setLayout(m_layout);
    if(m_expandingAllowed)
    {
        expandButton()->setIcon(":/main/container-open.png");
        connect(expandButton(), SIGNAL(clicked()), this, SLOT(switchExpand()));
    }
}

WItem::~WItem()
{
    delete m_resizer;
    delete m_description;
    delete m_containerBase;
    delete m_tags;
    delete m_tabs;
    delete m_layout;
    delete m_button;
}

void WItem::initializeItem()
{
    assignActions();
    updateGeometry();
}

ui::widget::WIconButton *WItem::expandButton()
{
    if(!m_button)
    {
        m_button = new ui::widget::WIconButton(this);
        m_button->move(width() - m_button->width() - 3, 3);
    }
    return m_button;
}

void WItem::resizeEvent(QResizeEvent *e)
{
    if(m_button)
    {
        m_button->move(width() - m_button->width() - 3, 3);
    }
    ui::widget::WStyledWidget::resizeEvent(e);
}

void WItem::mousePressEvent ( QMouseEvent * ev )
{
    if (ev->buttons() || Qt::LeftButton)
    {
        emit clicked(itemID());
    }
}

void WItem::mouseDoubleClickEvent(QMouseEvent * ev)
{
    if (ev->buttons() || Qt::LeftButton)
    {
        emit doubleClicked(itemID());
    }
}

void WItem::setAlternateBackground(bool alternate)
{
    setProperty("alt_bg", alternate);
}

void WItem::assignActions()
{}

void WItem::setHeightDelta(int delta)
{
    m_heightDelta = delta;
    updateGeometry();
}

void WItem::updateGeometry()
{
    int pHeight = labelsHeight()  + (expanded() ? m_heightDelta : 0);
    m_sizeHint = QSize(width(), pHeight);
    resize(m_sizeHint);
    QWidget::updateGeometry();
}

QSize WItem::minimumSizeHint() const
{
    return m_sizeHint;
}

QSize WItem::sizeHint() const
{
    return m_sizeHint;
}

void WItem::buildExpanderUIEvent()
{}

bool WItem::expanderConstructed()
{
    return !!m_tabs;
}

void WItem::constructExpander()
{
    if(!expanderConstructed())
    {
        m_tabs = new QTabWidget(this);
        m_tabs->setTabPosition(QTabWidget::South);
        buildExpanderUIEvent();
        m_resizer = new ui::widget::WResizer(this);
        m_layout->addWidget(m_tabs   , m_layout->rowCount(), 0, 1, -1);
        m_layout->addWidget(m_resizer, m_layout->rowCount(), 0, 1, -1);
        updateGeometry();
    }
}

void WItem::switchExpand()
{
    if(!m_expanderOpen)
    {
        constructExpander();
        expandButton()->setIcon(":/main/container-close.png");
    }
    else
    {
        expandButton()->setIcon(":/main/container-open.png");
    }
    m_expanderOpen = !m_expanderOpen;
    m_resizer->setVisible(m_expanderOpen);
    m_tabs->setVisible(m_expanderOpen);
    changeStyle();
    updateGeometry();
}

void WItem::changeStyle()
{
    setProperty("more_ui", m_expanderOpen);
    setStyleSheet(tools::resources::readTextResource(":/qss/item.qss"));
}

bool WItem::expanded()
{
    return m_expanderOpen;
}

void WItem::appendContainer(WBase *containerBase, const QIcon& icon, const QString &label)
{
    m_containerBase = containerBase;
    m_containerBase->buildUi();
    m_containerBase->container()->refresh();
    m_tabs->addTab(m_containerBase, icon, label);
}

WBase *WItem::expandingContainerBase()
{
    return m_containerBase;
}

void WItem::refreshTags()
{
    if(expanderConstructed() && m_tags)
    {
        m_tags->refresh();
    }
}

void WItem::appendDescriptionTab()
{
    m_description = new ui::widget::WItemDescription(this);
    m_tabs->addTab(m_description, HACC_ICONS->icon(tools::icons::iDescription), tr("Description"));
}

void WItem::setDescription(const QString &text)
{
    if(expanderConstructed() && m_description)
    {
        m_description->setText(text);
    }
}

void WItem::setImage(const QPixmap &pixmap)
{
    if(expanderConstructed() && m_description)
    {
        m_description->setImage(pixmap);
    }
}

}
}
}

//9283402710 Женя еремеев
