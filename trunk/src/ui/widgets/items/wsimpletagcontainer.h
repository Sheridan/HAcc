/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WTAGCONTAINER_Hs
#define WTAGCONTAINER_Hs
#include "wcontainer.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleTagContainer : public ui::item::base::WContainer
{
    Q_OBJECT
public:
    WSimpleTagContainer(QWidget *parent = 0);
    ~WSimpleTagContainer();

private:
    void appendTag(const hacc::TDBID &id, const QString &name);

public slots:
    void refresh(const hacc::TDBID &id = 0);
};

}
}
}
#endif // WTAGCONTAINER_Hs
