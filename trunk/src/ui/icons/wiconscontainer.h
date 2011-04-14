#ifndef WICONSCONTAINER_H
#define WICONSCONTAINER_H

#include "wabstractscrollarea.h"
#include "lflowlayout.h"
#include "hacc_types.h"
#include <QList>

namespace ui
{
namespace icons
{

class WIconItem;
class WIconsContainer : public ui::widget::WAbstractScrollArea
{
    Q_OBJECT
public:
    explicit WIconsContainer(QWidget *parent = 0);
    virtual ~WIconsContainer();

private:
    ui::layout::LFlowLayout *m_baseLayout;
    void buildUi();
    int contentHeight();
    void clear();
    QList<WIconItem *> m_icons;

public slots:
    void refresh();

signals:
    void selected(hacc::TDBID /*iconId*/);
};

}
}
#endif // WICONSCONTAINER_H
