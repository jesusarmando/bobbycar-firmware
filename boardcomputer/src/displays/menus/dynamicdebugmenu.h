#pragma once

#include <array>

#include <Arduino.h>
#include <WString.h>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "texts.h"
#include "globals.h"

namespace {
class DynamicMenuGasItem final : public MenuItemInterface
{
public:
    String title() const override { return String("gas: ") + gas; }
    void triggered() override {}
};

class DynamicMenuBremsItem final : public MenuItemInterface
{
public:
    String title() const override { return String("brems: ") + brems; }
    void triggered() override {}
};

class DynamicMenuRandomItem final : public MenuItemInterface
{
    using Base = MenuItemInterface;

public:
    String title() const override { return m_title; }
    void start() override { MenuItemInterface::start(); updateTitle(); }
    void update() override;
    void triggered() override {}

private:
    void updateTitle();

    unsigned long m_lastUpdate;
    String m_title;
};

template<typename Tscreen>
class DynamicDebugMenu final : public MenuDisplayInterface
{
    using Base = MenuDisplayInterface;

public:
    String title() const override { return m_title; }

    void start() override { MenuDisplayInterface::start(); updateTitle(); }
    void update() override;

    const std::reference_wrapper<MenuItemInterface> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItemInterface> *end() const override { return std::end(arr); };

private:
    void updateTitle();

    unsigned long m_lastUpdate;
    String m_title;

    DynamicMenuGasItem m_dynamicMenuGasItem;
    DynamicMenuBremsItem m_dynamicMenuBremsItem;
    DynamicMenuRandomItem m_dynamicMenuRandomItem;
    SwitchScreenMenuItem<Tscreen, TEXT_BACK> m_backItem;

    const std::array<std::reference_wrapper<MenuItemInterface>, 4> arr{{
        std::ref<MenuItemInterface>(m_dynamicMenuGasItem),
        std::ref<MenuItemInterface>(m_dynamicMenuBremsItem),
        std::ref<MenuItemInterface>(m_dynamicMenuRandomItem),
        std::ref<MenuItemInterface>(m_backItem)
    }};
};

void DynamicMenuRandomItem::update()
{
    Base::update();

    if (millis() - m_lastUpdate >= 100)
        updateTitle();
}

void DynamicMenuRandomItem::updateTitle()
{
    m_title = String{"random: "} + random(0, 100);
    m_lastUpdate = millis();
}

template<typename Tscreen>
void DynamicDebugMenu<Tscreen>::update()
{
    Base::update();

    if (millis() - m_lastUpdate >= 500)
        updateTitle();
}

template<typename Tscreen>
void DynamicDebugMenu<Tscreen>::updateTitle()
{
    m_title = String{TEXT_DYNAMICMENU} + ": " + random(0, 100);
    m_lastUpdate = millis();
}
}
