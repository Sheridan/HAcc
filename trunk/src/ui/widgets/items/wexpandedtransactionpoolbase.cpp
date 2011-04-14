#include "wexpandedtransactionpoolbase.h"
#include "wexpandedtransactionpoolcontainer.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace expanded
{

WExpandedTransactionPoolBase::WExpandedTransactionPoolBase(QWidget *parent) : ui::item::base::WBase(parent)
{}

WExpandedTransactionPoolBase::~WExpandedTransactionPoolBase()
{}

void WExpandedTransactionPoolBase::constructControls(QToolBar *tb)
{
    tb->addAction(HACC_TRANSACTIONS_POOLS->addTransactionLocalAction());
    tb->addAction(HACC_TRANSACTIONS_POOLS->addTransactionBuyAction());
    tb->addAction(HACC_TRANSACTIONS_POOLS->addTransactionSellAction());
    tb->addSeparator();
    tb->addAction(HACC_TRANSACTIONS_POOLS->addTransactionMoneyIncomingAction());
    tb->addAction(HACC_TRANSACTIONS_POOLS->addTransactionMoneyOutgoingAction());
    tb->addSeparator();
//    tb->addAction(HACC_TRANSACTIONS_POOLS->addTransactionAcceptGiftAction());
//    tb->addAction(HACC_TRANSACTIONS_POOLS->addTransactionGiveGiftAction());

}

base::WContainer *WExpandedTransactionPoolBase::buidContainer()
{
    return new WExpandedTransactionPoolContainer(this);
}

void WExpandedTransactionPoolBase::constructHeader(base::WHeader *header)
{
    header->setLabels(4,2,QStringList()
                      << tr("Source contractor")
                      << tr("Source account")
                      << tr("Destination contractor")
                      << tr("Destination account")
                      << tr("Date")
                      << tr("Time")
                      << tr("Transactions count")
                      << tr("Total cost"));
}

}
}
}
