#include "wsimpleenumeratedthingtypeitem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleEnumeratedThingTypeItem::WSimpleEnumeratedThingTypeItem(const hacc::TDBID &id)
    : base::WItem(2, 1),
      hacc::model::CEnumeratedThingType()
{
    setID(id);
    setIcon(0, 0, HACC_ICONS->icon(tools::icons::iEnumerated));
    HACC_INIT_ITEM;
}

WSimpleEnumeratedThingTypeItem::~WSimpleEnumeratedThingTypeItem()
{}

void WSimpleEnumeratedThingTypeItem::setItemData(const QString &enumeratedThingTypeName, const int &precision)
{
    setText(0, 0, enumeratedThingTypeName);
    setText(1, 0, QString::number(precision));
}

void WSimpleEnumeratedThingTypeItem::enumeratedThingTypeUpdated()
{
    QSqlQuery q = HACC_DB->query("select "
                                 "thing_enumerated_types.precision, "
                                 "thing_enumerated_types.name "
                                 "from thing_enumerated_types "
                                 "where thing_enumerated_types.id=?",
                                 QVariantList() << itemID());
    if(HACC_QUERY_DATA_AVIALABLE(q))
    {
        //! \todo Добавить действие, если запрос не вернет данных
        setItemData(HACC_DB_2_STRG(q, 1),
                    HACC_DB_2_PREC(q, 0));
    }
}

hacc::TDBID WSimpleEnumeratedThingTypeItem::itemID()
{
    return hacc::model::CEnumeratedThingType::id();
}

void WSimpleEnumeratedThingTypeItem::assignActions()
{
    if(!HACC_ENUMERATED_THING_TYPES->checkSpecialEnumeratedType(itemID()))
    {
        controlLabel(0, 0)->addAction(hacc::model::CEnumeratedThingType::editAction());
        controlLabel(0, 0)->addAction(hacc::model::CEnumeratedThingType::removeAction());
    }
}

}
}
}
