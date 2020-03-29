#pragma once

#include "display.h"
#include "globals.h"
#include "texts.h"
#include "label.h"
#include "progressbar.h"

namespace {
template<typename Tscreen>
class CalibrateDisplay final : public Display
{
public:
    void start() override;
    void update() override;

    void button(bool pressed) override;

private:
    void redraw();

    bool m_pressed{};

    unsigned int m_lastRedraw{};

    Label<25, 50, 100, 25> m_label0;
    Label<25, 75, 100, 25> m_label1;
    Label<25, 100, 100, 25> m_label2;
    Label<25, 125, 100, 25> m_label3;
    ProgressBar<20, 200, 200, 10, 0, 1000> m_progressBar0;
    ProgressBar<20, 230, 200, 10, 0, 1000> m_progressBar1;
};

template<typename Tscreen>
void CalibrateDisplay<Tscreen>::start()
{
    m_pressed = false;

    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(TEXT_CALIBRATE, 5, 5, 4);

    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

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

    if (m_pressed)
        switchScreen<Tscreen>();
}

template<typename Tscreen>
void CalibrateDisplay<Tscreen>::button(bool pressed)
{
    if (!pressed)
        m_pressed = true;
}

template<typename Tscreen>
void CalibrateDisplay<Tscreen>::redraw()
{
    m_label0.repaint(gas);
    m_label1.repaint(brems);
    m_label2.repaint((long)raw_gas);
    m_label3.repaint((long)raw_brems);

    m_progressBar0.repaint(gas);
    m_progressBar1.repaint(brems);
}
}
