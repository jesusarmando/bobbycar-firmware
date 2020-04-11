#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
struct FrontFreqAccessor { static auto &getRef() { return front.command.buzzer.freq; } };
template<typename Tscreen>
using FrontFreqChangeScreen = ChangeValueDisplay<uint8_t, FrontFreqAccessor, Tscreen, TEXT_SETFRONTFREQ>;

struct FrontPatternAccessor { static auto &getRef() { return front.command.buzzer.pattern; } };
template<typename Tscreen>
using FrontPatternChangeScreen = ChangeValueDisplay<uint8_t, FrontPatternAccessor, Tscreen, TEXT_SETFRONTPATTERN>;

struct BackFreqAccessor { static auto &getRef() { return back.command.buzzer.freq; } };
template<typename Tscreen>
using BackFreqChangeScreen = ChangeValueDisplay<uint8_t, BackFreqAccessor, Tscreen, TEXT_SETBACKFREQ>;

struct BackPatternAccessor { static auto &getRef() { return back.command.buzzer.pattern; } };
template<typename Tscreen>
using BackPatternChangeScreen = ChangeValueDisplay<uint8_t, BackPatternAccessor, Tscreen, TEXT_SETBACKPATTERN>;

template<typename Tscreen>
class BuzzerMenu final :
    public StaticTitle<TEXT_BUZZER>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<FrontFreqChangeScreen<BuzzerMenu<Tscreen>>, TEXT_SETFRONTFREQ>,
        StaticSwitchScreenMenuItem<FrontPatternChangeScreen<BuzzerMenu<Tscreen>>, TEXT_SETFRONTPATTERN>,
        StaticSwitchScreenMenuItem<BackFreqChangeScreen<BuzzerMenu<Tscreen>>, TEXT_SETBACKFREQ>,
        StaticSwitchScreenMenuItem<BackPatternChangeScreen<BuzzerMenu<Tscreen>>, TEXT_SETBACKPATTERN>,
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
