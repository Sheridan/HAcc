#include "ciditem.h"
namespace hacc
{

CIDItem::CIDItem(const hacc::TDBID & id)
{
    setID(id);
}

hacc::TDBID & CIDItem::id()
{
    return m_id;
}

void CIDItem::setID(const hacc::TDBID & id)
{
    m_id = id;
}

}
