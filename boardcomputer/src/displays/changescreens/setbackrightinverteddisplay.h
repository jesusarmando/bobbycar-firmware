#pragma once

#include "changevaluedisplay_bool.h"
#include "globals.h"

namespace {
class InvertMenu;
}

namespace {
class SetBackRightInvertedDisplay : public ChangeValueDisplay<bool, InvertMenu>
{
public:
    SetBackRightInvertedDisplay();
};

SetBackRightInvertedDisplay::SetBackRightInvertedDisplay() :
    ChangeValueDisplay<bool, InvertMenu>{"Invert back right", back.invertRight}
{
}
}
