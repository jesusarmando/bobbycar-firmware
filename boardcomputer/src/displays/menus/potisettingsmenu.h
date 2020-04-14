#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "settingsaccessors.h"

namespace {
class PotiSettingsMenu;
class CalibrateDisplay;
class HardwareSettingsMenu;
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

using SampleCountChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETSAMPLECOUNT>, SampleCountAccessor, SwitchScreenAction<PotiSettingsMenu>>;
using GasMinChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETGASMIN>, GasMinAccessor, SwitchScreenAction<PotiSettingsMenu>>;
using GasMaxChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETGASMAX>, GasMaxAccessor, SwitchScreenAction<PotiSettingsMenu>>;
using BremsMinChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETBREMSMIN>, BremsMinAccessor, SwitchScreenAction<PotiSettingsMenu>>;
using BremsMaxChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETBREMSMAX>, BremsMaxAccessor, SwitchScreenAction<PotiSettingsMenu>>;

class PotiSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_POTISETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, GasText,                         DisabledColor, StaticFont<2>, DummyAction>,
        makeComponent<MenuItem, BremsText,                       DisabledColor, StaticFont<2>, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_CALIBRATE>,      SwitchScreenAction<CalibrateDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETSAMPLECOUNT>, SwitchScreenAction<SampleCountChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGASMIN>,      SwitchScreenAction<GasMinChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGASMAX>,      SwitchScreenAction<GasMaxChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBREMSMIN>,    SwitchScreenAction<BremsMinChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBREMSMAX>,    SwitchScreenAction<BremsMaxChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,           SwitchScreenAction<HardwareSettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
