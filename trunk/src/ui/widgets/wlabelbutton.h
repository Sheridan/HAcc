#ifndef QLABELBUTTON_H
#define QLABELBUTTON_H

#include "wicon.h"

namespace ui
{
namespace widget
{

//! Метка-кнопка
class WLabelButton : public QLabel
{
    Q_OBJECT
public:
    explicit WLabelButton(QWidget *parent = 0);
    void enableHandCursor(bool enable);

private:
    void mousePressEvent ( QMouseEvent * ev );

protected:
    virtual void mouseClickEvent() {};

signals:
    void clicked();

};

}
}
#endif // QLABELBUTTON_H
