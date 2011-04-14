#include "witemlabel.h"
#include <QVariant>

namespace ui
{
namespace item
{
namespace base
{

WItemLabel::WItemLabel(QWidget *parent) : ui::widget::WStyledWidget(parent)
{
//    updateGeometry();
    m_layout = new QHBoxLayout();
    m_layout->setContentsMargins(5,0,5,0);
//    m_layout->setMargin(0);
    m_label  = new ui::widget::WControlLabel(this);
    m_layout->addWidget(m_label);
    setLayout(m_layout);
    m_icon = NULL;
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_sizeHint = m_label->size();
    setMinimumHeight(m_sizeHint.height());
    setMaximumHeight(m_sizeHint.height());
    resize(m_sizeHint);
}

WItemLabel::~WItemLabel()
{
    delete m_icon;
    delete m_label;
    delete m_layout;
}

void WItemLabel::setText(const QString &text)
{
    m_label->setText(text);
}

void WItemLabel::setIcon(const QIcon &icon)
{
    createIcon();
    m_icon->setIcon(icon);
}

void WItemLabel::setIcon(const QString &file)
{
    createIcon();
    m_icon->setIcon(file);
}

void WItemLabel::setIcon(const hacc::TDBID &id)
{
    createIcon();
    m_icon->setIcon(id);
}

void WItemLabel::createIcon()
{
    if(!m_icon)
    {
        m_icon = new ui::icons::WIcon(16, this);
        m_layout->insertWidget(0, m_icon);
    }
}

ui::widget::WControlLabel * WItemLabel::label()
{
    return m_label;
}

QSize WItemLabel::minimumSizeHint() const
{
    return m_sizeHint;
}

QSize WItemLabel::sizeHint() const
{
    return m_sizeHint;
}

}
}
}
