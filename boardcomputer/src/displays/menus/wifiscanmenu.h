#pragma once

#include <vector>

#include <Arduino.h>
#include <WiFi.h>

#include "menudisplay.h"
#include "utils.h"
#include "actions/multiaction.h"
#include "actions/switchscreenaction.h"
#include "actions/dummyaction.h"
#include "icons/back.h"
#include "texts.h"

namespace {
class WifiSettingsMenu;
}

namespace {
class WifiScanMenu : public MenuDisplay
{
    using Base = MenuDisplay;

public:
    String text() const override;

    void start() override;
    void update() override;
    void stop() override;

    const std::reference_wrapper<MenuItem> *begin() const override { return &(*std::begin(refVec)); };
    const std::reference_wrapper<MenuItem> *end() const override { return &(*std::end(refVec)); };

private:
    makeComponent<MenuItem, StaticText<TEXT_BACK>, SwitchScreenAction<WifiSettingsMenu>, StaticMenuItemIcon<&icons::back>> m_backItem;

    std::vector<makeComponent<MenuItem, ChangeableText, DummyAction>> vec;

    std::vector<std::reference_wrapper<MenuItem>> refVec{{
        std::ref<MenuItem>(m_backItem)
    }};

    unsigned long m_lastScanComplete;
};

String WifiScanMenu::text() const
{
    auto text = String{vec.size()} + " found";
    switch (WiFi.scanComplete())
    {
    case WIFI_SCAN_RUNNING: text += " (scanning)"; break;
    case WIFI_SCAN_FAILED: text += " (error)"; break;
    }
    return text;
}

void WifiScanMenu::start()
{
    Base::start();

    m_lastScanComplete = 0;

    WiFi.scanNetworks(true);
}

void WifiScanMenu::update()
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
            {
                vec.back().stop();
                vec.pop_back();
            }

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

void WifiScanMenu::stop()
{
    WiFi.scanDelete();
}
}
