/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef DWCONTAINERBASE_H
#define DWCONTAINERBASE_H

#include <QDockWidget>
#include "wbase.h"

//! Сгенерирован creator'ом
namespace Ui { class DWContainerBase; }
namespace ui
{
namespace dock
{

//! Базовый класс доков
/**

*/
class DWContainerBase : public QDockWidget
{
    Q_OBJECT

public:
    explicit DWContainerBase(const QString &title, const QIcon &icon, QWidget *parent = 0);
    ~DWContainerBase();
    void init();

protected:
//    void changeEvent(QEvent *e);
    virtual ui::item::base::WBase *constructContainerBase() = 0;

private:
    ui::item::base::WBase *m_containerBase;
    Ui::DWContainerBase *ui;
};

}
}
#endif // DWCONTAINERBASE_H
