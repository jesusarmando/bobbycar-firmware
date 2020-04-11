#pragma once

#include "changevaluedisplay.h"
#include "staticmenudisplay.h"
#include "menuitems/setvaluemenuitem.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "texts.h"

namespace {
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
void ChangeValueDisplay<bool, Taccessor, Tdisplay, Ttext>::start()
{
    Base::start();

    if (Taccessor::getValue() == true)
        Base::setSelectedIndex(0);
    else if (Taccessor::getValue() == false)
        Base::setSelectedIndex(1);
}
}
