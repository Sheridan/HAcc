#ifndef WICONITEM_H
#define WICONITEM_H

#include "wiconbuttonbase.h"
#include <QMenu>

namespace ui
{
namespace icons
{

class WIconItem : public WIconButtonBase
{
    Q_OBJECT
public:
    explicit WIconItem(const hacc::TDBID &iconId, QWidget *parent = 0);
    virtual ~WIconItem();

private:
    QMenu   *m_menu;

signals:
    void selected(hacc::TDBID /*iconId*/);

private slots:
    void emitSelected();
    void remove();
    void edit();

};

}
}
#endif // WICONITEM_H
