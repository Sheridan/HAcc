#include "witemdescription.h"
#include "images.h"
#include <QVariant>

namespace ui
{
namespace widget
{

WItemDescription::WItemDescription(QWidget *parent) :
    QWidget(parent)
{
    m_layout = new QHBoxLayout();
    m_text = new QLabel(this);
    m_text->setProperty("description", true);
    m_text->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_text->setWordWrap(true);
    m_text->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    m_text->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    m_layout->addWidget(m_text);
    setLayout(m_layout);
    m_image = NULL;
}

WItemDescription::~WItemDescription()
{
    delete m_image;
    delete m_text;
    delete m_layout;
}

void WItemDescription::setText(const QString &text)
{
    m_text->setText(text);
}

void WItemDescription::setImage(const QPixmap &image)
{
    if(!image.isNull())
    {
        if(!m_image)
        {
            m_image = new ui::images::WImage(128, this);
            m_layout->addWidget(m_image);
        }
        m_image->setPixmap(image, 128);
    }
    else
    {
        if(m_image)
        {
            m_layout->removeWidget(m_image);
            delete m_image;
            m_image = NULL;
        }
    }
}

void WItemDescription::clear()
{
    m_text->clear();
    if(m_image)
    {
        m_layout->removeWidget(m_image);
        delete m_image;
        m_image = NULL;
    }
}

}
}
