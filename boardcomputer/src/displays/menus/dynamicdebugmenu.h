#pragma once

#include <array>

#include <Arduino.h>
#include <WString.h>

#include "staticmenudisplay.h"
#include "menuitems/livestatusmenuitem.h"
#include "menuitems/staticdummymenuitem.h"
#include "menuitems/backmenuitem.h"
#include "texts.h"
#include "globals.h"

namespace {
class RandomTitle : public virtual TitleInterface
{
public:
    String title() const override { return m_title; }

protected:
    void updateTitle()
    {
        const auto now = millis();
        if (!m_nextUpdate || now >= m_nextUpdate)
        {
            m_title = String{"Dynamic text: "} + random(0, 100);
            m_nextUpdate = now + random(0, 1000);
        }
    }

private:
    unsigned long m_nextUpdate{};
    String m_title;
};

class DynamicTextMenuItem : public DummyMenuItem, public RandomTitle
{
    using Base = DummyMenuItem;

public:
    void update() override { Base::update(); updateTitle(); }
};

constexpr char TEXT_DYNAMICCOLOR[] = "Dynamic color";
class DynamicColorMenuItem : public DummyMenuItem, public StaticTitle<TEXT_DYNAMICCOLOR>
{
    using Base = DummyMenuItem;

public:
    void update() override
    {
        Base::update();
        const auto now = millis();
        if (!m_nextUpdate || now >= m_nextUpdate)
        {
            const auto count = std::distance(std::begin(default_4bit_palette), std::end(default_4bit_palette));
            m_color = default_4bit_palette[random(0, count)];
            m_nextUpdate = now + random(0, 1000);
        }
    }

    int color() const override { return m_color; }

private:
    unsigned long m_nextUpdate{};
    int m_color;
};

constexpr char TEXT_DYNAMICFONT[] = "Dynamic font";
class DynamicFontMenuItem : public DummyMenuItem, public StaticTitle<TEXT_DYNAMICFONT>
{
    using Base = DummyMenuItem;

public:
    void update() override
    {
        Base::update();
        const auto now = millis();
        if (!m_nextUpdate || now >= m_nextUpdate)
        {
            m_font = random(1, 5);
            m_nextUpdate = now + random(0, 1000);
        }
    }

    int font() const override { return m_font; }

private:
    unsigned long m_nextUpdate{};
    int m_font;
};

constexpr char TEXT_DUMMYITEM[] = "Dummy item";

template<typename Tscreen>
class DynamicDebugMenu final :
    public StaticMenuDisplay<
        DynamicTextMenuItem,
        DynamicColorMenuItem,
        DynamicFontMenuItem,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        BackMenuItem<Tscreen>
    >,
    public RandomTitle
{
    using Base = StaticMenuDisplay<
        DynamicTextMenuItem,
        DynamicColorMenuItem,
        DynamicFontMenuItem,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        StaticDummyMenuItem<TEXT_DUMMYITEM>,
        BackMenuItem<Tscreen>
    >;

public:
    void update() override { Base::update(); updateTitle(); }
};
}
