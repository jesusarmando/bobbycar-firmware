#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "globals.h"

namespace {
class PotiSettingsMenu;
class CalibrateDisplay;
class SettingsMenu;
}

namespace {
struct GasText : public virtual TextInterface {
public:
    String text() const override { return String{"gas: "} + raw_gas + ": " + gas; }
};
struct BremsText : public virtual TextInterface {
public:
    String text() const override { return String{"brems: "} + raw_brems + ": " + brems; }
};

struct GasMinAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return gasMin; } };
using GasMinChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETGASMIN>, GasMinAccessor, SwitchScreenAction<PotiSettingsMenu>>;

struct GasMaxAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return gasMax; } };
using GasMaxChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETGASMAX>, GasMaxAccessor, SwitchScreenAction<PotiSettingsMenu>>;

struct BremsMinAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return bremsMin; } };
using BremsMinChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETBREMSMIN>, BremsMinAccessor, SwitchScreenAction<PotiSettingsMenu>>;

struct BremsMaxAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return bremsMax; } };
using BremsMaxChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETBREMSMAX>, BremsMaxAccessor, SwitchScreenAction<PotiSettingsMenu>>;

class PotiSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_POTISETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, GasText,                      DisabledColor, DummyAction>,
        makeComponent<MenuItem, BremsText,                    DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_CALIBRATE>,   SwitchScreenAction<CalibrateDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGASMIN>,   SwitchScreenAction<GasMinChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGASMAX>,   SwitchScreenAction<GasMaxChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBREMSMIN>, SwitchScreenAction<BremsMinChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBREMSMAX>, SwitchScreenAction<BremsMaxChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,        SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
