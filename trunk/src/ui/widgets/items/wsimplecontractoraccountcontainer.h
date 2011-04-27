/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WCONTRACTORACCOUNTCONTAINER_Hs
#define WCONTRACTORACCOUNTCONTAINER_Hs

#include "wcontainer.h"
#include "ccontractors.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleContractorAccountContainer : public ui::item::base::WContainer
{
    Q_OBJECT
public:
    explicit WSimpleContractorAccountContainer(hacc::model::EContractorFilter filter, QWidget *parent = 0);
    ~WSimpleContractorAccountContainer();
    void setCurrencyFilter(const hacc::TDBID &currencyID);

private:
    hacc::model::EContractorFilter m_filter;
    hacc::TDBID m_currencyID;
    void appendRow(const hacc::TDBID &accountID   , const QString &accountName   , const hacc::TDBID &accountIconID,
                   const hacc::TDBID &contractorID, const QString &contractorName, const hacc::TDBID &contractorIconID,
                   const hacc::TDBID &currencyID  , const QString &currencyName  , const hacc::TDBID &currencyIconID);

public slots:
    void refresh(const hacc::TDBID &createdID = 0);

};

}
}
}
#endif // WCONTRACTORACCOUNTCONTAINER_Hs
