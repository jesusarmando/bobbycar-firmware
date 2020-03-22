#pragma once

#include "globals.h"
#include "switchscreenmenuitem.h"

namespace {
class SelectModeItem : public SwitchScreenItem
{
public:
    SelectModeItem(ModeBase &mode, Display &display, const char *text);

    void triggered() const override;

private:
    ModeBase &m_mode;
};

SelectModeItem::SelectModeItem(ModeBase &mode, Display &display, const char *text) :
    SwitchScreenItem{display, text},
    m_mode{mode}
{
}

void SelectModeItem::triggered() const
{
    currentMode = &m_mode;

    SwitchScreenItem::triggered();
}
}
