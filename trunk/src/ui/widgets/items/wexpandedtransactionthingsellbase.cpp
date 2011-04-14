#include "wexpandedtransactionthingsellbase.h"
#include "wexpandedtransactionthingsellcontainer.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

WExpandedTransactionThingSellBase::WExpandedTransactionThingSellBase(QWidget *parent)
    : ui::item::base::WBase(parent),
      hacc::model::CTransactionPool()
{
}

WExpandedTransactionThingSellBase::WExpandedTransactionThingSellBase(const hacc::TDBID &parentPool, QWidget *parent)
    : ui::item::base::WBase(parent),
      hacc::model::CTransactionPool()
{
    setID(parentPool);
}

WExpandedTransactionThingSellBase::~WExpandedTransactionThingSellBase()
{}

void WExpandedTransactionThingSellBase::constructControls(QToolBar *tb)
{
    tb->addAction(hacc::model::CTransactionPool::addSellAction());
}

base::WContainer *WExpandedTransactionThingSellBase::buidContainer()
{
    return new WExpandedTransactionThingSellContainer(id(), this);
}

void WExpandedTransactionThingSellBase::constructHeader(base::WHeader *header)
{
    header->setLabels(6,1,QStringList()
                      << QObject::tr("Thing")
                      << QObject::tr("Manufacturer")
                      << QObject::tr("Buy money")
                      << QObject::tr("Sell money")
                      << QObject::tr("Current owner")
                      << QObject::tr("Serial"));
}

}
}
}
