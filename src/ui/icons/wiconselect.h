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
    explicit WIconSelect(const hacc::TDBID &iconId, QWidget *parent = 0);
    explicit WIconSelect(QWidget *parent = 0);
    virtual ~WIconSelect();

private slots:
    void select();

};

}
}

#endif // WICONSELECT_H
