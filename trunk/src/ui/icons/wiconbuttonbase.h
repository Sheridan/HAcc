/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WICONBUTTONBASE_H
#define WICONBUTTONBASE_H

#include <QToolButton>
#include "ciditem.h"

namespace ui
{
namespace icons
{

//! База для кнопки-иконки
class WIconButtonBase : public QToolButton, public hacc::CIDItem
{
    Q_OBJECT
public:
    WIconButtonBase(const hacc::TDBID &iconID, QWidget *parent = 0);
    ~WIconButtonBase();
    void setID(const hacc::TDBID & id);
};

}
}

#endif // WICONBUTTONBASE_H
