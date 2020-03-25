#pragma once

#include "display.h"
#include "globals.h"
#include "utils.h"
#include "texts.h"
#include "menudisplay.h"
#include "menuitems/setvaluemenuitem.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
template<typename Tvalue, typename Taccessor, typename Tdisplay, const char *Ttext>
class ChangeValueDisplay final : public Display
{
public:
    void start() override;
    void update() override final;
    void redraw() override final;

    int framerate() const override { return 60; }

    void rotate(int offset) override;
    void button(bool pressed) override;

private:
    void redrawMenu() const;

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

template<typename Tvalue, typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Taccessor, Tdisplay, Ttext>::start()
{
    Display::start();

    tft.setRotation(0);

    m_value = Taccessor::getRef();
    m_needsRedraw = true;
    m_pressed = false;
}

template<typename Tvalue, typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Taccessor, Tdisplay, Ttext>::update()
{
    if (m_pressed)
    {
        Taccessor::getRef() = m_value;
        switchScreen<Tdisplay>();
    }
}

template<typename Tvalue, typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Taccessor, Tdisplay, Ttext>::redraw()
{
    if (m_needsRedraw)
    {
        redrawMenu();
        m_needsRedraw = false;
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
        m_pressed = true;
}

template<typename Tvalue, typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Taccessor, Tdisplay, Ttext>::redrawMenu() const
{
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(Ttext, 5, 5, 4);

    tft.drawNumber(m_value, 50, 50, 7);
}

template<typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<bool, Taccessor, Tdisplay, Ttext>::start()
{
    Base::start();

    if (Taccessor::getRef() == true)
        Base::m_current = Base::begin() + 0;
    else if (Taccessor::getRef() == false)
        Base::m_current = Base::begin() + 1;
}

template<typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<ControlMode, Taccessor, Tdisplay, Ttext>::start()
{
    Base::start();

    if (Taccessor::getRef() == ControlMode::OpenMode)
        Base::m_current = Base::begin() + 0;
    else if (Taccessor::getRef() == ControlMode::Voltage)
        Base::m_current = Base::begin() + 1;
    else if (Taccessor::getRef() == ControlMode::Speed)
        Base::m_current = Base::begin() + 2;
    else if (Taccessor::getRef() == ControlMode::Torque)
        Base::m_current = Base::begin() + 3;
    else
        Base::m_current = Base::begin() + 4;
}

template<typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<ControlType, Taccessor, Tdisplay, Ttext>::start()
{
    Base::start();

    if (Taccessor::getRef() == ControlType::Commutation)
        Base::m_current = Base::begin() + 0;
    else if (Taccessor::getRef() == ControlType::Sinusoidal)
        Base::m_current = Base::begin() + 1;
    else if (Taccessor::getRef() == ControlType::FieldOrientedControl)
        Base::m_current = Base::begin() + 2;
    else
        Base::m_current = Base::begin() + 3;
}
}
