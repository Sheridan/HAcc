#ifndef WSIMPLECONTRACTORBASE_H
#define WSIMPLECONTRACTORBASE_H
#include "wbase.h"
#include "wsimplecontractorcontainer.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleContractorBase : public ui::item::base::WBase
{
    Q_OBJECT
public:
    explicit WSimpleContractorBase(hacc::model::EContractorFilter filter, QWidget *parent = 0);
    ~WSimpleContractorBase();
private:
    void constructControls(QToolBar *tb);
    hacc::model::EContractorFilter m_filter;
    ui::item::base::WContainer *buidContainer();
    void constructHeader(base::WHeader *header);

};

}
}
}

#endif // WSIMPLECONTRACTORBASE_H
