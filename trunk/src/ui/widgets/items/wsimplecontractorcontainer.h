#ifndef WSIMPLECONTRACTORCONTAINER_H
#define WSIMPLECONTRACTORCONTAINER_H

#include "wcontainer.h"
#include "ccontractors.h"

namespace ui
{
namespace item
{
namespace simple
{

class WSimpleContractorContainer : public ui::item::base::WContainer
{
    Q_OBJECT
public:
    explicit WSimpleContractorContainer(hacc::model::EContractorFilter filter, QWidget *parent = 0);
    ~WSimpleContractorContainer();

private:
    hacc::model::EContractorFilter m_filter;
    void appendContractor(const hacc::TDBID &contractorID, const QString &contractorName, const hacc::TDBID &contractorIconId);

public slots:
    void refresh(const hacc::TDBID &createdID = 0);

};

}
}
}
#endif // WSIMPLECONTRACTORCONTAINER_H
