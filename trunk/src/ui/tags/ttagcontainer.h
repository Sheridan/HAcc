#ifndef TTAGCONTAINER_H
#define TTAGCONTAINER_H
// --------------------------------------------------- h -----------------------------------------
#include "wtagcontainer.h"

namespace ui
{
namespace tag
{

//! Универсальный контейнер для тегов
template <typename TBase, typename TBases> class TTagContainer: public base::WTagContainer, public TBase
{
public:
    TTagContainer(QWidget *parent = 0);
    ~TTagContainer();
    void setObjectName(const QString &name);
    void setItemID(const hacc::TDBID &itemID);
private:
    hacc::TDBID itemID();
    void commitEvent();
    hacc::model::TItemTags & itemTags();
    bool checkSpetialPurposeTag(const hacc::TDBID &tagID);
    TBases *m_worker;
};

}
}

// --------------------------------------------------- cpp -----------------------------------------
namespace ui
{
namespace tag
{

template <typename TBase, typename TBases>            TTagContainer<TBase,TBases>::TTagContainer(QWidget *parent) : base::WTagContainer(parent), TBase()
{
    m_worker = static_cast<TBases *>(TBase::worker());
}
template <typename TBase, typename TBases>            TTagContainer<TBase,TBases>::~TTagContainer()                    {}
template <typename TBase, typename TBases>hacc::TDBID TTagContainer<TBase,TBases>::itemID()                            { return TBase::id(); }
template <typename TBase, typename TBases>void        TTagContainer<TBase,TBases>::setObjectName(const QString &name)  { base::WTagContainer::setObjectName(name); }
template <typename TBase, typename TBases>void        TTagContainer<TBase,TBases>::commitEvent()
{
    m_worker->setTags(selectedTags(), TBase::id());
}

template <typename TBase, typename TBases>hacc::model::TItemTags & TTagContainer<TBase,TBases>::itemTags()
{
    return m_worker->tags(TBase::id());
}

template <typename TBase, typename TBases>bool TTagContainer<TBase,TBases>::checkSpetialPurposeTag(const hacc::TDBID &tagID)
{
    return m_worker->checkSpetialPurposeTag(tagID);
}

template <typename TBase, typename TBases>void TTagContainer<TBase,TBases>::setItemID(const hacc::TDBID &itemID)
{
    TBase::setID(itemID);
}


}
}
#endif // TTAGCONTAINER_H
