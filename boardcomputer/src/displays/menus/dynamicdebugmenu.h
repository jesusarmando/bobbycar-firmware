#pragma once

#include <array>

#include <Arduino.h>
#include <WString.h>

#include "staticmenudisplay.h"
#include "menuitems/livestatusmenuitem.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "texts.h"
#include "globals.h"

namespace {
struct RandomNumberLiveStatus { static String getText() { return String{"random: "} + random(0, 100); } };

template<typename Tscreen>
class DynamicDebugMenu final : public StaticMenuDisplay<
    LiveStatusMenuItem<RandomNumberLiveStatus>,
    StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
>
{
    using Base = StaticMenuDisplay<
        LiveStatusMenuItem<RandomNumberLiveStatus>,
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >;

public:
    String title() const override { return m_title; }

    void start() override;
    void update() override;

private:
    void updateTitle();

    unsigned long m_lastUpdate;
    String m_title;
};

template<typename Tscreen>
void DynamicDebugMenu<Tscreen>::start()
{
    Base::start();
    updateTitle();
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
