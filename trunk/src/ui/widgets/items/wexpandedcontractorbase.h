#ifndef WCONTRACTORBASE_He
#define WCONTRACTORBASE_He

#include "wbase.h"
#include <QComboBox>
#include "wexpandedcontractorcontainer.h"

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedContractorBase : public ui::item::base::WBase
{
    Q_OBJECT
public:
    WExpandedContractorBase(QWidget *parent = 0);
    ~WExpandedContractorBase();
private:
    void constructControls(QToolBar *tb);
    QComboBox *m_cbContractorFilter;
    ui::item::base::WContainer *buidContainer();
    void constructHeader(base::WHeader *header);

private slots:
    void setContainerAccountFilter(int filter);
};

}
}
}
#endif // WCONTRACTORBASE_He
