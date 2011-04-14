#include "wselectorpopup.h"
#include "hacc_debug.h"
#include <QVariant>
#include <QPoint>
namespace ui
{
namespace selector
{
namespace base
{

WSelectorPopup::WSelectorPopup(QWidget *parent)
    :  ui::widget::WStyledWidget(parent, Qt::Popup),
       hacc::CIDItem()
{
    m_leSearchText = NULL;
    m_layout = NULL;
    setProperty("selector", "popup");
}

WSelectorPopup::~WSelectorPopup()
{
    delete m_leSearchText;
    delete m_layout;
}

void WSelectorPopup::buildUi()
{
    if(!m_layout)
    {
        m_layout = new QVBoxLayout();
        m_leSearchText = new QLineEdit(this);
        m_container = createContainer();
        m_container->buildUi();
        container()->refresh();
        m_layout->addWidget(m_leSearchText);
        m_layout->addWidget(m_container);
        setLayout(m_layout);
        connect(container(), SIGNAL(clicked(hacc::TDBID)), this, SLOT(close()));
        connect(m_leSearchText, SIGNAL(textChanged(QString)), container(), SLOT(setSearchText(QString)));
    }
}

ui::item::base::WContainer * WSelectorPopup::container()
{
    return m_container->container();
}

void WSelectorPopup::popup()
{
    QWidget *btt = qobject_cast<QWidget *>(parent());
    QPoint parentPos = btt->rect().bottomLeft();
    move(btt->mapToGlobal(parentPos));
    show();
}

}
}
}
