#include "wsimplecurrencyitem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleCurrencyItem::WSimpleCurrencyItem(const hacc::TDBID &currencyID)
    : ui::item::base::WItem(1, 1),
      hacc::model::CCurrency()
{
    setID(currencyID);
    setIcon(0, 0, HACC_ICONS->icon(tools::icons::iCurrency));
    HACC_INIT_ITEM;
}

WSimpleCurrencyItem::~WSimpleCurrencyItem()
{}

void WSimpleCurrencyItem::setCurrencyData(const QString &name, const QString &reduction)
{
    setText(0, 0, QString("%0 (%1)").arg(name).arg(reduction));
}

void WSimpleCurrencyItem::assignActions()
{
    controlLabel(0, 0)->addAction(hacc::model::CCurrency::editAction());
    controlLabel(0, 0)->addAction(hacc::model::CCurrency::removeAction());
}

void WSimpleCurrencyItem:: currencyUpdated()
{

    QSqlQuery q = HACC_DB->query("select name, reduction from currencyes where id=?", QVariantList() << itemID());
    if(q.next())
    {
        setCurrencyData(
                    HACC_DB_2_STRG(q, 1),
                    HACC_DB_2_STRG(q, 2)
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
