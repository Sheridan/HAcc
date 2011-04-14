#ifndef WTAGLABEL_H
#define WTAGLABEL_H

#include "wlabelbutton.h"
#include "ciditem.h"

namespace ui
{
namespace tag
{
namespace base
{

class WTagLabel : public ui::widget::WLabelButton, public hacc::CIDItem
{
    Q_OBJECT
public:
    explicit WTagLabel(const hacc::TDBID &tagID, QWidget *parent = 0);
    ~WTagLabel();
    void setAttached(bool attached);

private:
    void mouseClickEvent();

signals:
    void clicked(const hacc::TDBID &/*tagID*/);
};

}
}
}
#endif // WTAGLABEL_H
