/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WICONITEM_H
#define WICONITEM_H

#include "wiconbuttonbase.h"
#include <QMenu>

namespace ui
{
namespace icons
{

//! Кнопка-иконка с меню для удаления\редактирования иконки
class WIconItem : public WIconButtonBase
{
    Q_OBJECT
public:
    WIconItem(const hacc::TDBID &iconID, QWidget *parent = 0);
    virtual ~WIconItem();

private:
    QMenu   *m_menu;

signals:
    void selected(hacc::TDBID /*iconID*/);

private slots:
    void emitSelected();
    void remove();
    void edit();

};

}
}
#endif // WICONITEM_H
