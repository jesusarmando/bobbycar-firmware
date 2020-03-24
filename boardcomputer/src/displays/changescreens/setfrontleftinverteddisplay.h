#pragma once

#include "changevaluedisplay_bool.h"
#include "texts.h"
#include "globals.h"

namespace {
class InvertMenu;
}

namespace {
class SetFrontLeftInvertedDisplay : public ChangeValueDisplay<bool, InvertMenu, TEXT_INVERTFRONTLEFT>
{
public:
    SetFrontLeftInvertedDisplay();
};

SetFrontLeftInvertedDisplay::SetFrontLeftInvertedDisplay() :
    ChangeValueDisplay<bool, InvertMenu, TEXT_INVERTFRONTLEFT>{front.invertLeft}
{
}
}
