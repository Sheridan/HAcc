#include "wbase.h"
#include "wcontainer.h"
#include <QVBoxLayout>
#include <QAction>
#include "st.h"

namespace ui
{
namespace item
{
namespace base
{

WBase::WBase(QWidget *parent) : QWidget(parent)
{
    m_toolBar = NULL;
    m_container = NULL;
    m_layout = NULL;
    m_header = NULL;
    m_height = 0;
}

WBase::~WBase()
{
    delete m_toolBar;
    delete m_container;
    delete m_header;
    delete m_layout;
}

void WBase::buildUi()
{
    m_container = buidContainer();

    m_layout = new QVBoxLayout();

    m_toolBar = new QToolBar("", this);
    m_toolBar->setMovable(false);
    m_toolBar->setFloatable(false);
    m_toolBar->setOrientation(Qt::Horizontal);

    QAction *ar = new QAction(QIcon(":/main/view-refresh.png"), tr("Refresh"), this);
    ar->setEnabled(HACC_DB->isOpen());
    connect(ar, SIGNAL(triggered()), m_container, SLOT(refresh()));
    connect(HACC_DB, SIGNAL(stateChange(bool)), ar, SLOT(setEnabled(bool)));

    m_toolBar->addAction(ar);
    m_toolBar->addSeparator();
    constructControls(m_toolBar);
    m_toolBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    m_header = new WHeader(this);
    constructHeader(m_header);
    m_header->updateGeometry();

    m_layout->addWidget(m_toolBar);
    m_layout->addWidget(m_header);
    m_layout->addWidget(m_container);

    m_height = m_toolBar->height() + m_header->height() + 90; // Hardcore 3-4 items height

    setLayout(m_layout);
}

int WBase::contentHeight()
{
    return m_height;
}

WContainer *WBase::container()
{
    return m_container;
}

}
}
}
