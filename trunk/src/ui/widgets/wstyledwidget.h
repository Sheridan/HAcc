#ifndef WSTYLEDWIDGET_H
#define WSTYLEDWIDGET_H

#include <QWidget>

namespace ui
{
namespace widget
{

//! Стилизирующийся виджет
/**
  По умолчанию у объектов унаследованных от QWidget не получится
  установить css стиль. Чтобы получилось - надо реализовать подобный интерфейс.
*/
class WStyledWidget : public QWidget
{
    Q_OBJECT
public:
    WStyledWidget(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~WStyledWidget();

private:
    void paintEvent(QPaintEvent *e);

};

}
}
#endif // WSTYLEDWIDGET_H
