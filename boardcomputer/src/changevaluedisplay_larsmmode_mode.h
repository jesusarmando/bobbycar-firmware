#pragma once

#include "changevaluedisplay.h"
#include "staticmenudisplay.h"
#include "menuitems/setvaluemenuitem.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "texts.h"
#include "modes/larsmmode.h"

namespace {
template<typename Taccessor, typename Tdisplay, const char *Ttext>
class ChangeValueDisplay<LarsmMode::Mode, Taccessor, Tdisplay, Ttext> final :
    public StaticTitle<Ttext>,
    public StaticMenuDisplay<
        SetValueMenuItem<LarsmMode::Mode, Taccessor, LarsmMode::Mode::Mode1, Tdisplay, TEXT_LARSMMODE1>,
        SetValueMenuItem<LarsmMode::Mode, Taccessor, LarsmMode::Mode::Mode2, Tdisplay, TEXT_LARSMMODE2>,
        SetValueMenuItem<LarsmMode::Mode, Taccessor, LarsmMode::Mode::Mode3, Tdisplay, TEXT_LARSMMODE3>,
        SetValueMenuItem<LarsmMode::Mode, Taccessor, LarsmMode::Mode::Mode4, Tdisplay, TEXT_LARSMMODE4>,
        StaticSwitchScreenMenuItem<Tdisplay, TEXT_BACK>
    >
{
    using Base = StaticMenuDisplay<
        SetValueMenuItem<LarsmMode::Mode, Taccessor, LarsmMode::Mode::Mode1, Tdisplay, TEXT_LARSMMODE1>,
        SetValueMenuItem<LarsmMode::Mode, Taccessor, LarsmMode::Mode::Mode2, Tdisplay, TEXT_LARSMMODE2>,
        SetValueMenuItem<LarsmMode::Mode, Taccessor, LarsmMode::Mode::Mode3, Tdisplay, TEXT_LARSMMODE3>,
        SetValueMenuItem<LarsmMode::Mode, Taccessor, LarsmMode::Mode::Mode4, Tdisplay, TEXT_LARSMMODE4>,
        StaticSwitchScreenMenuItem<Tdisplay, TEXT_BACK>
    >;

public:
    void start() override;
};

template<typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<LarsmMode::Mode, Taccessor, Tdisplay, Ttext>::start()
{
    Base::start();

    if (Taccessor::getValue() == LarsmMode::Mode::Mode1)
        Base::setSelectedIndex(0);
    else if (Taccessor::getValue() == LarsmMode::Mode::Mode2)
        Base::setSelectedIndex(1);
    else if (Taccessor::getValue() == LarsmMode::Mode::Mode3)
        Base::setSelectedIndex(2);
    else if (Taccessor::getValue() == LarsmMode::Mode::Mode4)
        Base::setSelectedIndex(3);
    else
    {
        Serial.printf("Unknown LarsmMode::Mode: %i", int(Taccessor::getValue()));
        Base::setSelectedIndex(4);
    }
}
}
