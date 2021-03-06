#pragma once

#include "displays/menus/aboutmenu.h"
#include "displays/menus/accesspointwifisettingsmenu.h"
#include "displays/menus/bluetoothsettingsmenu.h"
#include "displays/menus/bluetoothmodesettingsmenu.h"
#include "displays/menus/bmsmenu.h"
#include "displays/menus/buzzermenu.h"
#include "displays/menus/commanddebugmenu.h"
#include "displays/menus/debugmenu.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "displays/menus/demosmenu.h"
#include "displays/menus/dynamicdebugmenu.h"
#include "displays/menus/enablemenu.h"
#include "displays/menus/feedbackdebugmenu.h"
#include "displays/menus/genericwifisettingsmenu.h"
#include "displays/menus/graphsmenu.h"
#include "displays/menus/hardwaresettingsmenu.h"
#include "displays/menus/invertmenu.h"
#include "displays/menus/larsmmodesettingsmenu.h"
#include "displays/menus/limitssettingsmenu.h"
#include "displays/menus/mainmenu.h"
#include "displays/menus/tempomatmodesettingsmenu.h"
#include "displays/menus/modessettingsmenu.h"
#include "displays/menus/motorfeedbackdebugmenu.h"
#include "displays/menus/motorstatedebugmenu.h"
#include "displays/menus/presetsmenu.h"
#include "displays/menus/potisettingsmenu.h"
#include "displays/menus/selectmodemenu.h"
#include "displays/menus/settingsmenu.h"
#include "displays/menus/stationwifisettingsmenu.h"
#include "displays/menus/websocketmodesettingsmenu.h"
#include "displays/menus/wifiscanmenu.h"
#include "displays/menus/wifisettingsmenu.h"
#include "displays/bmsdisplay.h"
#include "displays/calibratedisplay.h"
#include "displays/dualgraphdisplay.h"
#include "displays/gameoflifedisplay.h"
#include "displays/lockscreen.h"
#include "displays/matrixdisplay.h"
#include "displays/metersdisplay.h"
#include "displays/multigraphdisplay.h"
#include "displays/pingpongdisplay.h"
#include "displays/poweroffdisplay.h"
#include "displays/spirodisplay.h"
#include "displays/starfielddisplay.h"
#include "displays/statusdisplay.h"

#include "globals.h"
#include "utils.h"
#include "icons/logo.h"

namespace {
union X {
    X() {}
    ~X() { ((Display&)statusDisplay).~Display(); }

    AboutMenu aboutMenu;
    AccessPointWifiSettingsMenu accessPointWifiSettingsMenu;
    BluetoothSettingsMenu bluetoothSettingsMenu;
    BluetoothModeSettingsMenu bluetoothModeSettingsMenu;
    BmsMenu bmsMenu;
    BuzzerMenu buzzerMenu;
    FrontCommandDebugMenu frontCommandDebugMenu;
    BackCommandDebugMenu backCommandDebugMenu;
    DebugMenu debugMenu;
    DefaultModeSettingsMenu defaultModeSettingsMenu;
    DemosMenu demosMenu;
    DynamicDebugMenu dynamicDebugMenu;
    EnableMenu enableMenu;
    FrontFeedbackDebugMenu frontFeedbackDebugMenu;
    BackFeedbackDebugMenu backFeedbackDebugMenu;
    GenericWifiSettingsMenu genericWifiSettingsMenu;
    GraphsMenu graphsMenu;
    HardwareSettingsMenu hardwareSettingsMenu;
    InvertMenu invertMenu;
    LarsmModeSettingsMenu larsmModeSettingsMenu;
    LimitsSettingsMenu limitsSettingsMenu;
    MainMenu mainMenu;
    TempomatModeSettingsMenu tempomatModeSettingsMenu;
    ModesSettingsMenu modesSettingsMenu;
    FrontLeftMotorStateDebugMenu frontLeftMotorStateDebugMenu;
    FrontRightMotorStateDebugMenu frontRightMotorStateDebugMenu;
    BackLeftMotorStateDebugMenu backLeftMotorStateDebugMenu;
    BackRightMotorStateDebugMenu backRightMotorStateDebugMenu;
    FrontLeftMotorFeedbackDebugMenu frontLeftMotorFeedbackDebugMenu;
    FrontRightMotorFeedbackDebugMenu frontRightMotorFeedbackDebugMenu;
    BackLeftMotorFeedbackDebugMenu backLeftMotorFeedbackDebugMenu;
    BackRightMotorFeedbackDebugMenu backRightMotorFeedbackDebugMenu;
    PotiSettingsMenu potiSettingsMenu;
    PresetsMenu presetsMenu;
    SelectModeMenu selectModeMenu;
    SettingsMenu settingsMenu;
    StationWifiSettingsMenu stationWifiSettingsMenu;
    WebsocketModeSettingsMenu websocketModeSettingsMenu;
    WifiScanMenu wifiScanMenu;
    WifiSettingsMenu wifiSettingsMenu;

    BmsDisplay bmsDisplay;
    CalibrateDisplay calibrateDisplay;
    DualGraphDisplay dualGraphDisplay;
    GameOfLifeDisplay gameOfLifeDisplay;
    Lockscreen lockScreen;
    MatrixDisplay matrixDisplay;
    MetersDisplay metersDisplay;
    MultiGraphDisplay multiGraphDisplay;
    PingPongDisplay pingPongDisplay;
    PoweroffDisplay poweroffDisplay;
    SpiroDisplay spiroDisplay;
    StarfieldDisplay starFieldDisplay;
    StatusDisplay statusDisplay;

    FrontFreqChangeScreen changeFrontFreq;
    FrontPatternChangeScreen changeFrontPattern;
    BackFreqChangeScreen changeBackFreq;
    BackPatternChangeScreen changeBackPattern;

    IMotMaxChangeScreen changeIMotMax;
    IDcMaxChangeScreen changeIDcMax;
    NMotMaxKmhChangeScreen changeNMotMaxKmh;
    NMotMaxRpmChangeScreen changeNMotMaxRpm;
    FieldWeakMaxChangeScreen changeFieldWeakMax;
    PhaseAdvMaxChangeScreen changePhaseAdvMax;

    WheelDiameterMmChangeScreen wheelDiameterMmChangeScreen;
    WheelDiameterInchChangeScreen wheelDiameterInchChangeScreen;
    NumMagnetPolesChangeScreen numMagnetPolesChangeScreen;

    DefaultModeCtrlTypChangeDisplay changeDefaultModeCtrlTyp;
    DefaultModeCtrlModChangeDisplay changeDefaultModeCtrlMod;
    DefaultModeSmoothingChangeDisplay changeDefaultModeSmoothing;
    DefaultModeFrontPercentageChangeDisplay changeDefaultModeFrontPercentage;
    DefaultModeBackPercentageChangeDisplay changeDefaultModeBackPercentage;
    DefaultModeAddSchwelleChangeDisplay changeDefaultModeAddSchwelle;
    DefaultModeGas1WertChangeDisplay changeDefaultModeGas1Wert;
    DefaultModeGas2WertChangeDisplay changeDefaultModeGas2Wert;
    DefaultModeBrems1WertChangeDisplay changeDefaultModeBrems1Wert;
    DefaultModeBrems2WertChangeDisplay changeDefaultModeBrems2Wert;

    TempomatModeCtrlTypChangeScreen changeManualModeCtrlTyp;
    TempomatModeCtrlModChangeScreen changeManualModeCtrlMod;

    LarsmModeModeChangeDisplay larsmModeModeChangeDisplay;
    LarsmModeIterationsChangeDisplay larsmModeIterationsChangeDisplay;

    SampleCountChangeScreen sampleCountChangeScreen;
    GasMinChangeScreen changeGasMin;
    GasMaxChangeScreen changeGasMax;
    BremsMinChangeScreen changeBremsMin;
    BremsMaxChangeScreen changeBremsMax;

    WifiModeChangeScreen wifiModeChangeScreen;
    WifiTxPowerChangeScreen wifiTxPowerChangeScreen;

    GasGraphDisplay gasGraphDisplay;
    BremsGraphDisplay bremsGraphDisplay;
    AvgSpeedGraphDisplay avgSpeedGraphDisplay;
    AvgSpeedKmhGraphDisplay avgSpeedKmhGraphDisplay;
    SumCurrentGraphDisplay sumCurrentGraphDisplay;
    FrontVoltageGraphDisplay frontVoltageGraphDisplay;
    BackVoltageGraphDisplay backVoltageGraphDisplay;
} displays;

template<typename T> T &getRefByType() = delete;
template<> decltype(displays.aboutMenu)                                        &getRefByType<decltype(displays.aboutMenu)>()                                        { return displays.aboutMenu; }
template<> decltype(displays.accessPointWifiSettingsMenu)                      &getRefByType<decltype(displays.accessPointWifiSettingsMenu)>()                      { return displays.accessPointWifiSettingsMenu; }
template<> decltype(displays.bluetoothSettingsMenu)                            &getRefByType<decltype(displays.bluetoothSettingsMenu)>()                            { return displays.bluetoothSettingsMenu; }
template<> decltype(displays.bluetoothModeSettingsMenu)                        &getRefByType<decltype(displays.bluetoothModeSettingsMenu)>()                        { return displays.bluetoothModeSettingsMenu; }
template<> decltype(displays.bmsMenu)                                          &getRefByType<decltype(displays.bmsMenu)>()                                          { return displays.bmsMenu; }
template<> decltype(displays.buzzerMenu)                                       &getRefByType<decltype(displays.buzzerMenu)>()                                       { return displays.buzzerMenu; }
template<> decltype(displays.frontCommandDebugMenu)                            &getRefByType<decltype(displays.frontCommandDebugMenu)>()                            { return displays.frontCommandDebugMenu; }
template<> decltype(displays.backCommandDebugMenu)                             &getRefByType<decltype(displays.backCommandDebugMenu)>()                             { return displays.backCommandDebugMenu; }
template<> decltype(displays.debugMenu)                                        &getRefByType<decltype(displays.debugMenu)>()                                        { return displays.debugMenu; }
template<> decltype(displays.defaultModeSettingsMenu)                          &getRefByType<decltype(displays.defaultModeSettingsMenu)>()                          { return displays.defaultModeSettingsMenu; }
template<> decltype(displays.demosMenu)                                        &getRefByType<decltype(displays.demosMenu)>()                                        { return displays.demosMenu; }
template<> decltype(displays.dynamicDebugMenu)                                 &getRefByType<decltype(displays.dynamicDebugMenu)>()                                 { return displays.dynamicDebugMenu; }
template<> decltype(displays.enableMenu)                                       &getRefByType<decltype(displays.enableMenu)>()                                       { return displays.enableMenu; }
template<> decltype(displays.frontFeedbackDebugMenu)                           &getRefByType<decltype(displays.frontFeedbackDebugMenu)>()                           { return displays.frontFeedbackDebugMenu; }
template<> decltype(displays.backFeedbackDebugMenu)                            &getRefByType<decltype(displays.backFeedbackDebugMenu)>()                            { return displays.backFeedbackDebugMenu; }
template<> decltype(displays.genericWifiSettingsMenu)                          &getRefByType<decltype(displays.genericWifiSettingsMenu)>()                          { return displays.genericWifiSettingsMenu; }
template<> decltype(displays.graphsMenu)                                       &getRefByType<decltype(displays.graphsMenu)>()                                       { return displays.graphsMenu; }
template<> decltype(displays.hardwareSettingsMenu)                             &getRefByType<decltype(displays.hardwareSettingsMenu)>()                             { return displays.hardwareSettingsMenu; }
template<> decltype(displays.invertMenu)                                       &getRefByType<decltype(displays.invertMenu)>()                                       { return displays.invertMenu; }
template<> decltype(displays.larsmModeSettingsMenu)                            &getRefByType<decltype(displays.larsmModeSettingsMenu)>()                            { return displays.larsmModeSettingsMenu; }
template<> decltype(displays.limitsSettingsMenu)                               &getRefByType<decltype(displays.limitsSettingsMenu)>()                               { return displays.limitsSettingsMenu; }
template<> decltype(displays.mainMenu)                                         &getRefByType<decltype(displays.mainMenu)>()                                         { return displays.mainMenu; }
template<> decltype(displays.tempomatModeSettingsMenu)                         &getRefByType<decltype(displays.tempomatModeSettingsMenu)>()                         { return displays.tempomatModeSettingsMenu; }
template<> decltype(displays.modesSettingsMenu)                                &getRefByType<decltype(displays.modesSettingsMenu)>()                                { return displays.modesSettingsMenu; }
template<> decltype(displays.frontLeftMotorStateDebugMenu)                     &getRefByType<decltype(displays.frontLeftMotorStateDebugMenu)>()                     { return displays.frontLeftMotorStateDebugMenu; }
template<> decltype(displays.frontRightMotorStateDebugMenu)                    &getRefByType<decltype(displays.frontRightMotorStateDebugMenu)>()                    { return displays.frontRightMotorStateDebugMenu; }
template<> decltype(displays.backLeftMotorStateDebugMenu)                      &getRefByType<decltype(displays.backLeftMotorStateDebugMenu)>()                      { return displays.backLeftMotorStateDebugMenu; }
template<> decltype(displays.backRightMotorStateDebugMenu)                     &getRefByType<decltype(displays.backRightMotorStateDebugMenu)>()                     { return displays.backRightMotorStateDebugMenu; }
template<> decltype(displays.frontLeftMotorFeedbackDebugMenu)                  &getRefByType<decltype(displays.frontLeftMotorFeedbackDebugMenu)>()                  { return displays.frontLeftMotorFeedbackDebugMenu; }
template<> decltype(displays.frontRightMotorFeedbackDebugMenu)                 &getRefByType<decltype(displays.frontRightMotorFeedbackDebugMenu)>()                 { return displays.frontRightMotorFeedbackDebugMenu; }
template<> decltype(displays.backLeftMotorFeedbackDebugMenu)                   &getRefByType<decltype(displays.backLeftMotorFeedbackDebugMenu)>()                   { return displays.backLeftMotorFeedbackDebugMenu; }
template<> decltype(displays.backRightMotorFeedbackDebugMenu)                  &getRefByType<decltype(displays.backRightMotorFeedbackDebugMenu)>()                  { return displays.backRightMotorFeedbackDebugMenu; }
template<> decltype(displays.potiSettingsMenu)                                 &getRefByType<decltype(displays.potiSettingsMenu)>()                                 { return displays.potiSettingsMenu; }
template<> decltype(displays.presetsMenu)                                      &getRefByType<decltype(displays.presetsMenu)>()                                      { return displays.presetsMenu; }
template<> decltype(displays.selectModeMenu)                                   &getRefByType<decltype(displays.selectModeMenu)>()                                   { return displays.selectModeMenu; }
template<> decltype(displays.settingsMenu)                                     &getRefByType<decltype(displays.settingsMenu)>()                                     { return displays.settingsMenu; }
template<> decltype(displays.stationWifiSettingsMenu)                          &getRefByType<decltype(displays.stationWifiSettingsMenu)>()                          { return displays.stationWifiSettingsMenu; }
template<> decltype(displays.websocketModeSettingsMenu)                        &getRefByType<decltype(displays.websocketModeSettingsMenu)>()                        { return displays.websocketModeSettingsMenu; }
template<> decltype(displays.wifiScanMenu)                                     &getRefByType<decltype(displays.wifiScanMenu)>()                                     { return displays.wifiScanMenu; }
template<> decltype(displays.wifiSettingsMenu)                                 &getRefByType<decltype(displays.wifiSettingsMenu)>()                                 { return displays.wifiSettingsMenu; }

template<> decltype(displays.bmsDisplay)                                       &getRefByType<decltype(displays.bmsDisplay)>()                                       { return displays.bmsDisplay; }
template<> decltype(displays.calibrateDisplay)                                 &getRefByType<decltype(displays.calibrateDisplay)>()                                 { return displays.calibrateDisplay; }
template<> decltype(displays.dualGraphDisplay)                                 &getRefByType<decltype(displays.dualGraphDisplay)>()                                 { return displays.dualGraphDisplay; }
template<> decltype(displays.gameOfLifeDisplay)                                &getRefByType<decltype(displays.gameOfLifeDisplay)>()                                { return displays.gameOfLifeDisplay; }
template<> decltype(displays.lockScreen)                                       &getRefByType<decltype(displays.lockScreen)>()                                       { return displays.lockScreen; }
template<> decltype(displays.matrixDisplay)                                    &getRefByType<decltype(displays.matrixDisplay)>()                                    { return displays.matrixDisplay; }
template<> decltype(displays.metersDisplay)                                    &getRefByType<decltype(displays.metersDisplay)>()                                    { return displays.metersDisplay; }
template<> decltype(displays.multiGraphDisplay)                                &getRefByType<decltype(displays.multiGraphDisplay)>()                                { return displays.multiGraphDisplay; }
template<> decltype(displays.pingPongDisplay)                                  &getRefByType<decltype(displays.pingPongDisplay)>()                                  { return displays.pingPongDisplay; }
template<> decltype(displays.poweroffDisplay)                                  &getRefByType<decltype(displays.poweroffDisplay)>()                                  { return displays.poweroffDisplay; }
template<> decltype(displays.spiroDisplay)                                     &getRefByType<decltype(displays.spiroDisplay)>()                                     { return displays.spiroDisplay; }
template<> decltype(displays.starFieldDisplay)                                 &getRefByType<decltype(displays.starFieldDisplay)>()                                 { return displays.starFieldDisplay; }
template<> decltype(displays.statusDisplay)                                    &getRefByType<decltype(displays.statusDisplay)>()                                    { return displays.statusDisplay; }

template<> decltype(displays.changeFrontFreq)                                  &getRefByType<decltype(displays.changeFrontFreq)>()                                  { return displays.changeFrontFreq; }
template<> decltype(displays.changeFrontPattern)                               &getRefByType<decltype(displays.changeFrontPattern)>()                               { return displays.changeFrontPattern; }
template<> decltype(displays.changeBackFreq)                                   &getRefByType<decltype(displays.changeBackFreq)>()                                   { return displays.changeBackFreq; }
template<> decltype(displays.changeBackPattern)                                &getRefByType<decltype(displays.changeBackPattern)>()                                { return displays.changeBackPattern; }

template<> decltype(displays.changeIMotMax)                                    &getRefByType<decltype(displays.changeIMotMax)>()                                    { return displays.changeIMotMax; }
template<> decltype(displays.changeIDcMax)                                     &getRefByType<decltype(displays.changeIDcMax)>()                                     { return displays.changeIDcMax; }
template<> decltype(displays.changeNMotMaxKmh)                                 &getRefByType<decltype(displays.changeNMotMaxKmh)>()                                 { return displays.changeNMotMaxKmh; }
template<> decltype(displays.changeNMotMaxRpm)                                 &getRefByType<decltype(displays.changeNMotMaxRpm)>()                                 { return displays.changeNMotMaxRpm; }
template<> decltype(displays.changeFieldWeakMax)                               &getRefByType<decltype(displays.changeFieldWeakMax)>()                               { return displays.changeFieldWeakMax; }
template<> decltype(displays.changePhaseAdvMax)                                &getRefByType<decltype(displays.changePhaseAdvMax)>()                                { return displays.changePhaseAdvMax; }

template<> decltype(displays.wheelDiameterMmChangeScreen)                      &getRefByType<decltype(displays.wheelDiameterMmChangeScreen)>()                      { return displays.wheelDiameterMmChangeScreen; }
template<> decltype(displays.wheelDiameterInchChangeScreen)                    &getRefByType<decltype(displays.wheelDiameterInchChangeScreen)>()                    { return displays.wheelDiameterInchChangeScreen; }
template<> decltype(displays.numMagnetPolesChangeScreen)                       &getRefByType<decltype(displays.numMagnetPolesChangeScreen)>()                       { return displays.numMagnetPolesChangeScreen; }

template<> decltype(displays.changeDefaultModeCtrlTyp)                         &getRefByType<decltype(displays.changeDefaultModeCtrlTyp)>()                         { return displays.changeDefaultModeCtrlTyp; }
template<> decltype(displays.changeDefaultModeCtrlMod)                         &getRefByType<decltype(displays.changeDefaultModeCtrlMod)>()                         { return displays.changeDefaultModeCtrlMod; }
template<> decltype(displays.changeDefaultModeSmoothing)                       &getRefByType<decltype(displays.changeDefaultModeSmoothing)>()                       { return displays.changeDefaultModeSmoothing; }
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

template<> decltype(displays.sampleCountChangeScreen)                          &getRefByType<decltype(displays.sampleCountChangeScreen)>()                          { return displays.sampleCountChangeScreen; }
template<> decltype(displays.changeGasMin)                                     &getRefByType<decltype(displays.changeGasMin)>()                                     { return displays.changeGasMin; }
template<> decltype(displays.changeGasMax)                                     &getRefByType<decltype(displays.changeGasMax)>()                                     { return displays.changeGasMax; }
template<> decltype(displays.changeBremsMin)                                   &getRefByType<decltype(displays.changeBremsMin)>()                                   { return displays.changeBremsMin; }
template<> decltype(displays.changeBremsMax)                                   &getRefByType<decltype(displays.changeBremsMax)>()                                   { return displays.changeBremsMax; }

template<> decltype(displays.wifiModeChangeScreen)                             &getRefByType<decltype(displays.wifiModeChangeScreen)>()                             { return displays.wifiModeChangeScreen; }
template<> decltype(displays.wifiTxPowerChangeScreen)                          &getRefByType<decltype(displays.wifiTxPowerChangeScreen)>()                          { return displays.wifiTxPowerChangeScreen; }

template<> decltype(displays.gasGraphDisplay)                                  &getRefByType<decltype(displays.gasGraphDisplay)>()                                  { return displays.gasGraphDisplay; }
template<> decltype(displays.bremsGraphDisplay)                                &getRefByType<decltype(displays.bremsGraphDisplay)>()                                { return displays.bremsGraphDisplay; }
template<> decltype(displays.avgSpeedGraphDisplay)                             &getRefByType<decltype(displays.avgSpeedGraphDisplay)>()                             { return displays.avgSpeedGraphDisplay; }
template<> decltype(displays.avgSpeedKmhGraphDisplay)                          &getRefByType<decltype(displays.avgSpeedKmhGraphDisplay)>()                          { return displays.avgSpeedKmhGraphDisplay; }
template<> decltype(displays.sumCurrentGraphDisplay)                           &getRefByType<decltype(displays.sumCurrentGraphDisplay)>()                           { return displays.sumCurrentGraphDisplay; }
template<> decltype(displays.frontVoltageGraphDisplay)                         &getRefByType<decltype(displays.frontVoltageGraphDisplay)>()                         { return displays.frontVoltageGraphDisplay; }
template<> decltype(displays.backVoltageGraphDisplay)                          &getRefByType<decltype(displays.backVoltageGraphDisplay)>()                          { return displays.backVoltageGraphDisplay; }

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
    ref.initScreen();
    ref.update();
    ref.redraw();
}

std::function<void()> changeScreenCallback;

template<typename T, typename... Args>
void switchScreen(Args&&... args)
{
    if (currentDisplay)
        changeScreenCallback = [&args...](){ switchScreenImpl<T>(std::forward<Args>(args)...); };
    else
        switchScreenImpl<T>(std::forward<Args>(args)...);
}

void initScreen()
{
    tft.init();
    tft.fillScreen(TFT_WHITE);
    tft.setTextColor(TFT_BLACK);
    tft.pushImage(0, 40, icons::logo.WIDTH, icons::logo.HEIGHT, icons::logo.buffer);
    tft.drawString("Bobbycar-OS", 32, 200, 4);
    tft.drawString("booting...", 32, 225, 4);
}

void updateDisplay()
{
    if (rotated)
    {
        const auto rotatedCopy = rotated;
        rotated = 0;

        if (currentDisplay)
            currentDisplay->rotate(rotatedCopy);
    }

    if (requestFullRedraw)
    {
        requestFullRedraw = false;

        tft.init();

        if (currentDisplay)
            currentDisplay->initScreen();
    }

    if (buttonLongPressed)
    {
        buttonLongPressed = false;
        Serial.println("todo: implement long press");
    }

    if (buttonPressed)
    {
        buttonPressed = false;

        if (currentDisplay)
            currentDisplay->button();
    }

    if (currentDisplay)
        currentDisplay->update();

    if (changeScreenCallback)
    {
        changeScreenCallback();
        changeScreenCallback = {};
    }
}

void redrawDisplay()
{
    if (currentDisplay)
        currentDisplay->redraw();
}
}
