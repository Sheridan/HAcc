#ifndef TITEMTAGSEDIT_H
#define TITEMTAGSEDIT_H
#include "fitemtagsedit.h"

namespace ui
{
//! Фомы, диалоги
namespace form
{

template <typename TagsContainer> class TItemTagsEdit : public FItemTagsEdit
{
public:
    TItemTagsEdit(const hacc::TDBID &id, QWidget *parent = 0);
    ~TItemTagsEdit();
    ui::tag::base::WTagContainer *constructContainer();
};


}
}
// -------------------------------  cpp ----------------------------------------
namespace ui
{
namespace form
{

template <typename TagsContainer>TItemTagsEdit<TagsContainer>::TItemTagsEdit(const hacc::TDBID &id, QWidget *parent) :
    FItemTagsEdit(id, parent)
{}

template <typename TagsContainer>TItemTagsEdit<TagsContainer>::~TItemTagsEdit()
{}

template <typename TagsContainer>ui::tag::base::WTagContainer *TItemTagsEdit<TagsContainer>::constructContainer()
{
    TagsContainer *ctr = new TagsContainer();
    ctr->setItemID(id());
    return ctr;
}

}
}

#endif // TITEMTAGSEDIT_H
