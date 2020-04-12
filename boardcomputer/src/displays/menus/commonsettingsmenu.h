#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "menuitems/backmenuitem.h"
#include "changevaluedisplay.h"
#include "displays/menus/enablemenu.h"
#include "displays/menus/invertmenu.h"
#include "texts.h"
#include "globals.h"

namespace {
struct IMotMaxAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return settings.iMotMax; } };
template<typename Tscreen>
class IMotMaxChangeScreen :
    public StaticTitle<TEXT_SETIMOTMAX>,
    public ChangeValueDisplay<int16_t>,
    public IMotMaxAccessor,
    public  SwitchScreenAction<Tscreen>
{};

struct IDcMaxAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return settings.iDcMax; } };
template<typename Tscreen>
class IDcMaxChangeScreen :
    public StaticTitle<TEXT_SETIDCMAX>,
    public ChangeValueDisplay<int16_t>,
    public IDcMaxAccessor,
    public SwitchScreenAction<Tscreen>
{};

struct NMotMaxAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return settings.nMotMax; } };
template<typename Tscreen>
class NMotMaxChangeScreen :
    public StaticTitle<TEXT_SETNMOTMAX>,
    public ChangeValueDisplay<int16_t>,
    public NMotMaxAccessor,
    public SwitchScreenAction<Tscreen>
{};

struct FieldWeakMaxAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return settings.fieldWeakMax; } };
template<typename Tscreen>
class FieldWeakMaxChangeScreen :
    public StaticTitle<TEXT_SETFIELDWEAKMAX>,
    public ChangeValueDisplay<int16_t>,
    public FieldWeakMaxAccessor,
    public SwitchScreenAction<Tscreen>
{};

struct PhaseAdvMaxAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return settings.phaseAdvMax; } };
template<typename Tscreen>
class PhaseAdvMaxChangeScreen :
    public StaticTitle<TEXT_SETPHASEADVMAX>,
    public ChangeValueDisplay<int16_t>,
    public PhaseAdvMaxAccessor,
    public SwitchScreenAction<Tscreen>
{};

template<typename Tscreen>
class CommonSettingsMenu final :
    public StaticTitle<TEXT_COMMONSETTINGS>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<IMotMaxChangeScreen<CommonSettingsMenu<Tscreen>>, TEXT_SETIMOTMAX>,
        StaticSwitchScreenMenuItem<IDcMaxChangeScreen<CommonSettingsMenu<Tscreen>>, TEXT_SETIDCMAX>,
        StaticSwitchScreenMenuItem<NMotMaxChangeScreen<CommonSettingsMenu<Tscreen>>, TEXT_SETNMOTMAX>,
        StaticSwitchScreenMenuItem<FieldWeakMaxChangeScreen<CommonSettingsMenu<Tscreen>>, TEXT_SETFIELDWEAKMAX>,
        StaticSwitchScreenMenuItem<PhaseAdvMaxChangeScreen<CommonSettingsMenu<Tscreen>>, TEXT_SETPHASEADVMAX>,
        StaticSwitchScreenMenuItem<EnableMenu<CommonSettingsMenu<Tscreen>>, TEXT_SETENABLED>,
        StaticSwitchScreenMenuItem<InvertMenu<CommonSettingsMenu<Tscreen>>, TEXT_SETINVERTED>,
        BackMenuItem<Tscreen>
    >
{};
}
