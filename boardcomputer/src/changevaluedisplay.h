#pragma once

#include "display.h"
#include "globals.h"
#include "utils.h"
#include "texts.h"
#include "menudisplay.h"
#include "menuitems/setvaluemenuitem.h"
#include "menuitems/switchscreenmenuitem.h"

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
};

template<typename Tvalue, typename Taccessor, typename Tdisplay, const char *Ttext>
class ChangeValueDisplay final : public ChangeValueDisplayInterface
{
public:
    void start() override;
    void update() override final;

    void rotate(int offset) override;
    void button(bool pressed) override;

    const char *title() const override { return Ttext; }

    int value() const { return m_value; }
    void setValue(int value) { m_value = value; m_needsRedraw = true; }

    void confirm() override;

private:
    void redraw() const;

    Tvalue m_value{};
    bool m_needsRedraw{};
    bool m_pressed{};
};

template<typename Taccessor, typename Tdisplay, const char *Ttext>
class ChangeValueDisplay<bool, Taccessor, Tdisplay, Ttext> final : public MenuDisplay<
    Ttext,
    SetValueMenuItem<bool, Taccessor, true, Tdisplay, TEXT_TRUE>,
    SetValueMenuItem<bool, Taccessor, false, Tdisplay, TEXT_FALSE>,
    SwitchScreenMenuItem<Tdisplay, TEXT_BACK>
>
{
    using Base = MenuDisplay<
        Ttext,
        SetValueMenuItem<bool, Taccessor, true, Tdisplay, TEXT_TRUE>,
        SetValueMenuItem<bool, Taccessor, false, Tdisplay, TEXT_FALSE>,
        SwitchScreenMenuItem<Tdisplay, TEXT_BACK>
    >;

public:
    void start() override;
};

template<typename Taccessor, typename Tdisplay, const char *Ttext>
class ChangeValueDisplay<ControlMode, Taccessor, Tdisplay, Ttext> final : public MenuDisplay<
    Ttext,
    SetValueMenuItem<ControlMode, Taccessor, ControlMode::OpenMode, Tdisplay, TEXT_OPENMODE>,
    SetValueMenuItem<ControlMode, Taccessor, ControlMode::Voltage, Tdisplay, TEXT_VOLTAGE>,
    SetValueMenuItem<ControlMode, Taccessor, ControlMode::Speed, Tdisplay, TEXT_SPEED>,
    SetValueMenuItem<ControlMode, Taccessor, ControlMode::Torque, Tdisplay, TEXT_TORQUE>,
    SwitchScreenMenuItem<Tdisplay, TEXT_BACK>
>
{
    using Base = MenuDisplay<
        Ttext,
        SetValueMenuItem<ControlMode, Taccessor, ControlMode::OpenMode, Tdisplay, TEXT_OPENMODE>,
        SetValueMenuItem<ControlMode, Taccessor, ControlMode::Voltage, Tdisplay, TEXT_VOLTAGE>,
        SetValueMenuItem<ControlMode, Taccessor, ControlMode::Speed, Tdisplay, TEXT_SPEED>,
        SetValueMenuItem<ControlMode, Taccessor, ControlMode::Torque, Tdisplay, TEXT_TORQUE>,
        SwitchScreenMenuItem<Tdisplay, TEXT_BACK>
    >;

public:
    void start() override;
};


template<typename Taccessor, typename Tdisplay, const char *Ttext>
class ChangeValueDisplay<ControlType, Taccessor, Tdisplay, Ttext> final : public MenuDisplay<
    Ttext,
    SetValueMenuItem<ControlType, Taccessor, ControlType::Commutation, Tdisplay, TEXT_COMMUTATION>,
    SetValueMenuItem<ControlType, Taccessor, ControlType::Sinusoidal, Tdisplay, TEXT_SINUSOIDAL>,
    SetValueMenuItem<ControlType, Taccessor, ControlType::FieldOrientedControl, Tdisplay, TEXT_FIELDORIENTEDCONTROL>,
    SwitchScreenMenuItem<Tdisplay, TEXT_BACK>
>
{
    using Base = MenuDisplay<
        Ttext,
        SetValueMenuItem<ControlType, Taccessor, ControlType::Commutation, Tdisplay, TEXT_COMMUTATION>,
        SetValueMenuItem<ControlType, Taccessor, ControlType::Sinusoidal, Tdisplay, TEXT_SINUSOIDAL>,
        SetValueMenuItem<ControlType, Taccessor, ControlType::FieldOrientedControl, Tdisplay, TEXT_FIELDORIENTEDCONTROL>,
        SwitchScreenMenuItem<Tdisplay, TEXT_BACK>
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

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
}

template<typename Tvalue, typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Taccessor, Tdisplay, Ttext>::start()
{
    m_value = Taccessor::getRef();
    m_needsRedraw = true;
    m_pressed = false;

    ChangeValueDisplayInterface::start();
}

template<typename Tvalue, typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Taccessor, Tdisplay, Ttext>::update()
{
    if (m_needsRedraw)
    {
        redraw();
        m_needsRedraw = false;
    }

    if (m_pressed)
    {
        Taccessor::getRef() = m_value;
        switchScreen<Tdisplay>();
    }
}

template<typename Tvalue, typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Taccessor, Tdisplay, Ttext>::rotate(int offset)
{
    m_value += offset;
    m_needsRedraw = true;
}

template<typename Tvalue, typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Taccessor, Tdisplay, Ttext>::button(bool pressed)
{
    if (!pressed)
        confirm();
}

template<typename Tvalue, typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Taccessor, Tdisplay, Ttext>::confirm()
{
    m_pressed = true;
}

template<typename Tvalue, typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Taccessor, Tdisplay, Ttext>::redraw() const
{
    tft.drawCentreString(String() + ' ' + m_value + ' ', tft.width()/2, 80, 7);
}

template<typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<bool, Taccessor, Tdisplay, Ttext>::start()
{
    Base::start();

    if (Taccessor::getRef() == true)
        Base::setSelectedItem(Base::begin() + 0);
    else if (Taccessor::getRef() == false)
        Base::setSelectedItem(Base::begin() + 1);
}

template<typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<ControlMode, Taccessor, Tdisplay, Ttext>::start()
{
    Base::start();

    if (Taccessor::getRef() == ControlMode::OpenMode)
        Base::setSelectedItem(Base::begin() + 0);
    else if (Taccessor::getRef() == ControlMode::Voltage)
        Base::setSelectedItem(Base::begin() + 1);
    else if (Taccessor::getRef() == ControlMode::Speed)
        Base::setSelectedItem(Base::begin() + 2);
    else if (Taccessor::getRef() == ControlMode::Torque)
        Base::setSelectedItem(Base::begin() + 3);
    else
        Base::setSelectedItem(Base::begin() + 4);
}

template<typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<ControlType, Taccessor, Tdisplay, Ttext>::start()
{
    Base::start();

    if (Taccessor::getRef() == ControlType::Commutation)
        Base::setSelectedItem(Base::begin() + 0);
    else if (Taccessor::getRef() == ControlType::Sinusoidal)
        Base::setSelectedItem(Base::begin() + 1);
    else if (Taccessor::getRef() == ControlType::FieldOrientedControl)
        Base::setSelectedItem(Base::begin() + 2);
    else
        Base::setSelectedItem(Base::begin() + 3);
}

}
