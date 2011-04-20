#include "wexpandedcontractoritem.h"
#include "st.h"
#include <QHBoxLayout>

namespace ui
{
namespace item
{
namespace expanded
{

WExpandedContractorItem::WExpandedContractorItem(const hacc::TDBID &id)
    : ui::item::base::WItem(1, 1, true),
      hacc::model::CContractor()
{
    setID(id);
    HACC_INIT_ITEM;
}

WExpandedContractorItem::~WExpandedContractorItem()
{
}

void WExpandedContractorItem::buildExpanderUIEvent()
{
    appendContainer(new ui::item::expanded::WExpandedAccountBase(itemID()),
                    HACC_ICONS->icon(tools::icons::iAccount),
                    QObject::tr("Accounts"));
    appendTagsTab < ui::tag::TTagContainer <hacc::model::CContractor, hacc::model::CContractors> >();
}

void WExpandedContractorItem::assignActions()
{
    controlLabel(0, 0)->addAction(hacc::model::CContractor::editAction());
    if(itemID() > 2) { controlLabel(0, 0)->addAction(hacc::model::CContractor::removeAction()); }
    controlLabel(0, 0)->addAction(hacc::model::CContractor::tagsEditAction());
}

void WExpandedContractorItem::setItemData(const hacc::TDBID &iconID, const QString &name)
{
    setIcon(0, 0, iconID);
    setText(0, 0, name);
}

void WExpandedContractorItem::contractorUpdated()
{
    QSqlQuery q = HACC_DB->query("select name, icon_id from contractors where id=?", QVariantList() << itemID());
    if(q.next())
    {
        setItemData(HACC_DB_2_DBID(q, 1), HACC_DB_2_STRG(q, 0));
    }
}

hacc::TDBID WExpandedContractorItem::itemID()
{
    return hacc::model::CContractor::id();
}

}
}
}
