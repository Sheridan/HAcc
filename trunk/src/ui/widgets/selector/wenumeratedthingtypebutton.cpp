#include "wenumeratedthingtypebutton.h"
#include "wenumeratedthingtypepopup.h"
#include "st.h"

namespace ui
{
namespace selector
{

WEnumeratedThingTypeButton::WEnumeratedThingTypeButton(QWidget *parent) : base::WSelectorButton(parent)
{
    m_layout = new QHBoxLayout();

    m_eTThingIcon = new ui::icons::WIcon(16, this);
    m_eTThingName = new QLabel(this);

    m_layout->addWidget(m_eTThingIcon);
    m_layout->addWidget(m_eTThingName);

    setID(1);

    m_eTThingIcon->setIcon(HACC_ICONS->icon(tools::icons::iEnumerated));

    setLayout(m_layout);

    connect(HACC_ENUMERATED_THING_TYPES, SIGNAL(created(const hacc::TDBID &)), this, SLOT(eTTCreated(const hacc::TDBID &)));
}

WEnumeratedThingTypeButton::~WEnumeratedThingTypeButton()
{
    delete m_eTThingName;
    delete m_eTThingIcon;
    delete m_layout;
}

void WEnumeratedThingTypeButton::idChanged()
{
    setData(HACC_ENUMERATED_THING_TYPES->thingEnumerateTypeName(id()));
}

base::WSelectorPopup * WEnumeratedThingTypeButton::constructPopup()
{
    return new WEnumeratedThingTypePopup(this);
}

void WEnumeratedThingTypeButton::setData(const QString &eTThingName)
{
    m_eTThingName->setText(eTThingName);
}

void WEnumeratedThingTypeButton::eTTCreated(const hacc::TDBID &eTTID)
{
    setID(eTTID);
}

}
}
