#ifndef WSELECTORBUTTON_H
#define WSELECTORBUTTON_H

#include "wstyledwidget.h"
#include "hacc_types.h"
#include "ciditem.h"

namespace ui
{
namespace selector
{
namespace base
{

class WSelectorPopup;
class WSelectorButton : public ui::widget::WStyledWidget, public hacc::CIDItem
{
    Q_OBJECT
public:
    explicit WSelectorButton(QWidget *parent = 0);
    ~WSelectorButton();
    void init();

public slots:
    void setID(const hacc::TDBID &id);

protected:
    virtual WSelectorPopup * constructPopup() = 0;
    virtual void idChanged() = 0;

private:
    WSelectorPopup *m_popup;
    void mousePressEvent ( QMouseEvent * ev );

signals:
    void clicked();
    void selected(const hacc::TDBID &/*id*/);

};

}
}
}
#endif // WSELECTORBUTTON_H
