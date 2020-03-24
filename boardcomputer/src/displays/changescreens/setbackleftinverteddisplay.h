#pragma once

#include "changevaluedisplay_bool.h"
#include "globals.h"

namespace {
class InvertMenu;
}

namespace {
class SetBackLeftInvertedDisplay : public ChangeValueDisplay<bool, InvertMenu>
{
public:
    SetBackLeftInvertedDisplay();
};

SetBackLeftInvertedDisplay::SetBackLeftInvertedDisplay() :
    ChangeValueDisplay<bool, InvertMenu>{"Invert back left", back.invertLeft}
{
}
}
