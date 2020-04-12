#pragma once

#include "staticmenudisplay.h"
#include "menuitems/livestatusmenuitem.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "menuitems/backmenuitem.h"
#include "changevaluedisplay.h"
#include "displays/calibratedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
struct GasLiveStatus { static String getText() { return String{"gas: "} + raw_gas + ": " + gas; } };
struct BremsLiveStatus { static String getText() { return String{"brems: "} + raw_brems + ": " + brems; } };

struct GasMinAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return gasMin; } };
template<typename Tscreen>
class GasMinChangeScreen :
    public StaticTitle<TEXT_SETGASMIN>,
    public ChangeValueDisplay<int16_t>,
    public GasMinAccessor,
    public SwitchScreenAction<Tscreen>
{};

struct GasMaxAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return gasMax; } };
template<typename Tscreen>
class GasMaxChangeScreen :
    public StaticTitle<TEXT_SETGASMAX>,
    public ChangeValueDisplay<int16_t>,
    public GasMaxAccessor,
    public SwitchScreenAction<Tscreen>
{};

struct BremsMinAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return bremsMin; } };
template<typename Tscreen>
class BremsMinChangeScreen :
    public StaticTitle<TEXT_SETBREMSMIN>,
    public ChangeValueDisplay<int16_t>,
    public BremsMinAccessor,
    public SwitchScreenAction<Tscreen>
{};

struct BremsMaxAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return bremsMax; } };
template<typename Tscreen>
class BremsMaxChangeScreen :
    public StaticTitle<TEXT_SETBREMSMAX>,
    public ChangeValueDisplay<int16_t>,
    public BremsMaxAccessor,
    public SwitchScreenAction<Tscreen>
{};

template<typename Tscreen>
class PotiSettingsMenu final :
    public StaticTitle<TEXT_POTISETTINGS>,
    public StaticMenuDisplay<
        LiveStatusMenuItem<GasLiveStatus>,
        LiveStatusMenuItem<BremsLiveStatus>,
        StaticSwitchScreenMenuItem<GasMinChangeScreen<PotiSettingsMenu<Tscreen>>, TEXT_SETGASMIN>,
        StaticSwitchScreenMenuItem<GasMaxChangeScreen<PotiSettingsMenu<Tscreen>>, TEXT_SETGASMAX>,
        StaticSwitchScreenMenuItem<BremsMinChangeScreen<PotiSettingsMenu<Tscreen>>, TEXT_SETBREMSMIN>,
        StaticSwitchScreenMenuItem<BremsMaxChangeScreen<PotiSettingsMenu<Tscreen>>, TEXT_SETBREMSMAX>,
        StaticSwitchScreenMenuItem<CalibrateDisplay<PotiSettingsMenu<Tscreen>>, TEXT_CALIBRATE>,
        BackMenuItem<Tscreen>
    >
{};
}
