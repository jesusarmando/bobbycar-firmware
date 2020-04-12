#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "displays/menus/enablemenu.h"
#include "displays/menus/invertmenu.h"
#include "icons/back.h"
#include "texts.h"
#include "globals.h"

namespace {
struct IMotMaxAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return settings.iMotMax; } };
template<typename Tscreen>
using IMotMaxChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETIMOTMAX>, IMotMaxAccessor, SwitchScreenAction<Tscreen>>;

struct IDcMaxAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return settings.iDcMax; } };
template<typename Tscreen>
using IDcMaxChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETIDCMAX>, IDcMaxAccessor, SwitchScreenAction<Tscreen>>;

struct NMotMaxAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return settings.nMotMax; } };
template<typename Tscreen>
using NMotMaxChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETNMOTMAX>, NMotMaxAccessor, SwitchScreenAction<Tscreen>>;

struct FieldWeakMaxAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return settings.fieldWeakMax; } };
template<typename Tscreen>
using FieldWeakMaxChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETFIELDWEAKMAX>, FieldWeakMaxAccessor, SwitchScreenAction<Tscreen>>;

struct PhaseAdvMaxAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return settings.phaseAdvMax; } };
template<typename Tscreen>
using PhaseAdvMaxChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETPHASEADVMAX>, PhaseAdvMaxAccessor, SwitchScreenAction<Tscreen>>;

template<typename Tscreen>
class CommonSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_COMMONSETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_SETIMOTMAX>,      DefaultFont, DefaultColor, SwitchScreenAction<IMotMaxChangeScreen<CommonSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETIDCMAX>,       DefaultFont, DefaultColor, SwitchScreenAction<IDcMaxChangeScreen<CommonSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETNMOTMAX>,      DefaultFont, DefaultColor, SwitchScreenAction<NMotMaxChangeScreen<CommonSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETFIELDWEAKMAX>, DefaultFont, DefaultColor, SwitchScreenAction<FieldWeakMaxChangeScreen<CommonSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETPHASEADVMAX>,  DefaultFont, DefaultColor, SwitchScreenAction<PhaseAdvMaxChangeScreen<CommonSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETENABLED>,      DefaultFont, DefaultColor, SwitchScreenAction<EnableMenu<CommonSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETINVERTED>,     DefaultFont, DefaultColor, SwitchScreenAction<InvertMenu<CommonSettingsMenu<Tscreen>>>>   ,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,            DefaultFont, DefaultColor, SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
