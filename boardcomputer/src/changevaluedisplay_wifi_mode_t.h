#pragma once

#include <esp_wifi_types.h>

#include "changevaluedisplay.h"
#include "staticmenudisplay.h"
#include "menuitems/staticdummymenuitem.h"
#include "texts.h"

namespace {
template<>
class ChangeValueDisplay<wifi_mode_t> :
    public StaticMenuDisplay<
        StaticDummyMenuItem<TEXT_WIFI_MODE_NULL>,
        StaticDummyMenuItem<TEXT_WIFI_MODE_STA>,
        StaticDummyMenuItem<TEXT_WIFI_MODE_AP>,
        StaticDummyMenuItem<TEXT_WIFI_MODE_APSTA>,
        StaticDummyMenuItem<TEXT_BACK>
    >,
    public virtual AccessorInterface<wifi_mode_t>
{
    using Base = StaticMenuDisplay<
        StaticDummyMenuItem<TEXT_WIFI_MODE_NULL>,
        StaticDummyMenuItem<TEXT_WIFI_MODE_STA>,
        StaticDummyMenuItem<TEXT_WIFI_MODE_AP>,
        StaticDummyMenuItem<TEXT_WIFI_MODE_APSTA>,
        StaticDummyMenuItem<TEXT_BACK>
    >;

public:
    void start() override;

    void triggered() override;
};

void ChangeValueDisplay<wifi_mode_t>::start()
{
    Base::start();

    if (getValue() == WIFI_MODE_NULL)
        Base::setSelectedIndex(0);
    else if (getValue() == WIFI_MODE_STA)
        Base::setSelectedIndex(1);
    else if (getValue() == WIFI_MODE_AP)
        Base::setSelectedIndex(2);
    else if (getValue() == WIFI_MODE_APSTA)
        Base::setSelectedIndex(3);
    else
    {
        Serial.printf("Unknown wifi_mode_t: %i", int(getValue()));
        Base::setSelectedIndex(4);
    }
}

void ChangeValueDisplay<wifi_mode_t>::triggered()
{
    Base::triggered();

    switch (Base::selectedIndex())
    {
    case 0: setValue(WIFI_MODE_NULL); break;
    case 1: setValue(WIFI_MODE_STA); break;
    case 2: setValue(WIFI_MODE_AP); break;
    case 3: setValue(WIFI_MODE_APSTA); break;
    }
}
}
