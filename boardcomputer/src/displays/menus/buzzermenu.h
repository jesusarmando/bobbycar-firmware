#pragma once

#include "staticmenudisplay.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "globals.h"

namespace {
struct FrontFreqAccessor : public RefAccessor<uint8_t> { uint8_t &getRef() const override { return front.command.buzzer.freq; } };
template<typename Tscreen>
using FrontFreqChangeScreen = makeComponent<ChangeValueDisplay<uint8_t>, StaticText<TEXT_SETFRONTFREQ>, FrontFreqAccessor, SwitchScreenAction<Tscreen>>;

struct FrontPatternAccessor : public RefAccessor<uint8_t> { uint8_t &getRef() const override { return front.command.buzzer.pattern; } };
template<typename Tscreen>
using FrontPatternChangeScreen = makeComponent<ChangeValueDisplay<uint8_t>, StaticText<TEXT_SETFRONTPATTERN>, FrontPatternAccessor, SwitchScreenAction<Tscreen>>;

struct BackFreqAccessor : public RefAccessor<uint8_t> { uint8_t &getRef() const override { return back.command.buzzer.freq; } };
template<typename Tscreen>
using BackFreqChangeScreen = makeComponent<ChangeValueDisplay<uint8_t>, StaticText<TEXT_SETBACKFREQ>, BackFreqAccessor, SwitchScreenAction<Tscreen>>;

struct BackPatternAccessor : public RefAccessor<uint8_t> { uint8_t &getRef() const override { return back.command.buzzer.pattern; } };
template<typename Tscreen>
using BackPatternChangeScreen = makeComponent<ChangeValueDisplay<uint8_t>, StaticText<TEXT_SETBACKPATTERN>, BackPatternAccessor, SwitchScreenAction<Tscreen>>;

template<typename Tscreen>
class BuzzerMenu :
    public StaticText<TEXT_BUZZER>,
    public StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_SETFRONTFREQ>,    DefaultFont, DefaultColor, SwitchScreenAction<FrontFreqChangeScreen<BuzzerMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETFRONTPATTERN>, DefaultFont, DefaultColor, SwitchScreenAction<FrontPatternChangeScreen<BuzzerMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBACKFREQ>,     DefaultFont, DefaultColor, SwitchScreenAction<BackFreqChangeScreen<BuzzerMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBACKPATTERN>,  DefaultFont, DefaultColor, SwitchScreenAction<BackPatternChangeScreen<BuzzerMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,            DefaultFont, DefaultColor, SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
