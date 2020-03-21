#pragma once

#include "globals.h"
#include "menuitem.h"

namespace {
class Display;

class SwitchScreenItem : public MenuItem
{
public:
    SwitchScreenItem(Display &display, const char *text);

    void triggered() override;

private:
    Display &m_display;
};

SwitchScreenItem::SwitchScreenItem(Display &display, const char *text) :
    MenuItem{text},
    m_display{display}
{
}

void SwitchScreenItem::triggered()
{
    currentDisplay = &m_display;
}
}
