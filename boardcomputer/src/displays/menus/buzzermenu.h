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
struct FrontFreqAccessor
{
    static auto getValue() { return front.command.buzzer.freq; }
    template<typename T> static void setValue(T value) { front.command.buzzer.freq = value; }
};
struct FrontPatternAccessor
{
    static auto getValue() { return front.command.buzzer.pattern; }
    template<typename T> static void setValue(T value) { front.command.buzzer.pattern = value; }
};
struct BackFreqAccessor
{
    static auto getValue() { return back.command.buzzer.freq; }
    template<typename T> static void setValue(T value) { back.command.buzzer.freq = value; }
};
struct BackPatternAccessor
{
    static auto getValue() { return back.command.buzzer.pattern; }
    template<typename T> static void setValue(T value) { back.command.buzzer.pattern = value; }
};

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
