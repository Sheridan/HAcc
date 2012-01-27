#include "ciconscache.h"
#include "special_tags_types.h"
#include "icons.h"
namespace tools
{
namespace icons
{

CIconsCache::CIconsCache()
{
}

CIconsCache::~CIconsCache()
{
    foreach (QIcon *i, m_icons) { delete i; }
    foreach (QIcon *i, m_eIcons) { delete i; }
    m_icons.clear();
    m_eIcons.clear();
}

#define HACC_MAX_ICONS 11
int CIconsCache::id(const EIcons &eIcon, const EOverlays &eOverlay)
{
    return (static_cast<int>(eIcon) * HACC_MAX_ICONS) + static_cast<int>(eOverlay);
}

const QIcon & CIconsCache::icon(const EIcons &eIcon, const EOverlays &eOverlay)
{
    int iid = id(eIcon, eOverlay);
    if(!m_icons.contains(iid))
    {
        QString file = ":/main/icons/item-empty.png";
        switch (eOverlay)
        {
            case oNew       : file=":/overlays/new.png"       ; break;
            case oTag       : file=":/overlays/tag.png"       ; break;
            case oEdit      : file=":/overlays/edit.png"      ; break;
            case oLocal     : file=":/overlays/local.png"     ; break;
            case oRemove    : file=":/overlays/delete.png"    ; break;
            case oIncoming  : file=":/overlays/incoming.png"  ; break;
            case oOutgoing  : file=":/overlays/outgoing.png"  ; break;
            case oWriteOff  : file=":/overlays/write-off.png" ; break;
            case oNewWindow : file=":/overlays/window-new.png"; break;
            case oCommission: file=":/overlays/commission.png"; break;
        }
        m_icons[iid] = new QIcon(stratificateIcons(icon(eIcon), setIconOpacity(file, 0.8)));
    }
    return *m_icons[iid];
}

const QIcon & CIconsCache::icon(const int& tagID)
{
    switch (tagID)
    {
        case HACC_TAG_ID_WRITE_OFF    : return icon(iMovement, oWriteOff  ); break;
        case HACC_TAG_ID_BUYING       : return icon(iValuable, oIncoming  ); break;
        case HACC_TAG_ID_SELLING      : return icon(iValuable, oOutgoing  ); break;
        case HACC_TAG_ID_TRANSFER     : return icon(iMoney   , oLocal     ); break;
        case HACC_TAG_ID_COMMISSION   : return icon(iMoney   , oCommission); break;
        case HACC_TAG_ID_INCOMING     : return icon(iMoney   , oIncoming  ); break;
        case HACC_TAG_ID_OUTGOING     : return icon(iMoney   , oOutgoing  ); break;
        //        case HACC_TAG_ID_GIFT_GIVE : return icon(); break;
        //        case HACC_TAG_ID_GIFT_ACCEPT   : return icon(); break;
        //        case HACC_TAG_ID_TAX          : return icon(); break;
        //        case HACC_TAG_ID_SERVICE        : return icon(); break;
        //        case HACC_TAG_ID_OBJECT         : return icon(); break;
        //        case HACC_TAG_ID_EXPENDABLE     : return icon(); break;
    }
    return *(new QIcon(":/main/icons/item-empty.png"));
}

const QIcon & CIconsCache::icon(const EIcons &eIcon)
{
    if(!m_eIcons.contains(eIcon))
    {
        QString file    = ":/main/icons/item-empty.png";
        switch (eIcon)
        {
            case iTag            : file=":/items/tag.png"             ; break;
            case iIcon           : file=":/items/icon.png"            ; break;
            case iGift           : file=":/items/gift.png"            ; break;
            case iMoney          : file=":/items/money.png"           ; break;
            case iThing          : file=":/items/thing.png"           ; break;
            case iAccount        : file=":/items/account.png"         ; break;
            case iMovement       : file=":/items/movement.png"        ; break;
            case iCurrency       : file=":/items/currency.png"        ; break;
            case iValuable       : file=":/items/valuable.png"        ; break;
            case iContractor     : file=":/items/contractor.png"      ; break;
            case iEnumerated     : file=":/items/enumerated.png"      ; break;
            case iTransaction    : file=":/items/transaction.png"     ; break;
            case iDescription    : file=":/main/description.png"      ; break;
            case iManufacturer   : file=":/items/manufacturer.png"    ; break;
            case iContractorSelf : file=":/items/contractor-self.png" ; break;
            case iTransactionPool: file=":/items/transaction-pool.png"; break;
        }
        m_eIcons[eIcon] = new QIcon(file);
    }
    return *m_eIcons[eIcon];
}

}
}
