#ifndef TDWCONTAINERBASE_H
#define TDWCONTAINERBASE_H
//----------------------------------------------------------- h ----------------------------------------------
#include "dwcontainerbase.h"

namespace ui
{
//! Доклеты
namespace dock
{

template <typename TContainerBase>class TDWContainerBase : public DWContainerBase
{
public:
    explicit TDWContainerBase(const QString &title, const QIcon &icon, QWidget *parent = 0);

private:
    ui::item::base::WBase *constructContainerBase();

};

}
}
//----------------------------------------------------------- cpp ----------------------------------------------
namespace ui
{
namespace dock
{

template <typename TContainerBase>TDWContainerBase<TContainerBase>::TDWContainerBase(const QString &title, const QIcon &icon, QWidget *parent)
    : DWContainerBase(title, icon, parent)
{}

template <typename TContainerBase> ui::item::base::WBase *TDWContainerBase<TContainerBase>::constructContainerBase()
{
    return new TContainerBase(this);
}

}
}
#endif // TDWCONTAINERBASE_H
