/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WMANUFACTURERCONTAINER_Hs
#define WMANUFACTURERCONTAINER_Hs

#include "wcontainer.h"
namespace ui
{
namespace item
{
namespace simple
{

class WSimpleManufacturerContainer : public ui::item::base::WContainer
{
    Q_OBJECT
public:
    explicit WSimpleManufacturerContainer(QWidget *parent = 0);
    ~WSimpleManufacturerContainer();
private:
    void appendManufacturer(const hacc::TDBID &manufacturerID, const hacc::TDBID &manufacturerIconID, const QString &manufacturerName);

public slots:
    void refresh(const hacc::TDBID &createdID = 0);
};

}
}
}
#endif // WMANUFACTURERCONTAINER_Hs
