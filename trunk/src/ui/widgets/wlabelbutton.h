/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef QLABELBUTTON_H
#define QLABELBUTTON_H

#include "wicon.h"

namespace ui
{
namespace widget
{

//! Метка-кнопка
/**
  Отсылает сигнал и вызывает виртфункцию при клике на себе.
*/
class WLabelButton : public QLabel
{
    Q_OBJECT
public:
    explicit WLabelButton(QWidget *parent = 0);
    void enableHandCursor(bool enable); //!< Указатель-рука вместо обычной стрелки

private:
    void mousePressEvent ( QMouseEvent * ev );

protected:
    virtual void mouseClickEvent() {}

signals:
    void clicked();

};

}
}
#endif // QLABELBUTTON_H
