#pragma once

#include "display.h"
#include "label.h"
#include "globals.h"
#include "utils.h"
#include "texts.h"
#include "staticmenudisplay.h"
#include "menuitems/setvaluemenuitem.h"
#include "menuitems/staticswitchscreenmenuitem.h"

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
    Label<26, 81, 188, 53, 7> m_label;
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

template<typename Taccessor, typename Tdisplay, const char *Ttext>
class ChangeValueDisplay<bool, Taccessor, Tdisplay, Ttext> final :
    public StaticTitle<Ttext>,
    public StaticMenuDisplay<
        SetValueMenuItem<bool, Taccessor, true, Tdisplay, TEXT_TRUE>,
        SetValueMenuItem<bool, Taccessor, false, Tdisplay, TEXT_FALSE>,
        StaticSwitchScreenMenuItem<Tdisplay, TEXT_BACK>
    >
{
    using Base = StaticMenuDisplay<
        SetValueMenuItem<bool, Taccessor, true, Tdisplay, TEXT_TRUE>,
        SetValueMenuItem<bool, Taccessor, false, Tdisplay, TEXT_FALSE>,
        StaticSwitchScreenMenuItem<Tdisplay, TEXT_BACK>
    >;

public:
    void start() override;
};

template<typename Taccessor, typename Tdisplay, const char *Ttext>
class ChangeValueDisplay<ControlMode, Taccessor, Tdisplay, Ttext> final :
    public StaticTitle<Ttext>,
    public StaticMenuDisplay<
        SetValueMenuItem<ControlMode, Taccessor, ControlMode::OpenMode, Tdisplay, TEXT_OPENMODE>,
        SetValueMenuItem<ControlMode, Taccessor, ControlMode::Voltage, Tdisplay, TEXT_VOLTAGE>,
        SetValueMenuItem<ControlMode, Taccessor, ControlMode::Speed, Tdisplay, TEXT_SPEED>,
        SetValueMenuItem<ControlMode, Taccessor, ControlMode::Torque, Tdisplay, TEXT_TORQUE>,
        StaticSwitchScreenMenuItem<Tdisplay, TEXT_BACK>
    >
{
    using Base = StaticMenuDisplay<
        SetValueMenuItem<ControlMode, Taccessor, ControlMode::OpenMode, Tdisplay, TEXT_OPENMODE>,
        SetValueMenuItem<ControlMode, Taccessor, ControlMode::Voltage, Tdisplay, TEXT_VOLTAGE>,
        SetValueMenuItem<ControlMode, Taccessor, ControlMode::Speed, Tdisplay, TEXT_SPEED>,
        SetValueMenuItem<ControlMode, Taccessor, ControlMode::Torque, Tdisplay, TEXT_TORQUE>,
        StaticSwitchScreenMenuItem<Tdisplay, TEXT_BACK>
    >;

public:
    void start() override;
};


template<typename Taccessor, typename Tdisplay, const char *Ttext>
class ChangeValueDisplay<ControlType, Taccessor, Tdisplay, Ttext> final :
    public StaticTitle<Ttext>,
    public StaticMenuDisplay<
        SetValueMenuItem<ControlType, Taccessor, ControlType::Commutation, Tdisplay, TEXT_COMMUTATION>,
        SetValueMenuItem<ControlType, Taccessor, ControlType::Sinusoidal, Tdisplay, TEXT_SINUSOIDAL>,
        SetValueMenuItem<ControlType, Taccessor, ControlType::FieldOrientedControl, Tdisplay, TEXT_FIELDORIENTEDCONTROL>,
        StaticSwitchScreenMenuItem<Tdisplay, TEXT_BACK>
    >
{
    using Base = StaticMenuDisplay<
        SetValueMenuItem<ControlType, Taccessor, ControlType::Commutation, Tdisplay, TEXT_COMMUTATION>,
        SetValueMenuItem<ControlType, Taccessor, ControlType::Sinusoidal, Tdisplay, TEXT_SINUSOIDAL>,
        SetValueMenuItem<ControlType, Taccessor, ControlType::FieldOrientedControl, Tdisplay, TEXT_FIELDORIENTEDCONTROL>,
        StaticSwitchScreenMenuItem<Tdisplay, TEXT_BACK>
    >;

public:
    void start() override;
};

void ChangeValueDisplayInterface::start()
{
    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(title(), 5, 5, 4);

    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    tft.drawRect(25, 75, 190, 65, TFT_WHITE);
    m_label.start();

    tft.setTextColor(TFT_WHITE);
    tft.drawString("Change value and", 10, 160, 4);
    tft.drawString("press button to", 10, 185, 4);
    tft.drawString("confirm and go", 10, 210, 4);
    tft.drawString("back.", 10, 235, 4);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
}

template<typename Tvalue, typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Taccessor, Tdisplay, Ttext>::start()
{
    m_value = Taccessor::getRef();

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
        Taccessor::getRef() = m_value;
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

template<typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<bool, Taccessor, Tdisplay, Ttext>::start()
{
    Base::start();

    if (Taccessor::getRef() == true)
        Base::setSelectedIndex(0);
    else if (Taccessor::getRef() == false)
        Base::setSelectedIndex(1);
}

template<typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<ControlMode, Taccessor, Tdisplay, Ttext>::start()
{
    Base::start();

    if (Taccessor::getRef() == ControlMode::OpenMode)
        Base::setSelectedIndex(0);
    else if (Taccessor::getRef() == ControlMode::Voltage)
        Base::setSelectedIndex(1);
    else if (Taccessor::getRef() == ControlMode::Speed)
        Base::setSelectedIndex(2);
    else if (Taccessor::getRef() == ControlMode::Torque)
        Base::setSelectedIndex(3);
    else
        Base::setSelectedIndex(4);
}

template<typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<ControlType, Taccessor, Tdisplay, Ttext>::start()
{
    Base::start();

    if (Taccessor::getRef() == ControlType::Commutation)
        Base::setSelectedIndex(0);
    else if (Taccessor::getRef() == ControlType::Sinusoidal)
        Base::setSelectedIndex(1);
    else if (Taccessor::getRef() == ControlType::FieldOrientedControl)
        Base::setSelectedIndex(2);
    else
        Base::setSelectedIndex(3);
}

}
