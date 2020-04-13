#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "menuitem.h"
#include "actions/toggleboolaction.h"
#include "actions/switchscreenaction.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "texts.h"
#include "globals.h"

namespace {
class CommonSettingsMenu;
}

namespace {
struct FrontLeftInvertedAccessor : public RefAccessor<bool> { bool &getRef() const override { return front.invertLeft; } };
struct FrontRightInvertedAccessor : public RefAccessor<bool> { bool &getRef() const override { return front.invertRight; } };
struct BackLeftInvertedAccessor : public RefAccessor<bool> { bool &getRef() const override { return back.invertLeft; } };
struct BackRightInvertedAccessor : public RefAccessor<bool> { bool &getRef() const override { return back.invertRight; } };

class InvertMenu :
    public MenuDisplay,
    public StaticText<TEXT_SETINVERTED>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_INVERTFRONTLEFT>,  ToggleBoolAction, CheckboxIcon, FrontLeftInvertedAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_INVERTFRONTRIGHT>, ToggleBoolAction, CheckboxIcon, FrontRightInvertedAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_INVERTBACKLEFT>,   ToggleBoolAction, CheckboxIcon, BackLeftInvertedAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_INVERTBACKRIGHT>,  ToggleBoolAction, CheckboxIcon, BackRightInvertedAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,             SwitchScreenAction<CommonSettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
