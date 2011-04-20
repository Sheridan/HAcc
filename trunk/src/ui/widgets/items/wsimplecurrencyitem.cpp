#include "wsimplecurrencyitem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleCurrencyItem::WSimpleCurrencyItem(const hacc::TDBID &currencyID)
    : ui::item::base::WItem(2, 1),
      hacc::model::CCurrency()
{
    setID(currencyID);
    HACC_INIT_ITEM;
}

WSimpleCurrencyItem::~WSimpleCurrencyItem()
{}

void WSimpleCurrencyItem::setCurrencyData(const hacc::TDBID &iconID, const QString &name, const QString &reduction)
{
    setIcon(0, 0, iconID);
    setText(0, 0, name);
    setText(1, 0, reduction);
}

void WSimpleCurrencyItem::assignActions()
{
    controlLabel(0, 0)->addAction(hacc::model::CCurrency::editAction());
    controlLabel(0, 0)->addAction(hacc::model::CCurrency::removeAction());
}

void WSimpleCurrencyItem:: currencyUpdated()
{

    QSqlQuery q = HACC_DB->query("select name, reduction, icon_id from currencyes where id=?", QVariantList() << itemID());
    if(q.next())
    {
        setCurrencyData(
                    HACC_DB_2_DBID(q, 2),
                    HACC_DB_2_STRG(q, 0),
                    HACC_DB_2_STRG(q, 1)
                    );
    }
}

hacc::TDBID WSimpleCurrencyItem::itemID()
{
    return hacc::model::CCurrency::id();
}

}
}
}
