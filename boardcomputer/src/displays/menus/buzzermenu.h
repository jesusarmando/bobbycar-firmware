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
    public MenuDisplay,
    public StaticText<TEXT_BUZZER>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_SETFRONTFREQ>,    SwitchScreenAction<FrontFreqChangeScreen<BuzzerMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETFRONTPATTERN>, SwitchScreenAction<FrontPatternChangeScreen<BuzzerMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBACKFREQ>,     SwitchScreenAction<BackFreqChangeScreen<BuzzerMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBACKPATTERN>,  SwitchScreenAction<BackPatternChangeScreen<BuzzerMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,            SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
