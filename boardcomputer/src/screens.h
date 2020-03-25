#pragma once

#include <map>
#include <set>

#include "displays/menus/bluetoothmodesettingsmenu.h"
#include "displays/menus/buzzermenu.h"
#include "displays/menus/commonsettingsmenu.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "displays/menus/demosmenu.h"
#include "displays/menus/enablemenu.h"
#include "displays/menus/invertmenu.h"
#include "displays/menus/mainmenu.h"
#include "displays/menus/manualmodesettingsmenu.h"
#include "displays/menus/potisettingsmenu.h"
#include "displays/menus/selectmodemenu.h"
#include "displays/menus/settingsmenu.h"
#include "displays/gameoflifedisplay.h"
#include "displays/metersdisplay.h"
#include "displays/pingpongdisplay.h"
#include "displays/spirodisplay.h"
#include "displays/starfielddisplay.h"
#include "displays/statusdisplay.h"

namespace {
union X {
    X() {}
    ~X() {}

    BluetoothModeSettingsMenu bluetoothModeSettingsMenu;
    BuzzerMenu buzzerMenu;
    CommonSettingsMenu commonSettingsMenu;
    DefaultModeSettingsMenu defaultModeSettingsMenu;
    DemosMenu demosMenu;
    EnableMenu enableMenu;
    InvertMenu invertMenu;
    MainMenu mainMenu;
    ManualModeSettingsMenu manualModeSettingsMenu;
    PotiSettingsMenu potiSettingsMenu;
    SelectModeMenu selectModeMenu;
    SettingsMenu settingsMenu;

    GameOfLifeDisplay gameOfLifeDisplay;
    MetersDisplay metersDisplay;
    PingPongDisplay pingPongDisplay;
    SpiroDisplay spiroDisplay;
    StarfieldDisplay starFieldDisplay;
    StatusDisplay statusDisplay;
} displays;

Display *currentDisplay{};

template<typename T> void switchScreen()
{
    if (currentDisplay)
        currentDisplay->~Display();
    else
        currentDisplay = &displays.mainMenu;

    new (currentDisplay) T;

    currentDisplay->start();
    currentDisplay->update();
    currentDisplay->redraw();
}

void printMemoryUsage(){
    std::map<int, std::set<const char *>> test;

    test[sizeof(displays)].insert("displays");
    test[sizeof(displays.bluetoothModeSettingsMenu)].insert("displays.bluetoothModeSettingsMenu");
    test[sizeof(displays.buzzerMenu)].insert("displays.buzzerMenu");
    test[sizeof(displays.commonSettingsMenu)].insert("displays.commonSettingsMenu");
    test[sizeof(displays.defaultModeSettingsMenu)].insert("displays.defaultModeSettingsMenu");
    test[sizeof(displays.demosMenu)].insert("displays.demosMenu");
    test[sizeof(displays.enableMenu)].insert("displays.enableMenu");
    test[sizeof(displays.invertMenu)].insert("displays.invertMenu");
    test[sizeof(displays.mainMenu)].insert("displays.mainMenu");
    test[sizeof(displays.manualModeSettingsMenu)].insert("displays.manualModeSettingsMenu");
    test[sizeof(displays.potiSettingsMenu)].insert("displays.potiSettingsMenu");
    test[sizeof(displays.selectModeMenu)].insert("displays.selectModeMenu");
    test[sizeof(displays.settingsMenu)].insert("displays.settingsMenu");
    test[sizeof(displays.gameOfLifeDisplay)].insert("displays.gameOfLifeDisplay");
    test[sizeof(displays.metersDisplay)].insert("displays.metersDisplay");
    test[sizeof(displays.pingPongDisplay)].insert("displays.pingPongDisplay");
    test[sizeof(displays.spiroDisplay)].insert("displays.spiroDisplay");
    test[sizeof(displays.starFieldDisplay)].insert("displays.starFieldDisplay");
    test[sizeof(displays.statusDisplay)].insert("displays.statusDisplay");

    for (auto iter = std::cbegin(test); iter != std::cend(test); iter++)
    {
        Serial.print("Folloging have a size of ");
        Serial.println(iter->first);

        for (const auto &x : iter->second)
            Serial.println(x);

        Serial.println();
    }
}
}
