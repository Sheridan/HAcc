#ifndef WCONTROLLABEL_H
#define WCONTROLLABEL_H

#include "wstyledwidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include "wiconbutton.h"
#include <QList>

namespace ui
{
namespace widget
{

class WControlLabel : public QLabel
{
    Q_OBJECT
public:
    explicit WControlLabel(QWidget *parent = 0);
    ~WControlLabel();
    void setButtonsVisible(bool visible);
    void addAction(QAction *action);

private:
    QList< ui::widget::WIconButton *> m_wicons;
    void enterEvent ( QEvent * event );
    void leaveEvent( QEvent * event );
    void resizeEvent ( QResizeEvent * event );
    void fixButtonsPosition();
};

}
}
#endif // WCONTROLLABEL_H
