#include "wsimplecontractoritem.h"
#include "st.h"

namespace ui
{
namespace item
{
namespace simple
{

WSimpleContractorItem::WSimpleContractorItem(const hacc::TDBID &contractorID)
    : base::WItem(1, 1),
      hacc::model::CContractor()
{
    hacc::model::CContractor::setID(contractorID);
    HACC_INIT_ITEM;
}

WSimpleContractorItem::~WSimpleContractorItem()
{
}

void WSimpleContractorItem::setContractorData(const hacc::TDBID &iconID, const QString &name)
{
    setIcon(0, 0, iconID);
    setText(0, 0, name);
}

void WSimpleContractorItem::assignActions()
{
    controlLabel(0,0)->addAction(hacc::model::CContractor::editAction());
}

void WSimpleContractorItem::contractorUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from contractors where id=?",
                                 QVariantList() << hacc::model::CContractor::id());
    if(q.next())
    {
        setContractorData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

hacc::TDBID WSimpleContractorItem::itemID()
{
    return hacc::model::CContractor::id();
}

}
}
}
