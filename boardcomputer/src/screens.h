#pragma once

#include <map>
#include <set>

#include "displays/menus/bluetoothsettingsmenu.h"
#include "displays/menus/bluetoothmodesettingsmenu.h"
#include "displays/menus/buzzermenu.h"
#include "displays/menus/commonsettingsmenu.h"
#include "displays/menus/debugmenu.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "displays/menus/demosmenu.h"
#include "displays/menus/dynamicdebugmenu.h"
#include "displays/menus/enablemenu.h"
#include "displays/menus/invertmenu.h"
#include "displays/menus/mainmenu.h"
#include "displays/menus/tempomatmodesettingsmenu.h"
#include "displays/menus/potisettingsmenu.h"
#include "displays/menus/selectmodemenu.h"
#include "displays/menus/settingsmenu.h"
#include "displays/bluetoothstatusdisplay.h"
#include "displays/calibratedisplay.h"
#include "displays/gameoflifedisplay.h"
#include "displays/matrixdisplay.h"
#include "displays/metersdisplay.h"
#include "displays/pingpongdisplay.h"
#include "displays/poweroffdisplay.h"
#include "displays/spirodisplay.h"
#include "displays/starfielddisplay.h"
#include "displays/statusdisplay.h"
#include "displays/versiondisplay.h"

#include "globals.h"
#include "utils.h"

namespace {
union X {
    X() {}
    ~X() { ((Display&)statusDisplay).~Display(); }

    MainMenu mainMenu;
    BluetoothSettingsMenu<SettingsMenu<MainMenu>> bluetoothSettingsMenu;
    BluetoothModeSettingsMenu<SettingsMenu<MainMenu>> bluetoothModeSettingsMenu;
    BuzzerMenu<DebugMenu<MainMenu>> buzzerMenu;
    CommonSettingsMenu<SettingsMenu<MainMenu>> commonSettingsMenu;
    DebugMenu<MainMenu> debugMenu;
    DefaultModeSettingsMenu<SettingsMenu<MainMenu>> defaultModeSettingsMenu;
    DemosMenu<MainMenu> demosMenu;
    DynamicDebugMenu<DebugMenu<MainMenu>> dynamicDebugMenu;
    EnableMenu<CommonSettingsMenu<SettingsMenu<MainMenu>>> enableMenu;
    InvertMenu<CommonSettingsMenu<SettingsMenu<MainMenu>>> invertMenu;
    TempomatModeSettingsMenu<SettingsMenu<MainMenu>> tempomatModeSettingsMenu;
    PotiSettingsMenu<SettingsMenu<MainMenu>> potiSettingsMenu;
    PresetsMenu<MainMenu> presetsMenu;
    SelectModeMenu<MainMenu> selectModeMenu;
    SettingsMenu<MainMenu> settingsMenu;

    BluetoothStatusDisplay<BluetoothSettingsMenu<SettingsMenu<MainMenu>>> bluetoothStatusDisplay;
    CalibrateDisplay<PotiSettingsMenu<SettingsMenu<MainMenu>>> calibrateDisplay;
    GameOfLifeDisplay<DemosMenu<MainMenu>> gameOfLifeDisplay;
    Lockscreen<MainMenu> lockScreen;
    MatrixDisplay<DemosMenu<MainMenu>> matrixDisplay;
    MetersDisplay<DemosMenu<MainMenu>> metersDisplay;
    PingPongDisplay<DemosMenu<MainMenu>> pingPongDisplay;
    PoweroffDisplay<MainMenu> poweroffDisplay;
    SpiroDisplay<DemosMenu<MainMenu>> spiroDisplay;
    StarfieldDisplay<DemosMenu<MainMenu>> starFieldDisplay;
    StatusDisplay<MainMenu> statusDisplay;
    VersionDisplay<SettingsMenu<MainMenu>> versionDisplay;

    FrontFreqChangeScreen<BuzzerMenu<DebugMenu<MainMenu>>> changeFrontFreq;
    FrontPatternChangeScreen<BuzzerMenu<DebugMenu<MainMenu>>> changeFrontPattern;
    BackFreqChangeScreen<BuzzerMenu<DebugMenu<MainMenu>>> changeBackFreq;
    BackPatternChangeScreen<BuzzerMenu<DebugMenu<MainMenu>>> changeBackPattern;

    IMotMaxChangeScreen<CommonSettingsMenu<SettingsMenu<MainMenu>>> changeIMotMax;
    IDcMaxChangeScreen<CommonSettingsMenu<SettingsMenu<MainMenu>>> changeIDcMax;
    NMotMaxChangeScreen<CommonSettingsMenu<SettingsMenu<MainMenu>>> changeNMotMax;
    FieldWeakMaxChangeScreen<CommonSettingsMenu<SettingsMenu<MainMenu>>> changeFieldWeakMax;
    PhaseAdvMaxChangeScreen<CommonSettingsMenu<SettingsMenu<MainMenu>>> changePhaseAdvMax;

    DefaultModeCtrlTypChangeDisplay<DefaultModeSettingsMenu<SettingsMenu<MainMenu>>> changeDefaultModeCtrlTyp;
    DefaultModeCtrlModChangeDisplay<DefaultModeSettingsMenu<SettingsMenu<MainMenu>>> changeDefaultModeCtrlMod;
    DefaultModeEnableFieldWeakeningSmootheningChangeDisplay<DefaultModeSettingsMenu<SettingsMenu<MainMenu>>> changeDefaultModeEnableFieldWeakeningSmoothening;
    DefaultModeWeakeningSmootheningChangeDisplay<DefaultModeSettingsMenu<SettingsMenu<MainMenu>>> changeDefaultModeWeakeningSmoothening;
    DefaultModeFrontPercentageChangeDisplay<DefaultModeSettingsMenu<SettingsMenu<MainMenu>>> changeDefaultModeFrontPercentage;
    DefaultModeBackPercentageChangeDisplay<DefaultModeSettingsMenu<SettingsMenu<MainMenu>>> changeDefaultModeBackPercentage;
    DefaultModeAddSchwelleChangeDisplay<DefaultModeSettingsMenu<SettingsMenu<MainMenu>>> changeDefaultModeAddSchwelle;
    DefaultModeGas1WertChangeDisplay<DefaultModeSettingsMenu<SettingsMenu<MainMenu>>> changeDefaultModeGas1Wert;
    DefaultModeGas2WertChangeDisplay<DefaultModeSettingsMenu<SettingsMenu<MainMenu>>> changeDefaultModeGas2Wert;
    DefaultModeBrems1WertChangeDisplay<DefaultModeSettingsMenu<SettingsMenu<MainMenu>>> changeDefaultModeBrems1Wert;
    DefaultModeBrems2WertChangeDisplay<DefaultModeSettingsMenu<SettingsMenu<MainMenu>>> changeDefaultModeBrems2Wert;

    FrontLeftEnabledChangeScreen<EnableMenu<CommonSettingsMenu<SettingsMenu<MainMenu>>>> changeFrontLeftEnabled;
    FrontRightEnabledChangeScreen<EnableMenu<CommonSettingsMenu<SettingsMenu<MainMenu>>>> changeFrontRightEnabled;
    BackLeftEnabledChangeScreen<EnableMenu<CommonSettingsMenu<SettingsMenu<MainMenu>>>> changeBackLeftEnabled;
    BackRightEnabledChangeScreen<EnableMenu<CommonSettingsMenu<SettingsMenu<MainMenu>>>> changeBackRightEnabled;

    FrontLeftInvertedChangeScreen<InvertMenu<CommonSettingsMenu<SettingsMenu<MainMenu>>>> changeFrontLeftInverted;
    FrontRightInvertedChangeScreen<InvertMenu<CommonSettingsMenu<SettingsMenu<MainMenu>>>> changeFrontRightInverted;
    BackLeftInvertedChangeScreen<InvertMenu<CommonSettingsMenu<SettingsMenu<MainMenu>>>> changeBackLeftInverted;
    BackRightInvertedChangeScreen<InvertMenu<CommonSettingsMenu<SettingsMenu<MainMenu>>>> changeBackRightInverted;

    FrontLedChangeScreen<DebugMenu<MainMenu>> changeFrontLed;
    BackLedChangeScreen<DebugMenu<MainMenu>> changeBackLed;

    TempomatModeCtrlTypChangeScreen<TempomatModeSettingsMenu<SettingsMenu<MainMenu>>> changeManualModeCtrlTyp;
    TempomatModeCtrlModChangeScreen<TempomatModeSettingsMenu<SettingsMenu<MainMenu>>> changeManualModeCtrlMod;

    GasMinChangeScreen<PotiSettingsMenu<SettingsMenu<MainMenu>>> changeGasMin;
    GasMaxChangeScreen<PotiSettingsMenu<SettingsMenu<MainMenu>>> changeGasMax;
    BremsMinChangeScreen<PotiSettingsMenu<SettingsMenu<MainMenu>>> changeBremsMin;
    BremsMaxChangeScreen<PotiSettingsMenu<SettingsMenu<MainMenu>>> changeBremsMax;
} displays;

using DefaultScreen = decltype(displays.statusDisplay);
//using DefaultScreen = decltype(displays.lockScreen);

template<typename T> T &getRefByType() = delete;
template<> decltype(displays.bluetoothSettingsMenu)                            &getRefByType<decltype(displays.bluetoothSettingsMenu)>()                            { return displays.bluetoothSettingsMenu; }
template<> decltype(displays.bluetoothModeSettingsMenu)                        &getRefByType<decltype(displays.bluetoothModeSettingsMenu)>()                        { return displays.bluetoothModeSettingsMenu; }
template<> decltype(displays.buzzerMenu)                                       &getRefByType<decltype(displays.buzzerMenu)>()                                       { return displays.buzzerMenu; }
template<> decltype(displays.commonSettingsMenu)                               &getRefByType<decltype(displays.commonSettingsMenu)>()                               { return displays.commonSettingsMenu; }
template<> decltype(displays.debugMenu)                                        &getRefByType<decltype(displays.debugMenu)>()                                        { return displays.debugMenu; }
template<> decltype(displays.defaultModeSettingsMenu)                          &getRefByType<decltype(displays.defaultModeSettingsMenu)>()                          { return displays.defaultModeSettingsMenu; }
template<> decltype(displays.demosMenu)                                        &getRefByType<decltype(displays.demosMenu)>()                                        { return displays.demosMenu; }
template<> decltype(displays.dynamicDebugMenu)                                 &getRefByType<decltype(displays.dynamicDebugMenu)>()                                 { return displays.dynamicDebugMenu; }
template<> decltype(displays.enableMenu)                                       &getRefByType<decltype(displays.enableMenu)>()                                       { return displays.enableMenu; }
template<> decltype(displays.invertMenu)                                       &getRefByType<decltype(displays.invertMenu)>()                                       { return displays.invertMenu; }
template<> decltype(displays.mainMenu)                                         &getRefByType<decltype(displays.mainMenu)>()                                         { return displays.mainMenu; }
template<> decltype(displays.tempomatModeSettingsMenu)                         &getRefByType<decltype(displays.tempomatModeSettingsMenu)>()                         { return displays.tempomatModeSettingsMenu; }
template<> decltype(displays.potiSettingsMenu)                                 &getRefByType<decltype(displays.potiSettingsMenu)>()                                 { return displays.potiSettingsMenu; }
template<> decltype(displays.presetsMenu)                                      &getRefByType<decltype(displays.presetsMenu)>()                                      { return displays.presetsMenu; }
template<> decltype(displays.selectModeMenu)                                   &getRefByType<decltype(displays.selectModeMenu)>()                                   { return displays.selectModeMenu; }
template<> decltype(displays.settingsMenu)                                     &getRefByType<decltype(displays.settingsMenu)>()                                     { return displays.settingsMenu; }

template<> decltype(displays.bluetoothStatusDisplay)                           &getRefByType<decltype(displays.bluetoothStatusDisplay)>()                           { return displays.bluetoothStatusDisplay; }
template<> decltype(displays.calibrateDisplay)                                 &getRefByType<decltype(displays.calibrateDisplay)>()                                 { return displays.calibrateDisplay; }
template<> decltype(displays.gameOfLifeDisplay)                                &getRefByType<decltype(displays.gameOfLifeDisplay)>()                                { return displays.gameOfLifeDisplay; }
template<> decltype(displays.lockScreen)                                       &getRefByType<decltype(displays.lockScreen)>()                                       { return displays.lockScreen; }
template<> decltype(displays.matrixDisplay)                                    &getRefByType<decltype(displays.matrixDisplay)>()                                    { return displays.matrixDisplay; }
template<> decltype(displays.metersDisplay)                                    &getRefByType<decltype(displays.metersDisplay)>()                                    { return displays.metersDisplay; }
template<> decltype(displays.pingPongDisplay)                                  &getRefByType<decltype(displays.pingPongDisplay)>()                                  { return displays.pingPongDisplay; }
template<> decltype(displays.poweroffDisplay)                                  &getRefByType<decltype(displays.poweroffDisplay)>()                                  { return displays.poweroffDisplay; }
template<> decltype(displays.spiroDisplay)                                     &getRefByType<decltype(displays.spiroDisplay)>()                                     { return displays.spiroDisplay; }
template<> decltype(displays.starFieldDisplay)                                 &getRefByType<decltype(displays.starFieldDisplay)>()                                 { return displays.starFieldDisplay; }
template<> decltype(displays.statusDisplay)                                    &getRefByType<decltype(displays.statusDisplay)>()                                    { return displays.statusDisplay; }
template<> decltype(displays.versionDisplay)                                   &getRefByType<decltype(displays.versionDisplay)>()                                   { return displays.versionDisplay; }

template<> decltype(displays.changeFrontFreq)                                  &getRefByType<decltype(displays.changeFrontFreq)>()                                  { return displays.changeFrontFreq; }
template<> decltype(displays.changeFrontPattern)                               &getRefByType<decltype(displays.changeFrontPattern)>()                               { return displays.changeFrontPattern; }
template<> decltype(displays.changeBackFreq)                                   &getRefByType<decltype(displays.changeBackFreq)>()                                   { return displays.changeBackFreq; }
template<> decltype(displays.changeBackPattern)                                &getRefByType<decltype(displays.changeBackPattern)>()                                { return displays.changeBackPattern; }

template<> decltype(displays.changeIMotMax)                                    &getRefByType<decltype(displays.changeIMotMax)>()                                    { return displays.changeIMotMax; }
template<> decltype(displays.changeIDcMax)                                     &getRefByType<decltype(displays.changeIDcMax)>()                                     { return displays.changeIDcMax; }
template<> decltype(displays.changeNMotMax)                                    &getRefByType<decltype(displays.changeNMotMax)>()                                    { return displays.changeNMotMax; }
template<> decltype(displays.changeFieldWeakMax)                               &getRefByType<decltype(displays.changeFieldWeakMax)>()                               { return displays.changeFieldWeakMax; }
template<> decltype(displays.changePhaseAdvMax)                                &getRefByType<decltype(displays.changePhaseAdvMax)>()                                { return displays.changePhaseAdvMax; }

template<> decltype(displays.changeDefaultModeCtrlTyp)                         &getRefByType<decltype(displays.changeDefaultModeCtrlTyp)>()                         { return displays.changeDefaultModeCtrlTyp; }
template<> decltype(displays.changeDefaultModeCtrlMod)                         &getRefByType<decltype(displays.changeDefaultModeCtrlMod)>()                         { return displays.changeDefaultModeCtrlMod; }
template<> decltype(displays.changeDefaultModeEnableFieldWeakeningSmoothening) &getRefByType<decltype(displays.changeDefaultModeEnableFieldWeakeningSmoothening)>() { return displays.changeDefaultModeEnableFieldWeakeningSmoothening; }
template<> decltype(displays.changeDefaultModeWeakeningSmoothening)            &getRefByType<decltype(displays.changeDefaultModeWeakeningSmoothening)>()            { return displays.changeDefaultModeWeakeningSmoothening; }
template<> decltype(displays.changeDefaultModeFrontPercentage)                 &getRefByType<decltype(displays.changeDefaultModeFrontPercentage)>()                 { return displays.changeDefaultModeFrontPercentage; }
template<> decltype(displays.changeDefaultModeBackPercentage)                  &getRefByType<decltype(displays.changeDefaultModeBackPercentage)>()                  { return displays.changeDefaultModeBackPercentage; }
template<> decltype(displays.changeDefaultModeAddSchwelle)                     &getRefByType<decltype(displays.changeDefaultModeAddSchwelle)>()                     { return displays.changeDefaultModeAddSchwelle; }
template<> decltype(displays.changeDefaultModeGas1Wert)                        &getRefByType<decltype(displays.changeDefaultModeGas1Wert)>()                        { return displays.changeDefaultModeGas1Wert; }
template<> decltype(displays.changeDefaultModeGas2Wert)                        &getRefByType<decltype(displays.changeDefaultModeGas2Wert)>()                        { return displays.changeDefaultModeGas2Wert; }
template<> decltype(displays.changeDefaultModeBrems1Wert)                      &getRefByType<decltype(displays.changeDefaultModeBrems1Wert)>()                      { return displays.changeDefaultModeBrems1Wert; }
template<> decltype(displays.changeDefaultModeBrems2Wert)                      &getRefByType<decltype(displays.changeDefaultModeBrems2Wert)>()                      { return displays.changeDefaultModeBrems2Wert; }

template<> decltype(displays.changeFrontLeftEnabled)                           &getRefByType<decltype(displays.changeFrontLeftEnabled)>()                           { return displays.changeFrontLeftEnabled; }
template<> decltype(displays.changeFrontRightEnabled)                          &getRefByType<decltype(displays.changeFrontRightEnabled)>()                          { return displays.changeFrontRightEnabled; }
template<> decltype(displays.changeBackLeftEnabled)                            &getRefByType<decltype(displays.changeBackLeftEnabled)>()                            { return displays.changeBackLeftEnabled; }
template<> decltype(displays.changeBackRightEnabled)                           &getRefByType<decltype(displays.changeBackRightEnabled)>()                           { return displays.changeBackRightEnabled; }

template<> decltype(displays.changeFrontLeftInverted)                          &getRefByType<decltype(displays.changeFrontLeftInverted)>()                          { return displays.changeFrontLeftInverted; }
template<> decltype(displays.changeFrontRightInverted)                         &getRefByType<decltype(displays.changeFrontRightInverted)>()                         { return displays.changeFrontRightInverted; }
template<> decltype(displays.changeBackLeftInverted)                           &getRefByType<decltype(displays.changeBackLeftInverted)>()                           { return displays.changeBackLeftInverted; }
template<> decltype(displays.changeBackRightInverted)                          &getRefByType<decltype(displays.changeBackRightInverted)>()                          { return displays.changeBackRightInverted; }

template<> decltype(displays.changeFrontLed)                                   &getRefByType<decltype(displays.changeFrontLed)>()                                   { return displays.changeFrontLed; }
template<> decltype(displays.changeBackLed)                                    &getRefByType<decltype(displays.changeBackLed)>()                                    { return displays.changeBackLed; }

template<> decltype(displays.changeManualModeCtrlTyp)                          &getRefByType<decltype(displays.changeManualModeCtrlTyp)>()                          { return displays.changeManualModeCtrlTyp; }
template<> decltype(displays.changeManualModeCtrlMod)                          &getRefByType<decltype(displays.changeManualModeCtrlMod)>()                          { return displays.changeManualModeCtrlMod; }

template<> decltype(displays.changeGasMin)                                     &getRefByType<decltype(displays.changeGasMin)>()                                     { return displays.changeGasMin; }
template<> decltype(displays.changeGasMax)                                     &getRefByType<decltype(displays.changeGasMax)>()                                     { return displays.changeGasMax; }
template<> decltype(displays.changeBremsMin)                                   &getRefByType<decltype(displays.changeBremsMin)>()                                   { return displays.changeBremsMin; }
template<> decltype(displays.changeBremsMax)                                   &getRefByType<decltype(displays.changeBremsMax)>()                                   { return displays.changeBremsMax; }

void deconstructScreen()
{
    if (currentDisplay)
    {
        currentDisplay->stop();
        currentDisplay->~Display();
        currentDisplay = nullptr;
    }
}

template<typename T>
void switchScreenImpl()
{
    deconstructScreen();

    T &ref = getRefByType<T>();
    new (&ref) T;
    currentDisplay = &ref;
    ref.start();
    ref.redraw();
}

std::function<void()> changeScreenCallback;

template<typename T>
void switchScreen()
{
    if (currentDisplay)
        changeScreenCallback = switchScreenImpl<T>;
    else
        switchScreenImpl<T>();
}

void initScreen()
{
    tft.init();
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setRotation(0);
    tft.drawString("Booting...", 32, 64, 4);
}

void updateDisplay()
{
    currentDisplay->update();
    if (changeScreenCallback)
    {
        changeScreenCallback();
        changeScreenCallback = {};
    }
}

void redrawDisplay()
{
    currentDisplay->redraw();
}

void printMemoryUsage(){
    std::map<int, std::set<const char *>> test;

    test[sizeof(displays)].insert("displays");
    test[sizeof(displays.bluetoothSettingsMenu)].insert("displays.bluetoothSettingsMenu");
    test[sizeof(displays.bluetoothModeSettingsMenu)].insert("displays.bluetoothModeSettingsMenu");
    test[sizeof(displays.buzzerMenu)].insert("displays.buzzerMenu");
    test[sizeof(displays.commonSettingsMenu)].insert("displays.commonSettingsMenu");
    test[sizeof(displays.debugMenu)].insert("displays.debugMenu");
    test[sizeof(displays.defaultModeSettingsMenu)].insert("displays.defaultModeSettingsMenu");
    test[sizeof(displays.demosMenu)].insert("displays.demosMenu");
    test[sizeof(displays.dynamicDebugMenu)].insert("displays.dynamicDebugMenu");
    test[sizeof(displays.enableMenu)].insert("displays.enableMenu");
    test[sizeof(displays.invertMenu)].insert("displays.invertMenu");
    test[sizeof(displays.mainMenu)].insert("displays.mainMenu");
    test[sizeof(displays.tempomatModeSettingsMenu)].insert("displays.tempomatModeSettingsMenu");
    test[sizeof(displays.potiSettingsMenu)].insert("displays.potiSettingsMenu");
    test[sizeof(displays.selectModeMenu)].insert("displays.selectModeMenu");
    test[sizeof(displays.settingsMenu)].insert("displays.settingsMenu");

    test[sizeof(displays.gameOfLifeDisplay)].insert("displays.gameOfLifeDisplay");
    test[sizeof(displays.metersDisplay)].insert("displays.metersDisplay");
    test[sizeof(displays.pingPongDisplay)].insert("displays.pingPongDisplay");
    test[sizeof(displays.spiroDisplay)].insert("displays.spiroDisplay");
    test[sizeof(displays.starFieldDisplay)].insert("displays.starFieldDisplay");
    test[sizeof(displays.statusDisplay)].insert("displays.statusDisplay");
    test[sizeof(displays.versionDisplay)].insert("displays.versionDisplay");

    test[sizeof(displays.changeFrontFreq)].insert("changeFrontFreq");
    test[sizeof(displays.changeFrontPattern)].insert("changeFrontPattern");
    test[sizeof(displays.changeBackFreq)].insert("changeBackFreq");
    test[sizeof(displays.changeBackPattern)].insert("changeBackPattern");
    test[sizeof(displays.changeIMotMax)].insert("changeIMotMax");
    test[sizeof(displays.changeIDcMax)].insert("changeIDcMax");
    test[sizeof(displays.changeNMotMax)].insert("changeNMotMax");
    test[sizeof(displays.changeFieldWeakMax)].insert("changeFieldWeakMax");
    test[sizeof(displays.changePhaseAdvMax)].insert("changePhaseAdvMax");
    test[sizeof(displays.changeDefaultModeCtrlTyp)].insert("changeDefaultModeCtrlTyp");
    test[sizeof(displays.changeDefaultModeCtrlMod)].insert("changeDefaultModeCtrlMod");
    test[sizeof(displays.changeDefaultModeEnableFieldWeakeningSmoothening)].insert("changeDefaultModeEnableFieldWeakeningSmoothening");
    test[sizeof(displays.changeDefaultModeWeakeningSmoothening)].insert("changeDefaultModeWeakeningSmoothening");
    test[sizeof(displays.changeDefaultModeFrontPercentage)].insert("changeDefaultModeFrontPercentage");
    test[sizeof(displays.changeDefaultModeBackPercentage)].insert("changeDefaultModeBackPercentage");
    test[sizeof(displays.changeDefaultModeAddSchwelle)].insert("changeDefaultModeAddSchwelle");
    test[sizeof(displays.changeDefaultModeGas1Wert)].insert("changeDefaultModeGas1Wert");
    test[sizeof(displays.changeDefaultModeGas2Wert)].insert("changeDefaultModeGas2Wert");
    test[sizeof(displays.changeDefaultModeBrems1Wert)].insert("changeDefaultModeBrems1Wert");
    test[sizeof(displays.changeDefaultModeBrems2Wert)].insert("changeDefaultModeBrems2Wert");
    test[sizeof(displays.changeFrontLeftEnabled)].insert("changeFrontLeftEnabled");
    test[sizeof(displays.changeFrontRightEnabled)].insert("changeFrontRightEnabled");
    test[sizeof(displays.changeBackLeftEnabled)].insert("changeBackLeftEnabled");
    test[sizeof(displays.changeBackRightEnabled)].insert("changeBackRightEnabled");
    test[sizeof(displays.changeFrontLeftInverted)].insert("changeFrontLeftInverted");
    test[sizeof(displays.changeFrontRightInverted)].insert("changeFrontRightInverted");
    test[sizeof(displays.changeBackLeftInverted)].insert("changeBackLeftInverted");
    test[sizeof(displays.changeBackRightInverted)].insert("changeBackRightInverted");
    test[sizeof(displays.changeFrontLed)].insert("changeFrontLed");
    test[sizeof(displays.changeBackLed)].insert("changeBackLed");
    test[sizeof(displays.changeManualModeCtrlTyp)].insert("changeManualModeCtrlTyp");
    test[sizeof(displays.changeManualModeCtrlMod)].insert("changeManualModeCtrlMod");
    test[sizeof(displays.changeGasMin)].insert("changeGasMin");
    test[sizeof(displays.changeGasMax)].insert("changeGasMax");
    test[sizeof(displays.changeBremsMin)].insert("changeBremsMin");
    test[sizeof(displays.changeBremsMax)].insert("changeBremsMax");

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
