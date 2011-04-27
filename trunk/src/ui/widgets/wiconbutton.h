/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WICONBUTTON_H
#define WICONBUTTON_H

#include "wicon.h"

namespace ui
{
namespace widget
{

//! Кнопка - иконка
class WIconButton :
        public ui::icons::WIcon
{
    Q_OBJECT
public:
    WIconButton(const QString &iconPath, QWidget *parent = 0);
    WIconButton(const QIcon &icon, QWidget *parent = 0);
    WIconButton(QWidget *parent = 0);
    ~WIconButton();

private:
    void mousePressEvent ( QMouseEvent * ev );
    void init();

signals:
    void clicked();
};

}
}
#endif // WICONBUTTON_H
