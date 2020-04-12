#pragma once

#include <esp_wifi_types.h>

#include "changevaluedisplay.h"
#include "staticmenudisplay.h"
#include "utils.h"
#include "actions/dummyaction.h"
#include "icons/back.h"
#include "texts.h"

namespace {
template<>
class ChangeValueDisplay<wifi_mode_t> :
    public StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_WIFI_MODE_NULL>,  DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_MODE_STA>,   DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_MODE_AP>,    DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_MODE_APSTA>, DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,            DefaultFont, DefaultColor, DummyAction, StaticMenuItemIcon<&icons::back>>
    >,
    public virtual AccessorInterface<wifi_mode_t>
{
    using Base = StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_WIFI_MODE_NULL>,  DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_MODE_STA>,   DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_MODE_AP>,    DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_MODE_APSTA>, DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,            DefaultFont, DefaultColor, DummyAction, StaticMenuItemIcon<&icons::back>>
    >;

public:
    void start() override;

    void triggered() override;
};

void ChangeValueDisplay<wifi_mode_t>::start()
{
    Base::start();

    if (getValue() == WIFI_MODE_NULL)
        setSelectedIndex(0);
    else if (getValue() == WIFI_MODE_STA)
        setSelectedIndex(1);
    else if (getValue() == WIFI_MODE_AP)
        setSelectedIndex(2);
    else if (getValue() == WIFI_MODE_APSTA)
        setSelectedIndex(3);
    else
    {
        Serial.printf("Unknown wifi_mode_t: %i", int(getValue()));
        setSelectedIndex(4);
    }
}

void ChangeValueDisplay<wifi_mode_t>::triggered()
{
    Base::triggered();

    switch (selectedIndex())
    {
    case 0: setValue(WIFI_MODE_NULL); break;
    case 1: setValue(WIFI_MODE_STA); break;
    case 2: setValue(WIFI_MODE_AP); break;
    case 3: setValue(WIFI_MODE_APSTA); break;
    }
}
}
