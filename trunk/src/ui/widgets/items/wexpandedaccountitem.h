/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WACCOUNTITEM_He
#define WACCOUNTITEM_He

#include "witem.h"
#include "caccount.h"
#include "ccurrency.h"

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedAccountContainer;
class WExpandedAccountItem :
                     public ui::item::base::WItem,
                     public hacc::model::CAccount,
                     public hacc::model::CCurrency
{
public:
    WExpandedAccountItem(const hacc::TDBID &accountID, const hacc::TDBID &currencyID);
    ~WExpandedAccountItem();
    void setAccountData (const hacc::TDBID &iconID , const QString &name);
    void setCurrencyData(const hacc::TDBID &iconID , const QString &name);
    hacc::TDBID itemID();

private:
    QVBoxLayout *m_baseLayout;
    void buildExpanderUIEvent();
    void assignActions();

private slots:
    void accountUpdated();
    void currencyUpdated();
};

}
}
}
#endif // WACCOUNTITEM_He
