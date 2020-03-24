#pragma once

#include "changevaluedisplay_bool.h"
#include "globals.h"

namespace {
class InvertMenu;
}

namespace {
class SetFrontRightInvertedDisplay : public ChangeValueDisplay<bool, InvertMenu>
{
public:
    SetFrontRightInvertedDisplay();
};

SetFrontRightInvertedDisplay::SetFrontRightInvertedDisplay() :
    ChangeValueDisplay<bool, InvertMenu>{"Invert front right", front.invertRight}
{
}
}
