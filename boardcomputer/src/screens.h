#pragma once

#include "displays/menus/accesspointwifisettingsmenu.h"
#include "displays/menus/bluetoothsettingsmenu.h"
#include "displays/menus/bluetoothmodesettingsmenu.h"
#include "displays/menus/buzzermenu.h"
#include "displays/menus/commonsettingsmenu.h"
#include "displays/menus/debugmenu.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "displays/menus/demosmenu.h"
#include "displays/menus/dynamicdebugmenu.h"
#include "displays/menus/enablemenu.h"
#include "displays/menus/genericwifisettingsmenu.h"
#include "displays/menus/invertmenu.h"
#include "displays/menus/larsmmodesettingsmenu.h"
#include "displays/menus/mainmenu.h"
#include "displays/menus/tempomatmodesettingsmenu.h"
#include "displays/menus/modessettingsmenu.h"
#include "displays/menus/potisettingsmenu.h"
#include "displays/menus/selectmodemenu.h"
#include "displays/menus/settingsmenu.h"
#include "displays/menus/stationwifisettingsmenu.h"
#include "displays/menus/websocketmodesettingsmenu.h"
#include "displays/menus/wifiscanmenu.h"
#include "displays/menus/wifisettingsmenu.h"
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
    AccessPointWifiSettingsMenu<WifiSettingsMenu<SettingsMenu<MainMenu>>> accessPointWifiSettingsMenu;
    BluetoothSettingsMenu<SettingsMenu<MainMenu>> bluetoothSettingsMenu;
    BluetoothModeSettingsMenu<ModesSettingsMenu<SettingsMenu<MainMenu>>> bluetoothModeSettingsMenu;
    BuzzerMenu<SettingsMenu<MainMenu>> buzzerMenu;
    CommonSettingsMenu<SettingsMenu<MainMenu>> commonSettingsMenu;
    DebugMenu<MainMenu> debugMenu;
    DefaultModeSettingsMenu<ModesSettingsMenu<SettingsMenu<MainMenu>>> defaultModeSettingsMenu;
    DemosMenu<MainMenu> demosMenu;
    DynamicDebugMenu<DebugMenu<MainMenu>> dynamicDebugMenu;
    EnableMenu<CommonSettingsMenu<SettingsMenu<MainMenu>>> enableMenu;
    GenericWifiSettingsMenu<WifiSettingsMenu<SettingsMenu<MainMenu>>> genericWifiSettingsMenu;
    InvertMenu<CommonSettingsMenu<SettingsMenu<MainMenu>>> invertMenu;
    LarsmModeSettingsMenu<ModesSettingsMenu<SettingsMenu<MainMenu>>> larsmModeSettingsMenu;
    TempomatModeSettingsMenu<ModesSettingsMenu<SettingsMenu<MainMenu>>> tempomatModeSettingsMenu;
    ModesSettingsMenu<SettingsMenu<MainMenu>> modesSettingsMenu;
    PotiSettingsMenu<SettingsMenu<MainMenu>> potiSettingsMenu;
    PresetsMenu<MainMenu> presetsMenu;
    SelectModeMenu<MainMenu> selectModeMenu;
    SettingsMenu<MainMenu> settingsMenu;
    StationWifiSettingsMenu<WifiSettingsMenu<SettingsMenu<MainMenu>>> stationWifiSettingsMenu;
    WebsocketModeSettingsMenu<ModesSettingsMenu<SettingsMenu<MainMenu>>> websocketModeSettingsMenu;
    WifiScanMenu<WifiSettingsMenu<SettingsMenu<MainMenu>>> wifiScanMenu;
    WifiSettingsMenu<SettingsMenu<MainMenu>> wifiSettingsMenu;

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

    FrontFreqChangeScreen<BuzzerMenu<SettingsMenu<MainMenu>>> changeFrontFreq;
    FrontPatternChangeScreen<BuzzerMenu<SettingsMenu<MainMenu>>> changeFrontPattern;
    BackFreqChangeScreen<BuzzerMenu<SettingsMenu<MainMenu>>> changeBackFreq;
    BackPatternChangeScreen<BuzzerMenu<SettingsMenu<MainMenu>>> changeBackPattern;

    IMotMaxChangeScreen<CommonSettingsMenu<SettingsMenu<MainMenu>>> changeIMotMax;
    IDcMaxChangeScreen<CommonSettingsMenu<SettingsMenu<MainMenu>>> changeIDcMax;
    NMotMaxKmhChangeScreen<CommonSettingsMenu<SettingsMenu<MainMenu>>> changeNMotMaxKmh;
    NMotMaxChangeScreen<CommonSettingsMenu<SettingsMenu<MainMenu>>> changeNMotMax;
    FieldWeakMaxChangeScreen<CommonSettingsMenu<SettingsMenu<MainMenu>>> changeFieldWeakMax;
    PhaseAdvMaxChangeScreen<CommonSettingsMenu<SettingsMenu<MainMenu>>> changePhaseAdvMax;

    DefaultModeCtrlTypChangeDisplay<DefaultModeSettingsMenu<ModesSettingsMenu<SettingsMenu<MainMenu>>>> changeDefaultModeCtrlTyp;
    DefaultModeCtrlModChangeDisplay<DefaultModeSettingsMenu<ModesSettingsMenu<SettingsMenu<MainMenu>>>> changeDefaultModeCtrlMod;
    DefaultModeWeakeningSmootheningChangeDisplay<DefaultModeSettingsMenu<ModesSettingsMenu<SettingsMenu<MainMenu>>>> changeDefaultModeWeakeningSmoothening;
    DefaultModeFrontPercentageChangeDisplay<DefaultModeSettingsMenu<ModesSettingsMenu<SettingsMenu<MainMenu>>>> changeDefaultModeFrontPercentage;
    DefaultModeBackPercentageChangeDisplay<DefaultModeSettingsMenu<ModesSettingsMenu<SettingsMenu<MainMenu>>>> changeDefaultModeBackPercentage;
    DefaultModeAddSchwelleChangeDisplay<DefaultModeSettingsMenu<ModesSettingsMenu<SettingsMenu<MainMenu>>>> changeDefaultModeAddSchwelle;
    DefaultModeGas1WertChangeDisplay<DefaultModeSettingsMenu<ModesSettingsMenu<SettingsMenu<MainMenu>>>> changeDefaultModeGas1Wert;
    DefaultModeGas2WertChangeDisplay<DefaultModeSettingsMenu<ModesSettingsMenu<SettingsMenu<MainMenu>>>> changeDefaultModeGas2Wert;
    DefaultModeBrems1WertChangeDisplay<DefaultModeSettingsMenu<ModesSettingsMenu<SettingsMenu<MainMenu>>>> changeDefaultModeBrems1Wert;
    DefaultModeBrems2WertChangeDisplay<DefaultModeSettingsMenu<ModesSettingsMenu<SettingsMenu<MainMenu>>>> changeDefaultModeBrems2Wert;

    TempomatModeCtrlTypChangeScreen<TempomatModeSettingsMenu<ModesSettingsMenu<SettingsMenu<MainMenu>>>> changeManualModeCtrlTyp;
    TempomatModeCtrlModChangeScreen<TempomatModeSettingsMenu<ModesSettingsMenu<SettingsMenu<MainMenu>>>> changeManualModeCtrlMod;

    LarsmModeModeChangeDisplay<LarsmModeSettingsMenu<ModesSettingsMenu<SettingsMenu<MainMenu>>>> larsmModeModeChangeDisplay;
    LarsmModeIterationsChangeDisplay<LarsmModeSettingsMenu<ModesSettingsMenu<SettingsMenu<MainMenu>>>> larsmModeIterationsChangeDisplay;

    GasMinChangeScreen<PotiSettingsMenu<SettingsMenu<MainMenu>>> changeGasMin;
    GasMaxChangeScreen<PotiSettingsMenu<SettingsMenu<MainMenu>>> changeGasMax;
    BremsMinChangeScreen<PotiSettingsMenu<SettingsMenu<MainMenu>>> changeBremsMin;
    BremsMaxChangeScreen<PotiSettingsMenu<SettingsMenu<MainMenu>>> changeBremsMax;

    WifiModeChangeScreen<GenericWifiSettingsMenu<WifiSettingsMenu<SettingsMenu<MainMenu>>>> wifiModeChangeScreen;
    WifiTxPowerChangeScreen<GenericWifiSettingsMenu<WifiSettingsMenu<SettingsMenu<MainMenu>>>> wifiTxPowerChangeScreen;
} displays;

using DefaultScreen = decltype(displays.statusDisplay);
//using DefaultScreen = decltype(displays.lockScreen);

template<typename T> T &getRefByType() = delete;
template<> decltype(displays.accessPointWifiSettingsMenu)                      &getRefByType<decltype(displays.accessPointWifiSettingsMenu)>()                      { return displays.accessPointWifiSettingsMenu; }
template<> decltype(displays.bluetoothSettingsMenu)                            &getRefByType<decltype(displays.bluetoothSettingsMenu)>()                            { return displays.bluetoothSettingsMenu; }
template<> decltype(displays.bluetoothModeSettingsMenu)                        &getRefByType<decltype(displays.bluetoothModeSettingsMenu)>()                        { return displays.bluetoothModeSettingsMenu; }
template<> decltype(displays.buzzerMenu)                                       &getRefByType<decltype(displays.buzzerMenu)>()                                       { return displays.buzzerMenu; }
template<> decltype(displays.commonSettingsMenu)                               &getRefByType<decltype(displays.commonSettingsMenu)>()                               { return displays.commonSettingsMenu; }
template<> decltype(displays.debugMenu)                                        &getRefByType<decltype(displays.debugMenu)>()                                        { return displays.debugMenu; }
template<> decltype(displays.defaultModeSettingsMenu)                          &getRefByType<decltype(displays.defaultModeSettingsMenu)>()                          { return displays.defaultModeSettingsMenu; }
template<> decltype(displays.demosMenu)                                        &getRefByType<decltype(displays.demosMenu)>()                                        { return displays.demosMenu; }
template<> decltype(displays.dynamicDebugMenu)                                 &getRefByType<decltype(displays.dynamicDebugMenu)>()                                 { return displays.dynamicDebugMenu; }
template<> decltype(displays.enableMenu)                                       &getRefByType<decltype(displays.enableMenu)>()                                       { return displays.enableMenu; }
template<> decltype(displays.genericWifiSettingsMenu)                          &getRefByType<decltype(displays.genericWifiSettingsMenu)>()                          { return displays.genericWifiSettingsMenu; }
template<> decltype(displays.invertMenu)                                       &getRefByType<decltype(displays.invertMenu)>()                                       { return displays.invertMenu; }
template<> decltype(displays.larsmModeSettingsMenu)                            &getRefByType<decltype(displays.larsmModeSettingsMenu)>()                            { return displays.larsmModeSettingsMenu; }
template<> decltype(displays.mainMenu)                                         &getRefByType<decltype(displays.mainMenu)>()                                         { return displays.mainMenu; }
template<> decltype(displays.tempomatModeSettingsMenu)                         &getRefByType<decltype(displays.tempomatModeSettingsMenu)>()                         { return displays.tempomatModeSettingsMenu; }
template<> decltype(displays.modesSettingsMenu)                                &getRefByType<decltype(displays.modesSettingsMenu)>()                                { return displays.modesSettingsMenu; }
template<> decltype(displays.potiSettingsMenu)                                 &getRefByType<decltype(displays.potiSettingsMenu)>()                                 { return displays.potiSettingsMenu; }
template<> decltype(displays.presetsMenu)                                      &getRefByType<decltype(displays.presetsMenu)>()                                      { return displays.presetsMenu; }
template<> decltype(displays.selectModeMenu)                                   &getRefByType<decltype(displays.selectModeMenu)>()                                   { return displays.selectModeMenu; }
template<> decltype(displays.settingsMenu)                                     &getRefByType<decltype(displays.settingsMenu)>()                                     { return displays.settingsMenu; }
template<> decltype(displays.stationWifiSettingsMenu)                          &getRefByType<decltype(displays.stationWifiSettingsMenu)>()                          { return displays.stationWifiSettingsMenu; }
template<> decltype(displays.websocketModeSettingsMenu)                        &getRefByType<decltype(displays.websocketModeSettingsMenu)>()                        { return displays.websocketModeSettingsMenu; }
template<> decltype(displays.wifiScanMenu)                                     &getRefByType<decltype(displays.wifiScanMenu)>()                                     { return displays.wifiScanMenu; }
template<> decltype(displays.wifiSettingsMenu)                                 &getRefByType<decltype(displays.wifiSettingsMenu)>()                                 { return displays.wifiSettingsMenu; }

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
template<> decltype(displays.changeNMotMaxKmh)                                 &getRefByType<decltype(displays.changeNMotMaxKmh)>()                                 { return displays.changeNMotMaxKmh; }
template<> decltype(displays.changeNMotMax)                                    &getRefByType<decltype(displays.changeNMotMax)>()                                    { return displays.changeNMotMax; }
template<> decltype(displays.changeFieldWeakMax)                               &getRefByType<decltype(displays.changeFieldWeakMax)>()                               { return displays.changeFieldWeakMax; }
template<> decltype(displays.changePhaseAdvMax)                                &getRefByType<decltype(displays.changePhaseAdvMax)>()                                { return displays.changePhaseAdvMax; }

template<> decltype(displays.changeDefaultModeCtrlTyp)                         &getRefByType<decltype(displays.changeDefaultModeCtrlTyp)>()                         { return displays.changeDefaultModeCtrlTyp; }
template<> decltype(displays.changeDefaultModeCtrlMod)                         &getRefByType<decltype(displays.changeDefaultModeCtrlMod)>()                         { return displays.changeDefaultModeCtrlMod; }
template<> decltype(displays.changeDefaultModeWeakeningSmoothening)            &getRefByType<decltype(displays.changeDefaultModeWeakeningSmoothening)>()            { return displays.changeDefaultModeWeakeningSmoothening; }
template<> decltype(displays.changeDefaultModeFrontPercentage)                 &getRefByType<decltype(displays.changeDefaultModeFrontPercentage)>()                 { return displays.changeDefaultModeFrontPercentage; }
template<> decltype(displays.changeDefaultModeBackPercentage)                  &getRefByType<decltype(displays.changeDefaultModeBackPercentage)>()                  { return displays.changeDefaultModeBackPercentage; }
template<> decltype(displays.changeDefaultModeAddSchwelle)                     &getRefByType<decltype(displays.changeDefaultModeAddSchwelle)>()                     { return displays.changeDefaultModeAddSchwelle; }
template<> decltype(displays.changeDefaultModeGas1Wert)                        &getRefByType<decltype(displays.changeDefaultModeGas1Wert)>()                        { return displays.changeDefaultModeGas1Wert; }
template<> decltype(displays.changeDefaultModeGas2Wert)                        &getRefByType<decltype(displays.changeDefaultModeGas2Wert)>()                        { return displays.changeDefaultModeGas2Wert; }
template<> decltype(displays.changeDefaultModeBrems1Wert)                      &getRefByType<decltype(displays.changeDefaultModeBrems1Wert)>()                      { return displays.changeDefaultModeBrems1Wert; }
template<> decltype(displays.changeDefaultModeBrems2Wert)                      &getRefByType<decltype(displays.changeDefaultModeBrems2Wert)>()                      { return displays.changeDefaultModeBrems2Wert; }

template<> decltype(displays.changeManualModeCtrlTyp)                          &getRefByType<decltype(displays.changeManualModeCtrlTyp)>()                          { return displays.changeManualModeCtrlTyp; }
template<> decltype(displays.changeManualModeCtrlMod)                          &getRefByType<decltype(displays.changeManualModeCtrlMod)>()                          { return displays.changeManualModeCtrlMod; }

template<> decltype(displays.larsmModeModeChangeDisplay)                       &getRefByType<decltype(displays.larsmModeModeChangeDisplay)>()                       { return displays.larsmModeModeChangeDisplay; }
template<> decltype(displays.larsmModeIterationsChangeDisplay)                 &getRefByType<decltype(displays.larsmModeIterationsChangeDisplay)>()                 { return displays.larsmModeIterationsChangeDisplay; }

template<> decltype(displays.changeGasMin)                                     &getRefByType<decltype(displays.changeGasMin)>()                                     { return displays.changeGasMin; }
template<> decltype(displays.changeGasMax)                                     &getRefByType<decltype(displays.changeGasMax)>()                                     { return displays.changeGasMax; }
template<> decltype(displays.changeBremsMin)                                   &getRefByType<decltype(displays.changeBremsMin)>()                                   { return displays.changeBremsMin; }
template<> decltype(displays.changeBremsMax)                                   &getRefByType<decltype(displays.changeBremsMax)>()                                   { return displays.changeBremsMax; }

template<> decltype(displays.wifiModeChangeScreen)                             &getRefByType<decltype(displays.wifiModeChangeScreen)>()                             { return displays.wifiModeChangeScreen; }
template<> decltype(displays.wifiTxPowerChangeScreen)                          &getRefByType<decltype(displays.wifiTxPowerChangeScreen)>()                          { return displays.wifiTxPowerChangeScreen; }

void deconstructScreen()
{
    if (currentDisplay)
    {
        currentDisplay->stop();
        currentDisplay->~Display();
        currentDisplay = nullptr;
    }
}

template<typename T, typename... Args>
void switchScreenImpl(Args&&... args)
{
    deconstructScreen();

    T &ref = getRefByType<T>();
    new (&ref) T{std::forward<Args>(args)...};
    currentDisplay = &ref;
    ref.start();
    ref.update();
    ref.redraw();
}

std::function<void()> changeScreenCallback;

template<typename T, typename... Args>
void switchScreen(Args&&... args)
{
    if (currentDisplay)
        changeScreenCallback = [args...](){ switchScreenImpl<T>(std::forward<Args>(args)...); };
    else
        switchScreenImpl<T>(std::forward<Args>(args)...);
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
}
