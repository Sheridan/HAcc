#ifndef WMANUFACTURERCONTAINER_He
#define WMANUFACTURERCONTAINER_He

#include "wcontainer.h"

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedManufacturerContainer : public ui::item::base::WContainer
{
    Q_OBJECT
public:
    explicit WExpandedManufacturerContainer(QWidget *parent = 0);
    ~WExpandedManufacturerContainer();
private:
    void appendManufacturer(const hacc::TDBID &manufacturerID, const hacc::TDBID &manufacturerIconID, const QString &manufacturerName);

public slots:
    void refresh(const hacc::TDBID &createdID = 0);
};

}
}
}
#endif // WMANUFACTURERCONTAINER_He
