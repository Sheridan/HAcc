/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WCONTRACTORITEM_He
#define WCONTRACTORITEM_He

#include "witem.h"
#include <QLabel>
#include <QSplitter>
#include <QHBoxLayout>
#include "ccontractor.h"
#include "wexpandedaccountbase.h"

namespace ui
{
namespace item
{
namespace expanded
{

class WExpandedContractorContainer;
class WExpandedContractorItem : public ui::item::base::WItem,
                        public hacc::model::CContractor
{
public:
    WExpandedContractorItem(const hacc::TDBID &id);
    ~WExpandedContractorItem();
    void setItemData(const hacc::TDBID &iconID, const QString &name);
    hacc::TDBID itemID();

private:
    void buildExpanderUIEvent();
    int expandHeight();
    void assignActions();

private:
    void contractorUpdated();
};

}
}
}
#endif // WCONTRACTORITEM_He
