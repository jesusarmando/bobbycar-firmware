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
#include "displays/changescreens/setdefaultmodeenablefieldweakeningsmootheningdisplay.h"
#include "displays/changescreens/setfrontleftenableddisplay.h"
#include "displays/changescreens/setfrontrightenableddisplay.h"
#include "displays/changescreens/setbackleftenableddisplay.h"
#include "displays/changescreens/setbackrightenableddisplay.h"
#include "displays/changescreens/setfrontleftinverteddisplay.h"
#include "displays/changescreens/setfrontrightinverteddisplay.h"
#include "displays/changescreens/setbackleftinverteddisplay.h"
#include "displays/changescreens/setbackrightinverteddisplay.h"
#include "displays/changescreens/setfrontleddisplay.h"
#include "displays/changescreens/setbackleddisplay.h"
#include "displays/changescreens/setdefaultmodectrlmoddisplay.h"
#include "displays/changescreens/setmanualmodectrlmoddisplay.h"
#include "displays/changescreens/setdefaultmodectrltypdisplay.h"
#include "displays/changescreens/setmanualmodectrltypdisplay.h"
#include "displays/changescreens/setfrontfreqdisplay.h"
#include "displays/changescreens/setfrontpatterndisplay.h"
#include "displays/changescreens/setbackfreqdisplay.h"
#include "displays/changescreens/setbackpatterndisplay.h"
#include "displays/changescreens/setimotmaxdisplay.h"
#include "displays/changescreens/setidcmaxdisplay.h"
#include "displays/changescreens/setnmotmaxdisplay.h"
#include "displays/changescreens/setfieldweakmaxdisplay.h"
#include "displays/changescreens/setphaseadvmaxdisplay.h"
#include "displays/changescreens/setdefaultmodeweakeningsmootheningdisplay.h"
#include "displays/changescreens/setdefaultmodefrontpercentagedisplay.h"
#include "displays/changescreens/setdefaultmodebackpercentagedisplay.h"
#include "displays/changescreens/setdefaultmodeaddschwelledisplay.h"
#include "displays/changescreens/setdefaultmodegas1wertdisplay.h"
#include "displays/changescreens/setdefaultmodegas2wertdisplay.h"
#include "displays/changescreens/setdefaultmodebrems1wertdisplay.h"
#include "displays/changescreens/setdefaultmodebrems2wertdisplay.h"
#include "displays/changescreens/setgasmindisplay.h"
#include "displays/changescreens/setgasmaxdisplay.h"
#include "displays/changescreens/setbremsmindisplay.h"
#include "displays/changescreens/setbremsmaxdisplay.h"

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

    SetDefaultModeEnableFieldWeakeningSmootheningDisplay setDefaultModeEnableFieldWeakeningSmootheningDisplay;
    SetFrontLeftEnabledDisplay setFrontLeftEnabledDisplay;
    SetFrontRightEnabledDisplay setFrontRightEnabledDisplay;
    SetBackLeftEnabledDisplay setBackLeftEnabledDisplay;
    SetBackRightEnabledDisplay setBackRightEnabledDisplay;
    SetFrontLeftInvertedDisplay setFrontLeftInvertedDisplay;
    SetFrontRightInvertedDisplay setFrontRightInvertedDisplay;
    SetBackLeftInvertedDisplay setBackLeftInvertedDisplay;
    SetBackRightInvertedDisplay setBackRightInvertedDisplay;
    SetFrontLedDisplay setFrontLedDisplay;
    SetBackLedDisplay setBackLedDisplay;

    SetDefaultModeCtrlModDisplay setDefaultModeCtrlModDisplay;
    SetManualModeCtrlModDisplay setManualModeCtrlModDisplay;
    SetDefaultModeCtrlTypDisplay setDefaultModeCtrlTypDisplay;
    SetManualModeCtrlTypDisplay setManualModeCtrlTypDisplay;

    SetFrontFreqDisplay setFrontFreqDisplay;
    SetFrontPatternDisplay setFrontPatternDisplay;
    SetBackFreqDisplay setBackFreqDisplay;
    SetBackPatternDisplay setBackPatternDisplay;

    SetIMotMaxDisplay setIMotMaxDisplay;
    SetIDcMaxDisplay setIDcMaxDisplay;
    SetNMotMaxDisplay setNMotMaxDisplay;
    SetFieldWeakMaxDisplay setFieldWeakMaxDisplay;
    SetPhaseAdvMaxDisplay setPhaseAdvMaxDisplay;
    SetDefaultModeWeakeningSmootheningDisplay setDefaultModeWeakeningSmootheningDisplay;
    SetDefaultModeFrontPercentageDisplay setDefaultModeFrontPercentageDisplay;
    SetDefaultModeBackPercentageDisplay setDefaultModeBackPercentageDisplay;
    SetDefaultModeAddSchwelleDisplay setDefaultModeAddSchwelleDisplay;
    SetDefaultModeGas1WertDisplay setDefaultModeGas1Wert;
    SetDefaultModeGas2WertDisplay setDefaultModeGas2Wert;
    SetDefaultModeBrems1WertDisplay setDefaultModeBrems1Wert;
    SetDefaultModeBrems2WertDisplay setDefaultModeBrems2Wert;
    SetGasMinDisplay setGasMinDisplay;
    SetGasMaxDisplay setGasMaxDisplay;
    SetBremsMinDisplay setBremsMinDisplay;
    SetBremsMaxDisplay setBremsMaxDisplay;
} displays;

Display *currentDisplay{};

template<typename T> void switchScreenImpl();

template<typename T> void switchScreen()
{
    if (currentDisplay)
    {
        currentDisplay->~Display();
        currentDisplay = nullptr;
    }

    switchScreenImpl<T>();

    currentDisplay->start();
    currentDisplay->update();
    currentDisplay->redraw();
}

template<> void switchScreenImpl<BluetoothModeSettingsMenu>() { new (&displays.bluetoothModeSettingsMenu) BluetoothModeSettingsMenu; currentDisplay = &displays.bluetoothModeSettingsMenu; }
template<> void switchScreenImpl<BuzzerMenu>() { new (&displays.buzzerMenu) BuzzerMenu; currentDisplay = &displays.buzzerMenu; }
template<> void switchScreenImpl<CommonSettingsMenu>() { new (&displays.commonSettingsMenu) CommonSettingsMenu; currentDisplay = &displays.commonSettingsMenu; }
template<> void switchScreenImpl<DefaultModeSettingsMenu>() { new (&displays.defaultModeSettingsMenu) DefaultModeSettingsMenu; currentDisplay = &displays.defaultModeSettingsMenu; }
template<> void switchScreenImpl<DemosMenu>() { new (&displays.demosMenu) DemosMenu; currentDisplay = &displays.demosMenu; }
template<> void switchScreenImpl<EnableMenu>() { new (&displays.enableMenu) EnableMenu; currentDisplay = &displays.enableMenu; }
template<> void switchScreenImpl<InvertMenu>() { new (&displays.invertMenu) InvertMenu; currentDisplay = &displays.invertMenu; }
template<> void switchScreenImpl<MainMenu>() { new (&displays.mainMenu) MainMenu; currentDisplay = &displays.mainMenu; }
template<> void switchScreenImpl<ManualModeSettingsMenu>() { new (&displays.manualModeSettingsMenu) ManualModeSettingsMenu; currentDisplay = &displays.manualModeSettingsMenu; }
template<> void switchScreenImpl<PotiSettingsMenu>() { new (&displays.potiSettingsMenu) PotiSettingsMenu; currentDisplay = &displays.potiSettingsMenu; }
template<> void switchScreenImpl<SelectModeMenu>() { new (&displays.selectModeMenu) SelectModeMenu; currentDisplay = &displays.selectModeMenu; }
template<> void switchScreenImpl<SettingsMenu>() { new (&displays.settingsMenu) SettingsMenu; currentDisplay = &displays.settingsMenu; }
template<> void switchScreenImpl<GameOfLifeDisplay>() { new (&displays.gameOfLifeDisplay) GameOfLifeDisplay; currentDisplay = &displays.gameOfLifeDisplay; }
template<> void switchScreenImpl<MetersDisplay>() { new (&displays.metersDisplay) MetersDisplay; currentDisplay = &displays.metersDisplay; }
template<> void switchScreenImpl<PingPongDisplay>() { new (&displays.pingPongDisplay) PingPongDisplay; currentDisplay = &displays.pingPongDisplay; }
template<> void switchScreenImpl<SpiroDisplay>() { new (&displays.spiroDisplay) SpiroDisplay; currentDisplay = &displays.spiroDisplay; }
template<> void switchScreenImpl<StarfieldDisplay>() { new (&displays.starFieldDisplay) StarfieldDisplay; currentDisplay = &displays.starFieldDisplay; }
template<> void switchScreenImpl<StatusDisplay>() { new (&displays.statusDisplay) StatusDisplay; currentDisplay = &displays.statusDisplay; }
template<> void switchScreenImpl<SetDefaultModeEnableFieldWeakeningSmootheningDisplay>() { new (&displays.setDefaultModeEnableFieldWeakeningSmootheningDisplay) SetDefaultModeEnableFieldWeakeningSmootheningDisplay; currentDisplay = &displays.setDefaultModeEnableFieldWeakeningSmootheningDisplay; }
template<> void switchScreenImpl<SetFrontLeftEnabledDisplay>() { new (&displays.setFrontLeftEnabledDisplay) SetFrontLeftEnabledDisplay; currentDisplay = &displays.setFrontLeftEnabledDisplay; }
template<> void switchScreenImpl<SetFrontRightEnabledDisplay>() { new (&displays.setFrontRightEnabledDisplay) SetFrontRightEnabledDisplay; currentDisplay = &displays.setFrontRightEnabledDisplay; }
template<> void switchScreenImpl<SetBackLeftEnabledDisplay>() { new (&displays.setBackLeftEnabledDisplay) SetBackLeftEnabledDisplay; currentDisplay = &displays.setBackLeftEnabledDisplay; }
template<> void switchScreenImpl<SetBackRightEnabledDisplay>() { new (&displays.setBackRightEnabledDisplay) SetBackRightEnabledDisplay; currentDisplay = &displays.setBackRightEnabledDisplay; }
template<> void switchScreenImpl<SetFrontLeftInvertedDisplay>() { new (&displays.setFrontLeftInvertedDisplay) SetFrontLeftInvertedDisplay; currentDisplay = &displays.setFrontLeftInvertedDisplay; }
template<> void switchScreenImpl<SetFrontRightInvertedDisplay>() { new (&displays.setFrontRightInvertedDisplay) SetFrontRightInvertedDisplay; currentDisplay = &displays.setFrontRightInvertedDisplay; }
template<> void switchScreenImpl<SetBackLeftInvertedDisplay>() { new (&displays.setBackLeftInvertedDisplay) SetBackLeftInvertedDisplay; currentDisplay = &displays.setBackLeftInvertedDisplay; }
template<> void switchScreenImpl<SetBackRightInvertedDisplay>() { new (&displays.setBackRightInvertedDisplay) SetBackRightInvertedDisplay; currentDisplay = &displays.setBackRightInvertedDisplay; }
template<> void switchScreenImpl<SetFrontLedDisplay>() { new (&displays.setFrontLedDisplay) SetFrontLedDisplay; currentDisplay = &displays.setFrontLedDisplay; }
template<> void switchScreenImpl<SetBackLedDisplay>() { new (&displays.setBackLedDisplay) SetBackLedDisplay; currentDisplay = &displays.setBackLedDisplay; }
template<> void switchScreenImpl<SetDefaultModeCtrlModDisplay>() { new (&displays.setDefaultModeCtrlModDisplay) SetDefaultModeCtrlModDisplay; currentDisplay = &displays.setDefaultModeCtrlModDisplay; }
template<> void switchScreenImpl<SetManualModeCtrlModDisplay>() { new (&displays.setManualModeCtrlModDisplay) SetManualModeCtrlModDisplay; currentDisplay = &displays.setManualModeCtrlModDisplay; }
template<> void switchScreenImpl<SetDefaultModeCtrlTypDisplay>() { new (&displays.setDefaultModeCtrlTypDisplay) SetDefaultModeCtrlTypDisplay; currentDisplay = &displays.setDefaultModeCtrlTypDisplay; }
template<> void switchScreenImpl<SetManualModeCtrlTypDisplay>() { new (&displays.setManualModeCtrlTypDisplay) SetManualModeCtrlTypDisplay; currentDisplay = &displays.setManualModeCtrlTypDisplay; }
template<> void switchScreenImpl<SetFrontFreqDisplay>() { new (&displays.setFrontFreqDisplay) SetFrontFreqDisplay; currentDisplay = &displays.setFrontFreqDisplay; }
template<> void switchScreenImpl<SetFrontPatternDisplay>() { new (&displays.setFrontPatternDisplay) SetFrontPatternDisplay; currentDisplay = &displays.setFrontPatternDisplay; }
template<> void switchScreenImpl<SetBackFreqDisplay>() { new (&displays.setBackFreqDisplay) SetBackFreqDisplay; currentDisplay = &displays.setBackFreqDisplay; }
template<> void switchScreenImpl<SetBackPatternDisplay>() { new (&displays.setBackPatternDisplay) SetBackPatternDisplay; currentDisplay = &displays.setBackPatternDisplay; }
template<> void switchScreenImpl<SetIMotMaxDisplay>() { new (&displays.setIMotMaxDisplay) SetIMotMaxDisplay; currentDisplay = &displays.setIMotMaxDisplay; }
template<> void switchScreenImpl<SetIDcMaxDisplay>() { new (&displays.setIDcMaxDisplay) SetIDcMaxDisplay; currentDisplay = &displays.setIDcMaxDisplay; }
template<> void switchScreenImpl<SetNMotMaxDisplay>() { new (&displays.setNMotMaxDisplay) SetNMotMaxDisplay; currentDisplay = &displays.setNMotMaxDisplay; }
template<> void switchScreenImpl<SetFieldWeakMaxDisplay>() { new (&displays.setFieldWeakMaxDisplay) SetFieldWeakMaxDisplay; currentDisplay = &displays.setFieldWeakMaxDisplay; }
template<> void switchScreenImpl<SetPhaseAdvMaxDisplay>() { new (&displays.setPhaseAdvMaxDisplay) SetPhaseAdvMaxDisplay; currentDisplay = &displays.setPhaseAdvMaxDisplay; }
template<> void switchScreenImpl<SetDefaultModeWeakeningSmootheningDisplay>() { new (&displays.setDefaultModeWeakeningSmootheningDisplay) SetDefaultModeWeakeningSmootheningDisplay; currentDisplay = &displays.setDefaultModeWeakeningSmootheningDisplay; }
template<> void switchScreenImpl<SetDefaultModeFrontPercentageDisplay>() { new (&displays.setDefaultModeFrontPercentageDisplay) SetDefaultModeFrontPercentageDisplay; currentDisplay = &displays.setDefaultModeFrontPercentageDisplay; }
template<> void switchScreenImpl<SetDefaultModeBackPercentageDisplay>() { new (&displays.setDefaultModeBackPercentageDisplay) SetDefaultModeBackPercentageDisplay; currentDisplay = &displays.setDefaultModeBackPercentageDisplay; }
template<> void switchScreenImpl<SetDefaultModeAddSchwelleDisplay>() { new (&displays.setDefaultModeAddSchwelleDisplay) SetDefaultModeAddSchwelleDisplay; currentDisplay = &displays.setDefaultModeAddSchwelleDisplay; }
template<> void switchScreenImpl<SetDefaultModeGas1WertDisplay>() { new (&displays.setDefaultModeGas1Wert) SetDefaultModeGas1WertDisplay; currentDisplay = &displays.setDefaultModeGas1Wert; }
template<> void switchScreenImpl<SetDefaultModeGas2WertDisplay>() { new (&displays.setDefaultModeGas2Wert) SetDefaultModeGas2WertDisplay; currentDisplay = &displays.setDefaultModeGas2Wert; }
template<> void switchScreenImpl<SetDefaultModeBrems1WertDisplay>() { new (&displays.setDefaultModeBrems1Wert) SetDefaultModeBrems1WertDisplay; currentDisplay = &displays.setDefaultModeBrems1Wert; }
template<> void switchScreenImpl<SetDefaultModeBrems2WertDisplay>() { new (&displays.setDefaultModeBrems2Wert) SetDefaultModeBrems2WertDisplay; currentDisplay = &displays.setDefaultModeBrems2Wert; }
template<> void switchScreenImpl<SetGasMinDisplay>() { new (&displays.setGasMinDisplay) SetGasMinDisplay; currentDisplay = &displays.setGasMinDisplay; }
template<> void switchScreenImpl<SetGasMaxDisplay>() { new (&displays.setGasMaxDisplay) SetGasMaxDisplay; currentDisplay = &displays.setGasMaxDisplay; }
template<> void switchScreenImpl<SetBremsMinDisplay>() { new (&displays.setBremsMinDisplay) SetBremsMinDisplay; currentDisplay = &displays.setBremsMinDisplay; }
template<> void switchScreenImpl<SetBremsMaxDisplay>() { new (&displays.setBremsMaxDisplay) SetBremsMaxDisplay; currentDisplay = &displays.setBremsMaxDisplay; }

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
    test[sizeof(displays.setDefaultModeEnableFieldWeakeningSmootheningDisplay)].insert("displays.setDefaultModeEnableFieldWeakeningSmootheningDisplay");
    test[sizeof(displays.setFrontLeftEnabledDisplay)].insert("displays.setFrontLeftEnabledDisplay");
    test[sizeof(displays.setFrontRightEnabledDisplay)].insert("displays.setFrontRightEnabledDisplay");
    test[sizeof(displays.setBackLeftEnabledDisplay)].insert("displays.setBackLeftEnabledDisplay");
    test[sizeof(displays.setBackRightEnabledDisplay)].insert("displays.setBackRightEnabledDisplay");
    test[sizeof(displays.setFrontLeftInvertedDisplay)].insert("displays.setFrontLeftInvertedDisplay");
    test[sizeof(displays.setFrontRightInvertedDisplay)].insert("displays.setFrontRightInvertedDisplay");
    test[sizeof(displays.setBackLeftInvertedDisplay)].insert("displays.setBackLeftInvertedDisplay");
    test[sizeof(displays.setBackRightInvertedDisplay)].insert("displays.setBackRightInvertedDisplay");
    test[sizeof(displays.setFrontLedDisplay)].insert("displays.setFrontLedDisplay");
    test[sizeof(displays.setBackLedDisplay)].insert("displays.setBackLedDisplay");
    test[sizeof(displays.setDefaultModeCtrlModDisplay)].insert("displays.setDefaultModeCtrlModDisplay");
    test[sizeof(displays.setManualModeCtrlModDisplay)].insert("displays.setManualModeCtrlModDisplay");
    test[sizeof(displays.setDefaultModeCtrlTypDisplay)].insert("displays.setDefaultModeCtrlTypDisplay");
    test[sizeof(displays.setManualModeCtrlTypDisplay)].insert("displays.setManualModeCtrlTypDisplay");
    test[sizeof(displays.setFrontFreqDisplay)].insert("displays.setFrontFreqDisplay");
    test[sizeof(displays.setFrontPatternDisplay)].insert("displays.setFrontPatternDisplay");
    test[sizeof(displays.setBackFreqDisplay)].insert("displays.setBackFreqDisplay");
    test[sizeof(displays.setBackPatternDisplay)].insert("displays.setBackPatternDisplay");
    test[sizeof(displays.setIMotMaxDisplay)].insert("displays.setIMotMaxDisplay");
    test[sizeof(displays.setIDcMaxDisplay)].insert("displays.setIDcMaxDisplay");
    test[sizeof(displays.setNMotMaxDisplay)].insert("displays.setNMotMaxDisplay");
    test[sizeof(displays.setFieldWeakMaxDisplay)].insert("displays.setFieldWeakMaxDisplay");
    test[sizeof(displays.setPhaseAdvMaxDisplay)].insert("displays.setPhaseAdvMaxDisplay");
    test[sizeof(displays.setDefaultModeWeakeningSmootheningDisplay)].insert("displays.setDefaultModeWeakeningSmootheningDisplay");
    test[sizeof(displays.setDefaultModeFrontPercentageDisplay)].insert("displays.setDefaultModeFrontPercentageDisplay");
    test[sizeof(displays.setDefaultModeBackPercentageDisplay)].insert("displays.setDefaultModeBackPercentageDisplay");
    test[sizeof(displays.setDefaultModeAddSchwelleDisplay)].insert("displays.setDefaultModeAddSchwelleDisplay");
    test[sizeof(displays.setDefaultModeGas1Wert)].insert("displays.setDefaultModeGas1Wert");
    test[sizeof(displays.setDefaultModeGas2Wert)].insert("displays.setDefaultModeGas2Wert");
    test[sizeof(displays.setDefaultModeBrems1Wert)].insert("displays.setDefaultModeBrems1Wert");
    test[sizeof(displays.setDefaultModeBrems2Wert)].insert("displays.setDefaultModeBrems2Wert");
    test[sizeof(displays.setGasMinDisplay)].insert("displays.setGasMinDisplay");
    test[sizeof(displays.setGasMaxDisplay)].insert("displays.setGasMaxDisplay");
    test[sizeof(displays.setBremsMinDisplay)].insert("displays.setBremsMinDisplay");
    test[sizeof(displays.setBremsMaxDisplay)].insert("displays.setBremsMaxDisplay");

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
