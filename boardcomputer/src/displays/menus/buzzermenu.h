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
class BuzzerMenu;
class SettingsMenu;
}

namespace {
struct FrontFreqAccessor : public RefAccessor<uint8_t> { uint8_t &getRef() const override { return front.command.buzzer.freq; } };
using FrontFreqChangeScreen = makeComponent<ChangeValueDisplay<uint8_t>, StaticText<TEXT_SETFRONTFREQ>, FrontFreqAccessor, SwitchScreenAction<BuzzerMenu>>;

struct FrontPatternAccessor : public RefAccessor<uint8_t> { uint8_t &getRef() const override { return front.command.buzzer.pattern; } };
using FrontPatternChangeScreen = makeComponent<ChangeValueDisplay<uint8_t>, StaticText<TEXT_SETFRONTPATTERN>, FrontPatternAccessor, SwitchScreenAction<BuzzerMenu>>;

struct BackFreqAccessor : public RefAccessor<uint8_t> { uint8_t &getRef() const override { return back.command.buzzer.freq; } };
using BackFreqChangeScreen = makeComponent<ChangeValueDisplay<uint8_t>, StaticText<TEXT_SETBACKFREQ>, BackFreqAccessor, SwitchScreenAction<BuzzerMenu>>;

struct BackPatternAccessor : public RefAccessor<uint8_t> { uint8_t &getRef() const override { return back.command.buzzer.pattern; } };
using BackPatternChangeScreen = makeComponent<ChangeValueDisplay<uint8_t>, StaticText<TEXT_SETBACKPATTERN>, BackPatternAccessor, SwitchScreenAction<BuzzerMenu>>;

class BuzzerMenu :
    public MenuDisplay,
    public StaticText<TEXT_BUZZER>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_SETFRONTFREQ>,    SwitchScreenAction<FrontFreqChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETFRONTPATTERN>, SwitchScreenAction<FrontPatternChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBACKFREQ>,     SwitchScreenAction<BackFreqChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBACKPATTERN>,  SwitchScreenAction<BackPatternChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,            SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
