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
struct FrontLeftEnabledAccessor : public RefAccessor<bool> { bool &getRef() const override { return front.command.left.enable; } };
struct FrontRightEnabledAccessor : public RefAccessor<bool> { bool &getRef() const override { return front.command.right.enable; } };
struct BackLeftEnabledAccessor : public RefAccessor<bool> { bool &getRef() const override { return back.command.left.enable; } };
struct BackRightEnabledAccessor : public RefAccessor<bool> { bool &getRef() const override { return back.command.right.enable; } };

class EnableMenu :
    public MenuDisplay,
    public StaticText<TEXT_SETENABLED>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_ENABLEFRONTLEFT>,  ToggleBoolAction, CheckboxIcon, FrontLeftEnabledAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_ENABLEFRONTRIGHT>, ToggleBoolAction, CheckboxIcon, FrontRightEnabledAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_ENABLEBACKLEFT>,   ToggleBoolAction, CheckboxIcon, BackLeftEnabledAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_ENABLEBACKRIGHT>,  ToggleBoolAction, CheckboxIcon, BackRightEnabledAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,             SwitchScreenAction<CommonSettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
