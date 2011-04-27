/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef TMDICHILD_H
#define TMDICHILD_H
#include "fmdichild.h"

// ----------------------------------------------------- h ---------------------------------------------------
namespace ui
{
namespace form
{

//! Универсальный диалог MDI окон сущностей
template <typename TContainerBase>class TMDIChild : public FMDIChild
{
public:
    explicit TMDIChild(const QString &title, const QIcon &icon, QWidget *parent = 0);

private:
    ui::item::base::WBase *constructContainerBase();

};

}
}
// ----------------------------------------------------- cpp ---------------------------------------------------
namespace ui
{
namespace form
{

template <typename TContainerBase>TMDIChild<TContainerBase>::TMDIChild(const QString &title, const QIcon &icon, QWidget *parent)
    : FMDIChild(title, icon, parent)
{}

template <typename TContainerBase> ui::item::base::WBase *TMDIChild<TContainerBase>::constructContainerBase()
{
    return new TContainerBase(this);
}

}
}
#endif // TMDICHILD_H
