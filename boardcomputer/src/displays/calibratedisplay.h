#pragma once

#include "demodisplay.h"
#include "display.h"
#include "globals.h"
#include "texts.h"
#include "label.h"
#include "progressbar.h"

namespace {
template<typename Tscreen>
class CalibrateDisplay final : public DemoDisplay<Tscreen>
{
    using Base = DemoDisplay<Tscreen>;

public:
    void start() override;
    void update() override;

private:
    void redraw();

    unsigned int m_lastRedraw{};

    Label<25, 50, 100, 23> m_label0;
    Label<25, 75, 100, 23> m_label1;
    Label<25, 100, 100, 23> m_label2;
    Label<25, 125, 100, 23> m_label3;
    ProgressBar<20, 200, 200, 10, 0, 1000> m_progressBar0;
    ProgressBar<20, 230, 200, 10, 0, 1000> m_progressBar1;
};

template<typename Tscreen>
void CalibrateDisplay<Tscreen>::start()
{
    Base::start();

    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(TEXT_CALIBRATE, 5, 5, 4);

    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    m_label0.start();
    m_label1.start();
    m_label2.start();
    m_label3.start();

    m_progressBar0.start();
    m_progressBar1.start();
}

template<typename Tscreen>
void CalibrateDisplay<Tscreen>::update()
{
    const auto now = millis();
    if (!m_lastRedraw || now - m_lastRedraw >= 1000/60)
    {
        redraw();
        m_lastRedraw = now;
    }

    Base::update();
}

template<typename Tscreen>
void CalibrateDisplay<Tscreen>::redraw()
{
    m_label0.repaint(String{gas});
    m_label1.repaint(String{brems});
    m_label2.repaint(String{raw_gas});
    m_label3.repaint(String{raw_brems});

    m_progressBar0.repaint(gas);
    m_progressBar1.repaint(brems);
}
}
