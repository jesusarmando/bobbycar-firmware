#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "globals.h"

namespace {
class CommonSettingsMenu;
class EnableMenu;
class InvertMenu;
class SettingsMenu;
}

namespace {
struct IMotMaxAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return settings.iMotMax; } };
using IMotMaxChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETIMOTMAX>, IMotMaxAccessor, SwitchScreenAction<CommonSettingsMenu>>;

struct IDcMaxAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return settings.iDcMax; } };
using IDcMaxChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETIDCMAX>, IDcMaxAccessor, SwitchScreenAction<CommonSettingsMenu>>;

struct NMotMaxKmhAccessor : public virtual AccessorInterface<int16_t>
{
    int16_t getValue() const override { return convertToKmh(settings.nMotMax); }
    void setValue(int16_t value) override { settings.nMotMax = convertFromKmh(value); }
};
using NMotMaxKmhChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETNMOTMAXKMH>, NMotMaxKmhAccessor, SwitchScreenAction<CommonSettingsMenu>>;

struct NMotMaxAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return settings.nMotMax; } };
using NMotMaxChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETNMOTMAX>, NMotMaxAccessor, SwitchScreenAction<CommonSettingsMenu>>;

struct FieldWeakMaxAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return settings.fieldWeakMax; } };
using FieldWeakMaxChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETFIELDWEAKMAX>, FieldWeakMaxAccessor, SwitchScreenAction<CommonSettingsMenu>>;

struct PhaseAdvMaxAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return settings.phaseAdvMax; } };
using PhaseAdvMaxChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETPHASEADVMAX>, PhaseAdvMaxAccessor, SwitchScreenAction<CommonSettingsMenu>>;

class CommonSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_COMMONSETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_SETIMOTMAX>,      SwitchScreenAction<IMotMaxChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETIDCMAX>,       SwitchScreenAction<IDcMaxChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETNMOTMAXKMH>,   SwitchScreenAction<NMotMaxKmhChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETNMOTMAX>,      SwitchScreenAction<NMotMaxChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETFIELDWEAKMAX>, SwitchScreenAction<FieldWeakMaxChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETPHASEADVMAX>,  SwitchScreenAction<PhaseAdvMaxChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETENABLED>,      SwitchScreenAction<EnableMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_SETINVERTED>,     SwitchScreenAction<InvertMenu>>   ,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,            SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
