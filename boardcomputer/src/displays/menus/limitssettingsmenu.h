#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "settingsaccessors.h"

namespace {
class LimitsSettingsMenu;
class SettingsMenu;
}

namespace {
using IMotMaxChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETIMOTMAX>, IMotMaxAccessor, SwitchScreenAction<LimitsSettingsMenu>>;
using IDcMaxChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETIDCMAX>, IDcMaxAccessor, SwitchScreenAction<LimitsSettingsMenu>>;
using NMotMaxKmhChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETNMOTMAXKMH>, NMotMaxKmhAccessor, SwitchScreenAction<LimitsSettingsMenu>>;
using NMotMaxRpmChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETNMOTMAX>, NMotMaxRpmAccessor, SwitchScreenAction<LimitsSettingsMenu>>;
using FieldWeakMaxChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETFIELDWEAKMAX>, FieldWeakMaxAccessor, SwitchScreenAction<LimitsSettingsMenu>>;
using PhaseAdvMaxChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETPHASEADVMAX>, PhaseAdvMaxAccessor, SwitchScreenAction<LimitsSettingsMenu>>;

class LimitsSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_LIMITSSETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_SETIMOTMAX>,      SwitchScreenAction<IMotMaxChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETIDCMAX>,       SwitchScreenAction<IDcMaxChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETNMOTMAXKMH>,   SwitchScreenAction<NMotMaxKmhChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETNMOTMAX>,      SwitchScreenAction<NMotMaxRpmChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETFIELDWEAKMAX>, SwitchScreenAction<FieldWeakMaxChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETPHASEADVMAX>,  SwitchScreenAction<PhaseAdvMaxChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,            SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
