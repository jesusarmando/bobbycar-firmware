#pragma once

#include <array>

#include <Arduino.h>
#include <WString.h>

#include "staticmenudisplay.h"
#include "utils.h"
#include "menuitem.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "icons/lock.h"
#include "texts.h"

namespace {
class RandomText : public virtual TextInterface
{
public:
    String text() const override
    {
        const auto now = millis();
        if (!m_nextUpdate || now >= m_nextUpdate)
        {
            m_title = String{"Dynamic text: "} + random(0, 100);
            m_nextUpdate = now + random(0, 1000);
        }

        return m_title;
    }

private:
    mutable unsigned long m_nextUpdate{};
    mutable String m_title;
};

class RandomColor : public virtual ColorInterface
{
public:
    int color() const override
    {
        const auto now = millis();
        if (!m_nextUpdate || now >= m_nextUpdate)
        {
            const auto count = std::distance(std::begin(default_4bit_palette), std::end(default_4bit_palette));
            m_color = default_4bit_palette[random(0, count)];
            m_nextUpdate = now + random(0, 1000);
        }

        return m_color;
    }

private:
    mutable unsigned long m_nextUpdate{};
    mutable int m_color;
};

class RandomFont : public virtual FontInterface
{
public:
    int font() const override
    {
        const auto now = millis();
        if (!m_nextUpdate || now >= m_nextUpdate)
        {
            m_font = random(1, 5);
            m_nextUpdate = now + random(0, 1000);
        }

        return m_font;
    }

private:
    mutable unsigned long m_nextUpdate{};
    mutable int m_font;
};

class StaticLockIcon : public virtual IconInterface<24, 24>
{
public:
    const Icon<24, 24> *icon() const override { return &icons::lock; }
};

constexpr char TEXT_DUMMYITEM[] = "Dummy item";
constexpr char TEXT_DYNAMICCOLOR[] = "Dynamic color";
constexpr char TEXT_DYNAMICFONT[] = "Dynamic font";
constexpr char TEXT_ITEMWITHICON[] = "Item with icon";

template<typename Tscreen>
class DynamicDebugMenu :
    public StaticMenuDisplay<
        // some padding to allow for scrolling
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DefaultFont, DefaultColor, DummyAction>,

        // now the interesting bits
        makeComponent<MenuItem, RandomText,                    DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DYNAMICCOLOR>, DefaultFont, RandomColor,  DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DYNAMICFONT>,  RandomFont,  DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_ITEMWITHICON>, DefaultFont, DefaultColor, DummyAction, StaticLockIcon>,

        // more padding
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DefaultFont, DefaultColor, DummyAction>,

        makeComponent<MenuItem, StaticText<TEXT_BACK>,         DefaultFont, DefaultColor, SwitchScreenAction<Tscreen>>
    >,
    public RandomText
{};
}
