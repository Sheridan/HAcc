#ifndef WSIMPLECURRENCYCONTAINER_H
#define WSIMPLECURRENCYCONTAINER_H
#include "wcontainer.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleCurrencyContainer : public ui::item::base::WContainer
{
    Q_OBJECT
public:
    WSimpleCurrencyContainer(QWidget *parent = 0);
    ~WSimpleCurrencyContainer();

private:
    void appendCurrency(const hacc::TDBID &id, const hacc::TDBID &iconID, const QString &name, const QString &reduction);

public slots:
    void refresh(const hacc::TDBID &id = 0);
};

}
}
}
#endif // WSIMPLECURRENCYCONTAINER_H
