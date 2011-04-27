/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WTRANSACTIONTHINGBUYBASE_He
#define WTRANSACTIONTHINGBUYBASE_He

#include "wbase.h"
#include "hacc_types.h"
#include "ctransactionpool.h"

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedTransactionThingBuyContainer;
class WExpandedTransactionThingBuyBase : public ui::item::base::WBase, public hacc::model::CTransactionPool
{
public:
    WExpandedTransactionThingBuyBase(QWidget *parent = 0);
    WExpandedTransactionThingBuyBase(const hacc::TDBID &parentPool, QWidget *parent = 0);
    ~WExpandedTransactionThingBuyBase();

private:
    void constructControls(QToolBar *tb);
    base::WContainer *buidContainer();
    void constructHeader(base::WHeader *header);
};

}
}
}
#endif // WTRANSACTIONTHINGBUYBASE_He
