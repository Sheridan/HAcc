#include "wexpandedaccountbase.h"
#include "st.h"
namespace ui
{
namespace item
{
namespace expanded
{
WExpandedAccountBase::WExpandedAccountBase(const hacc::TDBID &parentContractor, QWidget *parent)
    : ui::item::base::WBase(parent),
      hacc::model::CContractor()
{
    setID(parentContractor);
}

WExpandedAccountBase::~WExpandedAccountBase()
{}

void WExpandedAccountBase::constructControls(QToolBar *tb)
{
    tb->addAction(addAccountAction());
}

base::WContainer *WExpandedAccountBase::buidContainer()
{
    return new WExpandedAccountContainer(id(), this);
}

void WExpandedAccountBase::constructHeader(base::WHeader *header)
{
    header->setLabels(1,1,QStringList() << QObject::tr("Name"));
}

}
}
}
