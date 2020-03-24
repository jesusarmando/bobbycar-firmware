#pragma once

#include "changevaluedisplay_bool.h"
#include "globals.h"

namespace {
class InvertMenu;
}

namespace {
class SetFrontLeftInvertedDisplay : public ChangeValueDisplay<bool, InvertMenu>
{
public:
    SetFrontLeftInvertedDisplay();
};

SetFrontLeftInvertedDisplay::SetFrontLeftInvertedDisplay() :
    ChangeValueDisplay<bool, InvertMenu>{"Invert front left", front.invertLeft}
{
}
}
