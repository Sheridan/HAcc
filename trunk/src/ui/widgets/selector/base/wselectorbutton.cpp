#include "wselectorbutton.h"
#include "wselectorpopup.h"
#include <QVariant>
#include <QMouseEvent>
#include "hacc_debug.h"

namespace ui
{
namespace selector
{
namespace base
{

WSelectorButton::WSelectorButton(QWidget *parent) : ui::widget::WStyledWidget(parent), hacc::CIDItem()
{
    setFocusPolicy(Qt::StrongFocus);
    setProperty("selector", "button");

    m_popup = NULL;
}

WSelectorButton::~WSelectorButton()
{
    delete m_popup;
}

void WSelectorButton::init()
{
    delete m_popup;
    m_popup = constructPopup();
    m_popup->buildUi();
    connect(this, SIGNAL(clicked()), m_popup, SLOT(popup()));
    connect(m_popup->container(), SIGNAL(clicked(const hacc::TDBID &)), this, SLOT(setID(const hacc::TDBID &)));
    connect(m_popup->container(), SIGNAL(clicked(const hacc::TDBID &)), this, SIGNAL(selected(const hacc::TDBID &)));
}

void WSelectorButton::setID(const hacc::TDBID &id)
{
    hacc::CIDItem::setID(id);
    idChanged();
}

void WSelectorButton::mousePressEvent ( QMouseEvent * ev )
{
    if (ev->buttons() || Qt::LeftButton)
    {
        emit clicked();
    }
}

}
}
}
