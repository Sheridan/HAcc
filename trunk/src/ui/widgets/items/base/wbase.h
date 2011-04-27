/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WBASE_H
#define WBASE_H

#include <QWidget>
#include <QToolBar>
#include <QVBoxLayout>
#include "wheader.h"

namespace ui
{
namespace item
{
namespace base
{

class WContainer;
//! Подложка под грид
/**
  Реализует заголовок грида, а также тулбар для грида
*/
class WBase : public QWidget
{
    Q_OBJECT
public:
    WBase(QWidget *parent = 0);
    virtual ~WBase();
    void buildUi();
    int contentHeight();     //!< Высота содержимого подложки
    WContainer *container(); //!< Собственно, грид

protected:
    virtual void constructControls(QToolBar *tb) = 0; //!< Для создания элементов тулбара
    virtual WContainer *buidContainer() = 0;          //!< Должна вернуть контейнер грида
    virtual void constructHeader(WHeader *header) = 0;//!< Для создания заголовка грида

private:
    QVBoxLayout   *m_layout;
    WHeader       *m_header;    //!< Заголовок грида
    WContainer    *m_container; //!< Собственно, грид
    QToolBar      *m_toolBar;   //!< Панелька с кнопкаме и всякиме фильтраме
    int            m_height;    //!< Высота содержимого подложки
};

}
}
}
#endif // WBASE_H
