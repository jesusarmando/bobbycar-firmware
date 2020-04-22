#pragma once

#include <Arduino.h>

#include "demodisplay.h"
#include "actions/switchscreenaction.h"
#include "globals.h"
#include "bmsutils.h"
#include "widgets/label.h"

namespace {
class MainMenu;
class MetersDisplay;
class StatusDisplay;
}
namespace {
class BmsDisplay : public DemoDisplay, public SwitchScreenAction<MainMenu>
{
public:
    void initScreen() override;
    void redraw() override;

    void rotate(int offset) override;

    Label m_statusLabel{0, 0};

    Label m_voltageLabel{105, 50};
    Label m_currentLabel{105, 75};
    Label m_capacityLabel{105, 100};
    Label m_socLabel{105, 125};
    Label m_cycleLabel{105, 150};
    Label m_powerLabel{105, 175};

    std::array<Label, 12> m_battLabels{{
        Label{0, 225}, Label{60, 225}, Label{120, 225}, Label{180, 225},
        Label{0, 250}, Label{60, 250}, Label{120, 250}, Label{180, 250},
        Label{0, 275}, Label{60, 275}, Label{120, 275}, Label{180, 275}
    }};
};

void BmsDisplay::initScreen()
{
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.setTextFont(2);
    m_statusLabel.start();
    m_statusLabel.redraw("init");

    tft.setTextFont(4);
    tft.drawString("Voltage:", 0, 50);
    m_voltageLabel.start();
    tft.drawString("Current:", 0, 75);
    m_currentLabel.start();
    tft.drawString("Capacity:", 0, 100);
    m_capacityLabel.start();
    tft.drawString("SOC:", 0, 125);
    m_socLabel.start();
    tft.drawString("Cycle:", 0, 150);
    m_cycleLabel.start();
    tft.drawString("Power:", 0, 175);
    m_powerLabel.start();

    for (auto &label : m_battLabels)
        label.start();
}

void BmsDisplay::redraw()
{
    m_statusLabel.redraw(bluetoothSerial.hasClient() ? "connected" : "not connected");
    m_voltageLabel.redraw(String{bms::voltage} + 'V');
    m_currentLabel.redraw(String{bms::current} + 'A');
    m_capacityLabel.redraw(String{int(bms::capacity)} + "mAh");
    m_socLabel.redraw(String{bms::soc} + '%');
    m_cycleLabel.redraw(String{bms::cycle} + "AH");
    m_powerLabel.redraw(String{bms::power} + 'W');

    for (int i = 0; i < 12; i++)
        m_battLabels[i].redraw(String{bms::batt[i]});
}

void BmsDisplay::rotate(int offset)
{
    if (offset < 0)
        switchScreen<MetersDisplay>();
    else if (offset > 0)
        switchScreen<StatusDisplay>();
}
}
