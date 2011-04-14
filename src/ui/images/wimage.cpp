#include "wimage.h"
namespace ui
{
namespace images
{

WImage::WImage(QWidget *parent) : QLabel(parent)
{
    init();
}

WImage::WImage(int side, QWidget *parent) : QLabel(parent)
{
    init();
    resize(side);
}

WImage::~WImage()
{}

void WImage::init()
{
    m_empty = true;
    m_sideSize = 0;
    m_emptyText = tr("No image");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setAlignment(Qt::AlignCenter);
}

const bool & WImage::empty() const
{
    return m_empty;
}

void WImage::setEmptyText(const QString &text)
{
    m_emptyText = text;
    if(m_empty) { setText(m_emptyText); }
}

void WImage::resize(int side)
{
    if(m_sideSize != side)
    {
        resize(side,side);
    }
}

void WImage::resize(int w, int h)
{
    QLabel::resize(w, h);
//    setMinimumSize(w, h);
//    setMaximumSize(w, h);
    m_sizeHint = QSize(w,h);
    if(w == h) { m_sideSize = w; }
}

QSize WImage::sizeHint () const
{
    return m_sizeHint;
}

void WImage::clear()
{
    QLabel::clear();
    setText(m_emptyText);
    m_empty = true;
}

void WImage::setPixmap(const QPixmap &pm, int extent)
{
    resize(extent);
    QLabel::setPixmap(pm);
    m_empty = false;
}

void WImage::setPixmap(const QString &file, int extent )
{
    setPixmap(QPixmap(file), extent);
}

}
}
