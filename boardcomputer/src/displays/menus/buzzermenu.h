#pragma once

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
class MainMenu;
}

namespace {
struct FrontFreqAccessor { static auto &getRef() { return front.command.buzzer.freq; } };
struct FrontPatternAccessor { static auto &getRef() { return front.command.buzzer.pattern; } };
struct BackFreqAccessor { static auto &getRef() { return back.command.buzzer.freq; } };
struct BackPatternAccessor { static auto &getRef() { return back.command.buzzer.pattern; } };

class BuzzerMenu final : public MenuDisplay<
    TEXT_BUZZER,
    SwitchScreenMenuItem<ChangeValueDisplay<uint8_t, FrontFreqAccessor, BuzzerMenu, TEXT_SETFRONTFREQ>, TEXT_SETFRONTFREQ>,
    SwitchScreenMenuItem<ChangeValueDisplay<uint8_t, FrontPatternAccessor, BuzzerMenu, TEXT_SETFRONTPATTERN>, TEXT_SETFRONTPATTERN>,
    SwitchScreenMenuItem<ChangeValueDisplay<uint8_t, BackFreqAccessor, BuzzerMenu, TEXT_SETBACKFREQ>, TEXT_SETBACKFREQ>,
    SwitchScreenMenuItem<ChangeValueDisplay<uint8_t, BackPatternAccessor, BuzzerMenu, TEXT_SETBACKPATTERN>, TEXT_SETBACKPATTERN>,
    SwitchScreenMenuItem<MainMenu, TEXT_BACK>
>
{};
}
