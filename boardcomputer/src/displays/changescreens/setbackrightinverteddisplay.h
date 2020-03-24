#pragma once

#include "changevaluedisplay_bool.h"
#include "texts.h"
#include "globals.h"

namespace {
class InvertMenu;
}

namespace {
class SetBackRightInvertedDisplay : public ChangeValueDisplay<bool, InvertMenu, TEXT_INVERTBACKRIGHT>
{
public:
    SetBackRightInvertedDisplay();
};

SetBackRightInvertedDisplay::SetBackRightInvertedDisplay() :
    ChangeValueDisplay<bool, InvertMenu, TEXT_INVERTBACKRIGHT>{back.invertRight}
{
}
}
