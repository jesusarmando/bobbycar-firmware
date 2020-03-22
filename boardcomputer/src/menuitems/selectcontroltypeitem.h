#pragma once

#include "switchscreenmenuitem.h"

namespace {
class SelectControlTypeItem : public SwitchScreenItem
{
public:
    SelectControlTypeItem(ControlType selectedControlType, ControlType &controlType, Display &display, const char *text);

    void triggered() const override;

private:
    const ControlType m_selectedControlType;
    ControlType &m_controlType;
};

SelectControlTypeItem::SelectControlTypeItem(ControlType selectedControlType, ControlType &controlType, Display &display, const char *text) :
    SwitchScreenItem{display, text},
    m_selectedControlType{selectedControlType},
    m_controlType{controlType}
{
}

void SelectControlTypeItem::triggered() const
{
    m_controlType = m_selectedControlType;

    SwitchScreenItem::triggered();
}
}
