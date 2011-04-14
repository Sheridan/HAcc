#ifndef WENUMERATEDTHINGTYPEITEM_Hs
#define WENUMERATEDTHINGTYPEITEM_Hs

#include "witem.h"
#include "cenumeratedthingtype.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleEnumeratedThingTypeItem : public base::WItem, public hacc::model::CEnumeratedThingType
{
public:
    explicit WSimpleEnumeratedThingTypeItem(const hacc::TDBID &id);
    ~WSimpleEnumeratedThingTypeItem();
    void setItemData(const QString &eTTypeName, const int &precision);
    hacc::TDBID itemID();
private:
    void enumeratedThingTypeUpdated();
    void assignActions();

};

}
}
}
#endif // WENUMERATEDTHINGTYPEITEM_Hs
