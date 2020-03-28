#pragma once

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
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
class BuzzerMenu final : public MenuDisplay<
    TEXT_BUZZER,
    SwitchScreenMenuItem<FrontFreqChangeScreen<BuzzerMenu<Tscreen>>, TEXT_SETFRONTFREQ>,
    SwitchScreenMenuItem<FrontPatternChangeScreen<BuzzerMenu<Tscreen>>, TEXT_SETFRONTPATTERN>,
    SwitchScreenMenuItem<BackFreqChangeScreen<BuzzerMenu<Tscreen>>, TEXT_SETBACKFREQ>,
    SwitchScreenMenuItem<BackPatternChangeScreen<BuzzerMenu<Tscreen>>, TEXT_SETBACKPATTERN>,
    SwitchScreenMenuItem<Tscreen, TEXT_BACK>
>
{};
}
