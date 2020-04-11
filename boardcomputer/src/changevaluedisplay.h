#pragma once

#include "display.h"
#include "label.h"
#include "globals.h"
#include "utils.h"
#include "texts.h"

namespace {
class ChangeValueDisplayInterface : public Display
{
public:
    void start() override;

    virtual const char *title() const = 0;

    ChangeValueDisplayInterface *asChangeValueDisplayInterface() override { return this; }
    const ChangeValueDisplayInterface *asChangeValueDisplayInterface() const override { return this; }

    virtual int value() const = 0;
    virtual void setValue(int value) = 0;

    virtual void confirm() = 0;

protected:
    Label<26, 81, 188, 53> m_label;
};

template<typename Tvalue, typename Taccessor, typename Tdisplay, const char *Ttext>
class ChangeValueDisplay final : public ChangeValueDisplayInterface
{
public:
    void start() override;
    void update() override;
    void redraw() override;

    void rotate(int offset) override;
    void button(bool pressed) override;

    const char *title() const override { return Ttext; }

    int value() const { return m_value; }
    void setValue(int value) { m_value = value; }

    void confirm() override;

private:
    Tvalue m_value{};

    int m_rotateOffset;
    bool m_pressed{};
};

void ChangeValueDisplayInterface::start()
{
    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);
    tft.setTextFont(4);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(title(), 5, 5);

    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    tft.drawRect(25, 75, 190, 65, TFT_WHITE);
    m_label.start();

    tft.setTextColor(TFT_WHITE);
    tft.drawString("Change value and", 10, 160);
    tft.drawString("press button to", 10, 185);
    tft.drawString("confirm and go", 10, 210);
    tft.drawString("back.", 10, 235);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextFont(7);
}

template<typename Tvalue, typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Taccessor, Tdisplay, Ttext>::start()
{
    m_value = Taccessor::getValue();

    m_rotateOffset = 0;
    m_pressed = false;

    ChangeValueDisplayInterface::start();
}

template<typename Tvalue, typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Taccessor, Tdisplay, Ttext>::update()
{
    if (!m_pressed)
    {
        const auto rotateOffset = m_rotateOffset;
        m_rotateOffset = 0;

        m_value += rotateOffset;
    }
    else
    {
        Taccessor::setValue(m_value);
        switchScreen<Tdisplay>();
    }
}

template<typename Tvalue, typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Taccessor, Tdisplay, Ttext>::redraw()
{
    m_label.redraw(String{m_value});
}

template<typename Tvalue, typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Taccessor, Tdisplay, Ttext>::rotate(int offset)
{
    m_rotateOffset += offset;
}

template<typename Tvalue, typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Taccessor, Tdisplay, Ttext>::button(bool pressed)
{
    if (!pressed)
        m_pressed = true;
}

template<typename Tvalue, typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Taccessor, Tdisplay, Ttext>::confirm()
{
    m_pressed = true;
}
}

#include "changevaluedisplay_bool.h"
#include "changevaluedisplay_controlmode.h"
#include "changevaluedisplay_controltype.h"
#include "changevaluedisplay_larsmmode_mode.h"
#include "changevaluedisplay_wifi_mode_t.h"
#include "changevaluedisplay_wifi_power_t.h"
