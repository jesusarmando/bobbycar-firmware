#pragma once

#include "switchscreenmenuitem.h"

namespace {
class SelectControlModeItem : public SwitchScreenItem
{
public:
    SelectControlModeItem(ControlMode selectedControlMode, ControlMode &controlMode, Display &display, const char *text);

    void triggered() const override;

private:
    const ControlMode m_selectedControlMode;
    ControlMode &m_controlMode;
};

SelectControlModeItem::SelectControlModeItem(ControlMode selectedControlMode, ControlMode &controlMode, Display &display, const char *text) :
    SwitchScreenItem{display, text},
    m_selectedControlMode{selectedControlMode},
    m_controlMode{controlMode}
{
}

void SelectControlModeItem::triggered() const
{
    m_controlMode = m_selectedControlMode;

    SwitchScreenItem::triggered();
}
}
