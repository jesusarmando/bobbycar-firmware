#pragma once

#include <vector>

#include <Arduino.h>
#include <WiFi.h>
#include <WString.h>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "menuitems/dummymenuitem.h"
#include "texts.h"
#include "globals.h"

namespace {
template<typename Tscreen, const char *Ttext>
class EndScanMenuItem : public SwitchScreenMenuItem<Tscreen, Ttext>
{
    using Base = SwitchScreenMenuItem<Tscreen, Ttext>;

public:
    using Base::Base;

    void triggered() override;
};

template<typename Tscreen>
class WifiScanMenu final : public MenuDisplayInterface
{
    using Base = MenuDisplayInterface;

public:
    String title() const override { return String{TEXT_WIFISCAN} + ": " + WiFi.scanComplete(); }

    void start() override;
    void update() override;

    const std::reference_wrapper<MenuItemInterface> *begin() const override { return &(*std::begin(refVec)); };
    const std::reference_wrapper<MenuItemInterface> *end() const override { return &(*std::end(refVec)); };

private:
    EndScanMenuItem<Tscreen, TEXT_BACK> m_backItem;

    std::vector<DummyMenuItem> vec;

    std::vector<std::reference_wrapper<MenuItemInterface>> refVec{{
        std::ref<MenuItemInterface>(m_backItem)
    }};

    unsigned long m_lastScanComplete;
};

template<typename Tscreen>
void WifiScanMenu<Tscreen>::start()
{
    Base::start();

    m_lastScanComplete = 0;

    WiFi.scanNetworks(true);
}

template<typename Tscreen>
void WifiScanMenu<Tscreen>::update()
{
    const auto n = WiFi.scanComplete();
    if (n >= 0)
    {
        if (n != vec.size())
        {
            while (n > vec.size())
            {
                vec.emplace_back();
                vec.back().start();
            }

            while (n < vec.size())
                vec.pop_back();

            refVec.clear();
            for (auto &item : vec)
                refVec.emplace_back(std::ref(item));
            refVec.emplace_back(std::ref(m_backItem));
        }

        const auto now = millis();
        if (!m_lastScanComplete)
        {
            for (auto iter = std::begin(vec); iter != std::end(vec); iter++)
                iter->setTitle(WiFi.SSID(std::distance(std::begin(vec), iter)));

            m_lastScanComplete = now;
        }
        else if (now - m_lastScanComplete >= 1000)
        {
            m_lastScanComplete = 0;
            WiFi.scanNetworks(true);
        }
    }

    Base::update();
}

template<typename Tscreen, const char *Ttext>
void EndScanMenuItem<Tscreen, Ttext>::triggered()
{
    WiFi.scanDelete();
    Base::triggered();
}
}
