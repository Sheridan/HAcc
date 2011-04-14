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
class WBase : public QWidget
{
    Q_OBJECT
public:
    WBase(QWidget *parent = 0);
    virtual ~WBase();
    void buildUi();
    int contentHeight();
    WContainer *container();

protected:
    virtual void constructControls(QToolBar *tb) = 0;
    virtual WContainer *buidContainer() = 0;
    virtual void constructHeader(WHeader *header) = 0;

private:
    QVBoxLayout   *m_layout;
    WHeader       *m_header;
    WContainer    *m_container;
    QToolBar      *m_toolBar;
    int            m_height;
};

}
}
}
#endif // WBASE_H
