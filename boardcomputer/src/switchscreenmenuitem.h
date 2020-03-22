#pragma once

#include "globals.h"
#include "menuitem.h"

namespace {
class SwitchScreenItem : public MenuItem
{
public:
    SwitchScreenItem(Display &display, const char *text);

    void triggered() const override;

private:
    Display &m_display;
};

SwitchScreenItem::SwitchScreenItem(Display &display, const char *text) :
    MenuItem{text},
    m_display{display}
{
}

void SwitchScreenItem::triggered() const
{
    currentDisplay = &m_display;
}
}
