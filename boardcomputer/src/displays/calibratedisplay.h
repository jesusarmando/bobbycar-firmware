#pragma once

#include <array>

#include <WString.h>

#include "demodisplay.h"
#include "actions/switchscreenaction.h"
#include "globals.h"
#include "texts.h"
#include "label.h"
#include "progressbar.h"
#include "modes/ignoreinputmode.h"

namespace {
class PotiSettingsMenu;
}

namespace {
class CalibrateDisplay : public DemoDisplay, public SwitchScreenAction<PotiSettingsMenu>
{
    using Base = DemoDisplay;

public:
    void start() override;
    void initScreen() override;
    void redraw() override;
    void stop() override;

private:
    ModeInterface *m_oldMode;
    IgnoreInputMode m_mode{0, ControlType::FieldOrientedControl, ControlMode::Torque};

    std::array<Label, 4> m_labels {{
        Label{25, 50}, // 100, 23
        Label{25, 75}, // 100, 23
        Label{25, 100}, // 100, 23
        Label{25, 125} // 100, 23
    }};

    ProgressBar m_progressBar0{20, 200, 200, 10, 0, 1000};
    ProgressBar m_progressBar1{20, 230, 200, 10, 0, 1000};
};

void CalibrateDisplay::start()
{
    Base::start();

    m_oldMode = currentMode;
    currentMode = &m_mode;
}

void CalibrateDisplay::initScreen()
{
    tft.fillScreen(TFT_BLACK);
    tft.setTextFont(4);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(TEXT_CALIBRATE, 5, 5, 4);

    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    for (auto &label : m_labels)
        label.start();

    m_progressBar0.start();
    m_progressBar1.start();
}

void CalibrateDisplay::redraw()
{
    m_labels[0].redraw(String{gas});
    m_labels[1].redraw(String{raw_gas});

    m_labels[2].redraw(String{brems});
    m_labels[3].redraw(String{raw_brems});

    m_progressBar0.redraw(gas);
    m_progressBar1.redraw(brems);
}

void CalibrateDisplay::stop()
{
    Base::stop();

    if (currentMode == &m_mode)
        currentMode = m_oldMode;
}
}
