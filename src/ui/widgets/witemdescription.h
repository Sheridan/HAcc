#ifndef WITEMDESCRIPTION_H
#define WITEMDESCRIPTION_H

#include <QWidget>
#include "wimage.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>

namespace ui
{
namespace widget
{

class WItemDescription : public QWidget
{
    Q_OBJECT
public:
    WItemDescription(QWidget *parent = 0);
    ~WItemDescription();
    void setText(const QString &text);
    void setImage(const QPixmap &image);
    void clear();

private:
    QLabel             *m_text;
    ui::images::WImage *m_image;
    QHBoxLayout        *m_layout;

};

}
}
#endif // WITEMDESCRIPTION_H
