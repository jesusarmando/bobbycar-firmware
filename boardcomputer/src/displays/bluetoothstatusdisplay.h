#pragma once

#include "demodisplay.h"
#include "label.h"
#include "globals.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class BluetoothStatusDisplay final : public DemoDisplay<Tscreen>
{
    using Base = DemoDisplay<Tscreen>;

public:
    void start() override;
    void update() override;

private:
    void redraw();

    Label<150, 50, 100, 23> m_label0;
    Label<150, 75, 100, 23> m_label1;
    Label<150, 100, 100, 23> m_label2;
    Label<150, 125, 100, 23> m_label3;
};

template<typename Tscreen>
void BluetoothStatusDisplay<Tscreen>::start()
{
    Base::start();

    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(TEXT_BLUETOOTHSTATUS, 5, 5, 4);

    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.drawString("available:", 0, 50, 4);
    m_label0.start();
    tft.drawString("hasClient:", 0, 75, 4);
    m_label1.start();
    tft.drawString("connected", 0, 100, 4);
    m_label2.start();
    tft.drawString("isReady", 0, 125, 4);
    m_label3.start();
}

template<typename Tscreen>
void BluetoothStatusDisplay<Tscreen>::update()
{
    redraw();

    Base::update();
}

template<typename Tscreen>
void BluetoothStatusDisplay<Tscreen>::redraw()
{
    m_label0.repaint(String{bluetoothSerial.available()});
    m_label1.repaint(bluetoothSerial.hasClient() ? "true" : "false");
    m_label2.repaint(bluetoothSerial.connected() ? "true" : "false");
    m_label3.repaint(bluetoothSerial.isReady() ? "true" : "false");
}
}
