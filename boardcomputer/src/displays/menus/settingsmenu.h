#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "globals.h"

#include "displays/menus/commonsettingsmenu.h"
#include "displays/menus/wifisettingsmenu.h"
#include "displays/menus/bluetoothsettingsmenu.h"
#include "displays/menus/modessettingsmenu.h"
#include "displays/menus/potisettingsmenu.h"
#include "displays/menus/buzzermenu.h"
#include "displays/versiondisplay.h"

namespace {
struct FrontLedAccessor : public RefAccessor<bool> { bool &getRef() const override { return front.command.led; } };
template<typename Tscreen>
class FrontLedChangeScreen :
    public ChangeValueDisplay<bool>,
    public StaticText<TEXT_SETFRONTLED>,
    public FrontLedAccessor
{
    using Base = ChangeValueDisplay<bool>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

struct BackLedAccessor : public RefAccessor<bool> { bool &getRef() const override { return back.command.led; } };
template<typename Tscreen>
class BackLedChangeScreen :
    public ChangeValueDisplay<bool>,
    public StaticText<TEXT_SETBACKLED>,
    public BackLedAccessor
{
    using Base = ChangeValueDisplay<bool>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

template<typename Tscreen>
class SettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_SETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_COMMONSETTINGS>,    DefaultFont, DefaultColor, SwitchScreenAction<CommonSettingsMenu<SettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_WIFISETTINGS>,      DefaultFont, DefaultColor, SwitchScreenAction<WifiSettingsMenu<SettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHSETTINGS>, DefaultFont, DefaultColor, SwitchScreenAction<BluetoothSettingsMenu<SettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_MODESSETTINGS>,     DefaultFont, DefaultColor, SwitchScreenAction<ModesSettingsMenu<SettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_POTISETTINGS>,      DefaultFont, DefaultColor, SwitchScreenAction<PotiSettingsMenu<SettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BUZZER>,            DefaultFont, DefaultColor, SwitchScreenAction<BuzzerMenu<SettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETFRONTLED>,       DefaultFont, DefaultColor, SwitchScreenAction<FrontLedChangeScreen<SettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBACKLED>,        DefaultFont, DefaultColor, SwitchScreenAction<BackLedChangeScreen<SettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_VERSION>,           DefaultFont, DefaultColor, SwitchScreenAction<VersionDisplay<SettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,              DefaultFont, DefaultColor, SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
