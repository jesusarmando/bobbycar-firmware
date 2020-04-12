#pragma once

#include <array>

#include <WString.h>

#include "demodisplay.h"
#include "display.h"
#include "globals.h"
#include "texts.h"
#include "label.h"
#include "progressbar.h"
#include "modes/ignoreinputmode.h"

namespace {
template<typename Tscreen>
class CalibrateDisplay : public DemoDisplay<Tscreen>
{
    using Base = DemoDisplay<Tscreen>;

public:
    void start() override;
    void redraw() override;
    void stop() override;

private:
    ModeInterface *m_oldMode;
    IgnoreInputMode m_mode{0, ControlType::FieldOrientedControl, ControlMode::Torque};

    std::array<Label, 4> m_labels {{
        Label{25, 50, 100, 23},
        Label{25, 75, 100, 23},
        Label{25, 100, 100, 23},
        Label{25, 125, 100, 23}
    }};

    ProgressBar<20, 200, 200, 10, 0, 1000> m_progressBar0;
    ProgressBar<20, 230, 200, 10, 0, 1000> m_progressBar1;
};

template<typename Tscreen>
void CalibrateDisplay<Tscreen>::start()
{
    Base::start();

    m_oldMode = currentMode;
    currentMode = &m_mode;

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

template<typename Tscreen>
void CalibrateDisplay<Tscreen>::redraw()
{
    m_labels[0].redraw(String{gas});
    m_labels[1].redraw(String{raw_gas});

    m_labels[2].redraw(String{brems});
    m_labels[3].redraw(String{raw_brems});

    m_progressBar0.redraw(gas);
    m_progressBar1.redraw(brems);
}

template<typename Tscreen>
void CalibrateDisplay<Tscreen>::stop()
{
    Base::stop();

    if (currentMode == &m_mode)
        currentMode = m_oldMode;
}
}
