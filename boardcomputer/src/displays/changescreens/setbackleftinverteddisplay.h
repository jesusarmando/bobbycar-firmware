#pragma once

#include "changevaluedisplay_bool.h"
#include "texts.h"
#include "globals.h"

namespace {
class InvertMenu;
}

namespace {
class SetBackLeftInvertedDisplay : public ChangeValueDisplay<bool, InvertMenu, TEXT_INVERTBACKLEFT>
{
public:
    SetBackLeftInvertedDisplay();
};

SetBackLeftInvertedDisplay::SetBackLeftInvertedDisplay() :
    ChangeValueDisplay<bool, InvertMenu, TEXT_INVERTBACKLEFT>{back.invertLeft}
{
}
}
