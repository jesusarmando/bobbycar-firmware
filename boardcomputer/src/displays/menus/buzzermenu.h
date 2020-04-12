#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "menuitems/backmenuitem.h"
#include "changevaluedisplay.h"
#include "actions/switchscreenaction.h"
#include "texts.h"
#include "globals.h"

namespace {
struct FrontFreqAccessor : public RefAccessor<uint8_t> { uint8_t &getRef() const override { return front.command.buzzer.freq; } };
template<typename Tscreen>
class FrontFreqChangeScreen :
    public StaticTitle<TEXT_SETFRONTFREQ>,
    public ChangeValueDisplay<uint8_t>,
    public FrontFreqAccessor,
    public SwitchScreenAction<Tscreen>
{};

struct FrontPatternAccessor : public RefAccessor<uint8_t> { uint8_t &getRef() const override { return front.command.buzzer.pattern; } };
template<typename Tscreen>
class FrontPatternChangeScreen :
    public StaticTitle<TEXT_SETFRONTPATTERN>,
    public ChangeValueDisplay<uint8_t>,
    public FrontPatternAccessor,
    public SwitchScreenAction<Tscreen>
{};

struct BackFreqAccessor : public RefAccessor<uint8_t> { uint8_t &getRef() const override { return back.command.buzzer.freq; } };
template<typename Tscreen>
class BackFreqChangeScreen :
    public StaticTitle<TEXT_SETBACKFREQ>,
    public ChangeValueDisplay<uint8_t>,
    public BackFreqAccessor,
    public SwitchScreenAction<Tscreen>
{};

struct BackPatternAccessor : public RefAccessor<uint8_t> { uint8_t &getRef() const override { return back.command.buzzer.pattern; } };
template<typename Tscreen>
class BackPatternChangeScreen :
    public StaticTitle<TEXT_SETBACKPATTERN>,
    public ChangeValueDisplay<uint8_t>,
    public BackPatternAccessor,
    public SwitchScreenAction<Tscreen>
{};

template<typename Tscreen>
class BuzzerMenu final :
    public StaticTitle<TEXT_BUZZER>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<FrontFreqChangeScreen<BuzzerMenu<Tscreen>>, TEXT_SETFRONTFREQ>,
        StaticSwitchScreenMenuItem<FrontPatternChangeScreen<BuzzerMenu<Tscreen>>, TEXT_SETFRONTPATTERN>,
        StaticSwitchScreenMenuItem<BackFreqChangeScreen<BuzzerMenu<Tscreen>>, TEXT_SETBACKFREQ>,
        StaticSwitchScreenMenuItem<BackPatternChangeScreen<BuzzerMenu<Tscreen>>, TEXT_SETBACKPATTERN>,
        BackMenuItem<Tscreen>
    >
{};
}
