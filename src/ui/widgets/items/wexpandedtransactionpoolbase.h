#ifndef WTRANSACTIONPOOLBASE_He
#define WTRANSACTIONPOOLBASE_He

#include "wbase.h"
#include "hacc_types.h"

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedTransactionPoolContainer;
class WExpandedTransactionPoolBase : public ui::item::base::WBase
{
    Q_OBJECT
public:
    WExpandedTransactionPoolBase(QWidget *parent = 0);
    ~WExpandedTransactionPoolBase();

private:
    void constructControls(QToolBar *tb);
    base::WContainer *buidContainer();
    void constructHeader(base::WHeader *header);

};

}
}
}
#endif // WTRANSACTIONPOOLBASE_He
