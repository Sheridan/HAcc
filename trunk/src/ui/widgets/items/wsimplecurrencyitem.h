#ifndef WSIMPLECURRENCYITEM_H
#define WSIMPLECURRENCYITEM_H

#include "witem.h"
#include "ccurrency.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleCurrencyItem :
        public ui::item::base::WItem,
        public hacc::model::CCurrency
{
public:
    WSimpleCurrencyItem(const hacc::TDBID &currencyID);
    ~WSimpleCurrencyItem();
    void setCurrencyData(const QString &name, const QString &reduction);
    hacc::TDBID itemID();

private:
    void currencyUpdated();
    void assignActions();
};

}
}
}

#endif // WSIMPLECURRENCYITEM_H
