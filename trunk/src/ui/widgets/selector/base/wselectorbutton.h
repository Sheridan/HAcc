/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
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
//! Кнопка-селектор, база
/**
  Логика такая: Есть кнопка WSelectorButton, при нажатии на нее всплывает WSelectorPopup с гридом для выбора.
  При клике на грид меню закрывается и на кнопке отображается то что выбрали.
*/
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
    virtual void idChanged() = 0; //!< Сменен идентификатор, надо обновить данные на кнопке

private:
    WSelectorPopup *m_popup; //!< Всплывающее меню
    void mousePressEvent ( QMouseEvent * ev );

signals:
    void clicked();
    void selected(const hacc::TDBID &/*id*/);

};

}
}
}
#endif // WSELECTORBUTTON_H
