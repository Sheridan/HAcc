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

private:
    hacc::model::EContractorFilter m_filter;
    void appendContractorAcount(const hacc::TDBID &accountId, const QString &accountName,
                                const hacc::TDBID &accountIconId,  const hacc::TDBID &contractorID,
                                const QString &contractorName, const hacc::TDBID &contractorIconId);

public slots:
    void refresh(const hacc::TDBID &createdID = 0);

};

}
}
}
#endif // WCONTRACTORACCOUNTCONTAINER_Hs
