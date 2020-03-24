#pragma once

#include "changevaluedisplay_bool.h"
#include "texts.h"
#include "globals.h"

namespace {
class InvertMenu;
}

namespace {
class SetFrontRightInvertedDisplay : public ChangeValueDisplay<bool, InvertMenu, TEXT_INVERTFRONTRIGHT>
{
public:
    SetFrontRightInvertedDisplay();
};

SetFrontRightInvertedDisplay::SetFrontRightInvertedDisplay() :
    ChangeValueDisplay<bool, InvertMenu, TEXT_INVERTFRONTRIGHT>{front.invertRight}
{
}
}
