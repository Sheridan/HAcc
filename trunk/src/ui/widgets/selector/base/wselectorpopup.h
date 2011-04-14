#ifndef WSELECTORPOPUP_H
#define WSELECTORPOPUP_H

#include <QVBoxLayout>
#include "wstyledwidget.h"
#include "hacc_types.h"
#include "ciditem.h"
#include <QLineEdit>
#include "wbase.h"
#include "wcontainer.h"

namespace ui
{
namespace selector
{
namespace base
{

class WSelectorPopup : public ui::widget::WStyledWidget, public hacc::CIDItem
{
    Q_OBJECT
public:
    explicit WSelectorPopup(QWidget *parent = 0);
    ~WSelectorPopup();
    ui::item::base::WContainer * container();
    void buildUi();

protected:
    virtual ui::item::base::WBase *createContainer() = 0;

private:
    QVBoxLayout           *m_layout;
    QLineEdit             *m_leSearchText;
    ui::item::base::WBase *m_container;

public slots:
    void popup();

signals:
    void selected(hacc::TDBID /*itemId*/);
};

}
}
}
#endif // WSELECTORPOPUP_H
