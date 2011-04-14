#include "wtaglabel.h"
#include <QVariant>
#include "resources.h"
#include "st.h"

namespace ui
{
namespace tag
{
namespace base
{

WTagLabel::WTagLabel(const hacc::TDBID &tagID, QWidget *parent)
    : ui::widget::WLabelButton(parent),
      hacc::CIDItem(tagID)
{
    setMargin(0);
}

WTagLabel::~WTagLabel()
{}

void WTagLabel::mouseClickEvent()
{
    emit clicked(id());
}

void WTagLabel::setAttached(bool attached)
{
    setProperty("tagAttached", attached);
    setStyleSheet(tools::resources::readTextResource(":/qss/taglabel.qss"));
}

}
}
}
