/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WICONSELECT_H
#define WICONSELECT_H

#include "wiconbuttonbase.h"
//! Интерфейс
namespace ui
{
//! Управление иконками
namespace icons
{

class WIconSelect : public WIconButtonBase
{
    Q_OBJECT
public:
    WIconSelect(const hacc::TDBID &iconID, QWidget *parent = 0);
    WIconSelect(QWidget *parent = 0);
    virtual ~WIconSelect();

private slots:
    void select();

};

}
}

#endif // WICONSELECT_H
