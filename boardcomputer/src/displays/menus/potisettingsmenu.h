#pragma once

#include "staticmenudisplay.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "displays/calibratedisplay.h"
#include "texts.h"
#include "globals.h"

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
template<typename Tscreen>
using GasMinChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETGASMIN>, GasMinAccessor, SwitchScreenAction<Tscreen>>;

struct GasMaxAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return gasMax; } };
template<typename Tscreen>
using GasMaxChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETGASMAX>, GasMaxAccessor, SwitchScreenAction<Tscreen>>;

struct BremsMinAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return bremsMin; } };
template<typename Tscreen>
using BremsMinChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETBREMSMIN>, BremsMinAccessor, SwitchScreenAction<Tscreen>>;

struct BremsMaxAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return bremsMax; } };
template<typename Tscreen>
using BremsMaxChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETBREMSMAX>, BremsMaxAccessor, SwitchScreenAction<Tscreen>>;

template<typename Tscreen>
class PotiSettingsMenu :
    public StaticText<TEXT_POTISETTINGS>,
    public StaticMenuDisplay<
        makeComponent<MenuItem, GasText,                      DefaultFont, DisabledColor, DummyAction>,
        makeComponent<MenuItem, BremsText,                    DefaultFont, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_CALIBRATE>,   DefaultFont, DefaultColor,    SwitchScreenAction<CalibrateDisplay<PotiSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGASMIN>,   DefaultFont, DefaultColor,    SwitchScreenAction<GasMinChangeScreen<PotiSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGASMAX>,   DefaultFont, DefaultColor,    SwitchScreenAction<GasMaxChangeScreen<PotiSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBREMSMIN>, DefaultFont, DefaultColor,    SwitchScreenAction<BremsMinChangeScreen<PotiSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBREMSMAX>, DefaultFont, DefaultColor,    SwitchScreenAction<BremsMaxChangeScreen<PotiSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,        DefaultFont, DefaultColor,    SwitchScreenAction<Tscreen>>
    >
{};
}
