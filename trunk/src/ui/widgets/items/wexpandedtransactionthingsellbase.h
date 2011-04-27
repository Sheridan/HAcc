/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WTRANSACTIONTHINGSELLBASE_He
#define WTRANSACTIONTHINGSELLBASE_He

#include "wbase.h"
#include "hacc_types.h"
#include "ctransactionpool.h"

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedTransactionThingSellBase : public ui::item::base::WBase, public hacc::model::CTransactionPool
{
public:
    WExpandedTransactionThingSellBase(QWidget *parent = 0);
    WExpandedTransactionThingSellBase(const hacc::TDBID &parentPool, QWidget *parent = 0);
    ~WExpandedTransactionThingSellBase();

private:
    void constructControls(QToolBar *tb);
    base::WContainer *buidContainer();
    void constructHeader(base::WHeader *header);
};

}
}
}
#endif // WTRANSACTIONTHINGSELLBASE_He
