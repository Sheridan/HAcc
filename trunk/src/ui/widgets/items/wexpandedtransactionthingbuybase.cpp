#include "wexpandedtransactionthingbuybase.h"
#include "wexpandedtransactionthingbuycontainer.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

WExpandedTransactionThingBuyBase::WExpandedTransactionThingBuyBase(QWidget *parent)
    : ui::item::base::WBase(parent),
      hacc::model::CTransactionPool()
{
}

WExpandedTransactionThingBuyBase::WExpandedTransactionThingBuyBase(const hacc::TDBID &parentPool, QWidget *parent)
    : ui::item::base::WBase(parent),
      hacc::model::CTransactionPool()
{
    setID(parentPool);
}

WExpandedTransactionThingBuyBase::~WExpandedTransactionThingBuyBase()
{}

void WExpandedTransactionThingBuyBase::constructControls(QToolBar *tb)
{
    tb->addAction(hacc::model::CTransactionPool::addAction());
}

base::WContainer *WExpandedTransactionThingBuyBase::buidContainer()
{
    return new WExpandedTransactionThingBuyContainer(id(), this);
}

void WExpandedTransactionThingBuyBase::constructHeader(base::WHeader *header)
{
    header->setLabels(4,1,QStringList()
                      << QObject::tr("Thing")
                      << QObject::tr("Manufacturer")
                      << QObject::tr("Amount")
                      << QObject::tr("Cost"));
}

}
}
}
