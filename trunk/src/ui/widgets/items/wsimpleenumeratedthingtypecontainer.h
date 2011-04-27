/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WENUMERATEDTHINGTYPECONTAINER_Hs
#define WENUMERATEDTHINGTYPECONTAINER_Hs

#include "wcontainer.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleEnumeratedThingTypeContainer : public ui::item::base::WContainer
{
    Q_OBJECT
public:
    explicit WSimpleEnumeratedThingTypeContainer(QWidget *parent = 0);
    ~WSimpleEnumeratedThingTypeContainer();

private:
    void appendThingEnumerateType(const hacc::TDBID &enumeratedThingTypeID, const QString &enumeratedThingTypeName, const int &precision);

public slots:
    void refresh(const hacc::TDBID &createdID = 0);
};

}
}
}
#endif // WENUMERATEDTHINGTYPECONTAINER_Hs
