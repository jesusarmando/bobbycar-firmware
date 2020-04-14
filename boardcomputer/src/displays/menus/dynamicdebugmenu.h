#pragma once

#include <Arduino.h>
#include <WString.h>

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "actions/dummyaction.h"
#include "actions/toggleboolaction.h"
#include "icons/lock.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "texts.h"

namespace {
class DebugMenu;
}

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

class RandomIcon : public virtual MenuItemIconInterface
{
public:
    const MenuItemIcon *icon() const override
    {
        const auto now = millis();
        if (!m_nextUpdate || now >= m_nextUpdate)
        {
            if (m_icon)
                m_icon = nullptr;
            else
                m_icon = &icons::lock;
            m_nextUpdate = now + random(0, 1000);
        }

        return m_icon;
    }

private:
    mutable unsigned long m_nextUpdate{};
    mutable const Icon<24, 24> *m_icon;
};

bool toggle;
struct ToggleAccessor : public virtual RefAccessor<bool>
{
public:
    bool &getRef() const override { return toggle; }
};

constexpr char TEXT_DUMMYITEM[] = "Dummy item";
constexpr char TEXT_DYNAMICCOLOR[] = "Dynamic color";
constexpr char TEXT_DYNAMICFONT[] = "Dynamic font";
constexpr char TEXT_DYNAMICICON[] = "Dynamic icon";
constexpr char TEXT_STATICICON[] = "Static icon";
constexpr char TEXT_DEBUGTOGGLE[] = "Toggle";

class DynamicDebugMenu :
    public MenuDisplay,
    public RandomText,
    public StaticMenuDefinition<
        // dummy items to allow for scrolling
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>,

        // the interesting bits
        makeComponent<MenuItem, RandomText,                    DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DYNAMICCOLOR>, RandomColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DYNAMICFONT>,  RandomFont, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DYNAMICICON>,  RandomIcon, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_STATICICON>,   StaticMenuItemIcon<&icons::lock>, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DEBUGTOGGLE>,  ToggleBoolAction, CheckboxIcon, ToggleAccessor>,
        makeComponent<MenuItem, RandomText,                    RandomColor, RandomFont, RandomIcon, DummyAction>,

        // more scrolling
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>,

        makeComponent<MenuItem, StaticText<TEXT_BACK>,         SwitchScreenAction<DebugMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
