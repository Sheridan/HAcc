#ifndef WLABEL_H
#define WLABEL_H

#include "wstyledwidget.h"
#include "wcontrollabel.h"
#include "wicon.h"
#include <QHBoxLayout>

namespace ui
{
namespace item
{
namespace base
{

//!< Ячейка грида
class WItemLabel : public ui::widget::WStyledWidget
{
    Q_OBJECT
public:
    WItemLabel(QWidget *parent = 0);
    ~WItemLabel();
    void setText(const QString     &text);
    void setIcon(const QIcon       &icon);
    void setIcon(const QString     &file);
    void setIcon(const hacc::TDBID &id  );
    ui::widget::WControlLabel * label();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

private:
    QHBoxLayout               *m_layout;
    ui::widget::WControlLabel *m_label;
    ui::icons::WIcon          *m_icon;
    QSize                      m_sizeHint;
    void createIcon();

};

}
}
}
#endif // WLABEL_H
