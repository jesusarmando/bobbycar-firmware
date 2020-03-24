#include <Arduino.h>

#include <HardwareSerial.h>
#include <WiFi.h>

#include <array>
#include <algorithm>
#include <functional>
#include <cstdint>

#include "../../common.h"

#include "globals.h"
#include "rotary.h"
#include "webhandler.h"
#include "displays/menus/mainmenu.h"
#include "modes/defaultmode.h"

namespace {
struct {
    AsyncWebServer server{80};
    WebHandler handler;
} web;

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

void deconstructScreen() { if (currentDisplay) { currentDisplay->~Display(); currentDisplay = nullptr; } }
template<> void switchScreen<BluetoothModeSettingsMenu>() { deconstructScreen(); new (&displays.bluetoothModeSettingsMenu) BluetoothModeSettingsMenu; currentDisplay = &displays.bluetoothModeSettingsMenu; }
template<> void switchScreen<BuzzerMenu>() { deconstructScreen(); new (&displays.buzzerMenu) BuzzerMenu; currentDisplay = &displays.buzzerMenu; }
template<> void switchScreen<CommonSettingsMenu>() { deconstructScreen(); new (&displays.commonSettingsMenu) CommonSettingsMenu; currentDisplay = &displays.commonSettingsMenu; }
template<> void switchScreen<DefaultModeSettingsMenu>() { deconstructScreen(); new (&displays.defaultModeSettingsMenu) DefaultModeSettingsMenu; currentDisplay = &displays.defaultModeSettingsMenu; }
template<> void switchScreen<DemosMenu>() { deconstructScreen(); new (&displays.demosMenu) DemosMenu; currentDisplay = &displays.demosMenu; }
template<> void switchScreen<EnableMenu>() { deconstructScreen(); new (&displays.enableMenu) EnableMenu; currentDisplay = &displays.enableMenu; }
template<> void switchScreen<InvertMenu>() { deconstructScreen(); new (&displays.invertMenu) InvertMenu; currentDisplay = &displays.invertMenu; }
template<> void switchScreen<MainMenu>() { deconstructScreen(); new (&displays.mainMenu) MainMenu; currentDisplay = &displays.mainMenu; }
template<> void switchScreen<ManualModeSettingsMenu>() { deconstructScreen(); new (&displays.manualModeSettingsMenu) ManualModeSettingsMenu; currentDisplay = &displays.manualModeSettingsMenu; }
template<> void switchScreen<PotiSettingsMenu>() { deconstructScreen(); new (&displays.potiSettingsMenu) PotiSettingsMenu; currentDisplay = &displays.potiSettingsMenu; }
template<> void switchScreen<SelectModeMenu>() { deconstructScreen(); new (&displays.selectModeMenu) SelectModeMenu; currentDisplay = &displays.selectModeMenu; }
template<> void switchScreen<SettingsMenu>() { deconstructScreen(); new (&displays.settingsMenu) SettingsMenu; currentDisplay = &displays.settingsMenu; }
template<> void switchScreen<GameOfLifeDisplay>() { deconstructScreen(); new (&displays.gameOfLifeDisplay) GameOfLifeDisplay; currentDisplay = &displays.gameOfLifeDisplay; }
template<> void switchScreen<MetersDisplay>() { deconstructScreen(); new (&displays.metersDisplay) MetersDisplay; currentDisplay = &displays.metersDisplay; }
template<> void switchScreen<PingPongDisplay>() { deconstructScreen(); new (&displays.pingPongDisplay) PingPongDisplay; currentDisplay = &displays.pingPongDisplay; }
template<> void switchScreen<SpiroDisplay>() { deconstructScreen(); new (&displays.spiroDisplay) SpiroDisplay; currentDisplay = &displays.spiroDisplay; }
template<> void switchScreen<StarfieldDisplay>() { deconstructScreen(); new (&displays.starFieldDisplay) StarfieldDisplay; currentDisplay = &displays.starFieldDisplay; }
template<> void switchScreen<StatusDisplay>() { deconstructScreen(); new (&displays.statusDisplay) StatusDisplay; currentDisplay = &displays.statusDisplay; }
template<> void switchScreen<SetDefaultModeEnableFieldWeakeningSmootheningDisplay>() { deconstructScreen(); new (&displays.setDefaultModeEnableFieldWeakeningSmootheningDisplay) SetDefaultModeEnableFieldWeakeningSmootheningDisplay; currentDisplay = &displays.setDefaultModeEnableFieldWeakeningSmootheningDisplay; }
template<> void switchScreen<SetFrontLeftEnabledDisplay>() { deconstructScreen(); new (&displays.setFrontLeftEnabledDisplay) SetFrontLeftEnabledDisplay; currentDisplay = &displays.setFrontLeftEnabledDisplay; }
template<> void switchScreen<SetFrontRightEnabledDisplay>() { deconstructScreen(); new (&displays.setFrontRightEnabledDisplay) SetFrontRightEnabledDisplay; currentDisplay = &displays.setFrontRightEnabledDisplay; }
template<> void switchScreen<SetBackLeftEnabledDisplay>() { deconstructScreen(); new (&displays.setBackLeftEnabledDisplay) SetBackLeftEnabledDisplay; currentDisplay = &displays.setBackLeftEnabledDisplay; }
template<> void switchScreen<SetBackRightEnabledDisplay>() { deconstructScreen(); new (&displays.setBackRightEnabledDisplay) SetBackRightEnabledDisplay; currentDisplay = &displays.setBackRightEnabledDisplay; }
template<> void switchScreen<SetFrontLeftInvertedDisplay>() { deconstructScreen(); new (&displays.setFrontLeftInvertedDisplay) SetFrontLeftInvertedDisplay; currentDisplay = &displays.setFrontLeftInvertedDisplay; }
template<> void switchScreen<SetFrontRightInvertedDisplay>() { deconstructScreen(); new (&displays.setFrontRightInvertedDisplay) SetFrontRightInvertedDisplay; currentDisplay = &displays.setFrontRightInvertedDisplay; }
template<> void switchScreen<SetBackLeftInvertedDisplay>() { deconstructScreen(); new (&displays.setBackLeftInvertedDisplay) SetBackLeftInvertedDisplay; currentDisplay = &displays.setBackLeftInvertedDisplay; }
template<> void switchScreen<SetBackRightInvertedDisplay>() { deconstructScreen(); new (&displays.setBackRightInvertedDisplay) SetBackRightInvertedDisplay; currentDisplay = &displays.setBackRightInvertedDisplay; }
template<> void switchScreen<SetFrontLedDisplay>() { deconstructScreen(); new (&displays.setFrontLedDisplay) SetFrontLedDisplay; currentDisplay = &displays.setFrontLedDisplay; }
template<> void switchScreen<SetBackLedDisplay>() { deconstructScreen(); new (&displays.setBackLedDisplay) SetBackLedDisplay; currentDisplay = &displays.setBackLedDisplay; }
template<> void switchScreen<SetDefaultModeCtrlModDisplay>() { deconstructScreen(); new (&displays.setDefaultModeCtrlModDisplay) SetDefaultModeCtrlModDisplay; currentDisplay = &displays.setDefaultModeCtrlModDisplay; }
template<> void switchScreen<SetManualModeCtrlModDisplay>() { deconstructScreen(); new (&displays.setManualModeCtrlModDisplay) SetManualModeCtrlModDisplay; currentDisplay = &displays.setManualModeCtrlModDisplay; }
template<> void switchScreen<SetDefaultModeCtrlTypDisplay>() { deconstructScreen(); new (&displays.setDefaultModeCtrlTypDisplay) SetDefaultModeCtrlTypDisplay; currentDisplay = &displays.setDefaultModeCtrlTypDisplay; }
template<> void switchScreen<SetManualModeCtrlTypDisplay>() { deconstructScreen(); new (&displays.setManualModeCtrlTypDisplay) SetManualModeCtrlTypDisplay; currentDisplay = &displays.setManualModeCtrlTypDisplay; }
template<> void switchScreen<SetFrontFreqDisplay>() { deconstructScreen(); new (&displays.setFrontFreqDisplay) SetFrontFreqDisplay; currentDisplay = &displays.setFrontFreqDisplay; }
template<> void switchScreen<SetFrontPatternDisplay>() { deconstructScreen(); new (&displays.setFrontPatternDisplay) SetFrontPatternDisplay; currentDisplay = &displays.setFrontPatternDisplay; }
template<> void switchScreen<SetBackFreqDisplay>() { deconstructScreen(); new (&displays.setBackFreqDisplay) SetBackFreqDisplay; currentDisplay = &displays.setBackFreqDisplay; }
template<> void switchScreen<SetBackPatternDisplay>() { deconstructScreen(); new (&displays.setBackPatternDisplay) SetBackPatternDisplay; currentDisplay = &displays.setBackPatternDisplay; }
template<> void switchScreen<SetIMotMaxDisplay>() { deconstructScreen(); new (&displays.setIMotMaxDisplay) SetIMotMaxDisplay; currentDisplay = &displays.setIMotMaxDisplay; }
template<> void switchScreen<SetIDcMaxDisplay>() { deconstructScreen(); new (&displays.setIDcMaxDisplay) SetIDcMaxDisplay; currentDisplay = &displays.setIDcMaxDisplay; }
template<> void switchScreen<SetNMotMaxDisplay>() { deconstructScreen(); new (&displays.setNMotMaxDisplay) SetNMotMaxDisplay; currentDisplay = &displays.setNMotMaxDisplay; }
template<> void switchScreen<SetFieldWeakMaxDisplay>() { deconstructScreen(); new (&displays.setFieldWeakMaxDisplay) SetFieldWeakMaxDisplay; currentDisplay = &displays.setFieldWeakMaxDisplay; }
template<> void switchScreen<SetPhaseAdvMaxDisplay>() { deconstructScreen(); new (&displays.setPhaseAdvMaxDisplay) SetPhaseAdvMaxDisplay; currentDisplay = &displays.setPhaseAdvMaxDisplay; }
template<> void switchScreen<SetDefaultModeWeakeningSmootheningDisplay>() { deconstructScreen(); new (&displays.setDefaultModeWeakeningSmootheningDisplay) SetDefaultModeWeakeningSmootheningDisplay; currentDisplay = &displays.setDefaultModeWeakeningSmootheningDisplay; }
template<> void switchScreen<SetDefaultModeFrontPercentageDisplay>() { deconstructScreen(); new (&displays.setDefaultModeFrontPercentageDisplay) SetDefaultModeFrontPercentageDisplay; currentDisplay = &displays.setDefaultModeFrontPercentageDisplay; }
template<> void switchScreen<SetDefaultModeBackPercentageDisplay>() { deconstructScreen(); new (&displays.setDefaultModeBackPercentageDisplay) SetDefaultModeBackPercentageDisplay; currentDisplay = &displays.setDefaultModeBackPercentageDisplay; }
template<> void switchScreen<SetDefaultModeAddSchwelleDisplay>() { deconstructScreen(); new (&displays.setDefaultModeAddSchwelleDisplay) SetDefaultModeAddSchwelleDisplay; currentDisplay = &displays.setDefaultModeAddSchwelleDisplay; }
template<> void switchScreen<SetDefaultModeGas1WertDisplay>() { deconstructScreen(); new (&displays.setDefaultModeGas1Wert) SetDefaultModeGas1WertDisplay; currentDisplay = &displays.setDefaultModeGas1Wert; }
template<> void switchScreen<SetDefaultModeGas2WertDisplay>() { deconstructScreen(); new (&displays.setDefaultModeGas2Wert) SetDefaultModeGas2WertDisplay; currentDisplay = &displays.setDefaultModeGas2Wert; }
template<> void switchScreen<SetDefaultModeBrems1WertDisplay>() { deconstructScreen(); new (&displays.setDefaultModeBrems1Wert) SetDefaultModeBrems1WertDisplay; currentDisplay = &displays.setDefaultModeBrems1Wert; }
template<> void switchScreen<SetDefaultModeBrems2WertDisplay>() { deconstructScreen(); new (&displays.setDefaultModeBrems2Wert) SetDefaultModeBrems2WertDisplay; currentDisplay = &displays.setDefaultModeBrems2Wert; }
template<> void switchScreen<SetGasMinDisplay>() { deconstructScreen(); new (&displays.setGasMinDisplay) SetGasMinDisplay; currentDisplay = &displays.setGasMinDisplay; }
template<> void switchScreen<SetGasMaxDisplay>() { deconstructScreen(); new (&displays.setGasMaxDisplay) SetGasMaxDisplay; currentDisplay = &displays.setGasMaxDisplay; }
template<> void switchScreen<SetBremsMinDisplay>() { deconstructScreen(); new (&displays.setBremsMinDisplay) SetBremsMinDisplay; currentDisplay = &displays.setBremsMinDisplay; }
template<> void switchScreen<SetBremsMaxDisplay>() { deconstructScreen(); new (&displays.setBremsMaxDisplay) SetBremsMaxDisplay; currentDisplay = &displays.setBremsMaxDisplay; }

ModeBase *lastMode{};
Display *lastDisplay{};

void handleDebugSerial()
{
    const auto status = WiFi.status();
    if (last_status != status)
    {
        Serial.print("Status changed to: ");
        Serial.println(toString(status));
        last_status = status;
    }

    const auto ip = WiFi.localIP();
    if (last_ip != ip)
    {
        Serial.print("IP changed to: ");
        Serial.println(ip.toString());
        last_ip = ip;
    }

    while(Serial.available())
    {
        const auto c = Serial.read();

        switch (c)
        {
        case 't':
        case 'T':
            power_toggle = !power_toggle;
            Serial.printf("power: %d\n", power_toggle);
            for (auto &controller : controllers)
                controller.command.poweroff = power_toggle;
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            for (auto &controller : controllers)
                controller.command.buzzer.freq = c-'0';
            break;
        case 'A':
            if (currentDisplay)
                currentDisplay->rotate(-1);
            break;
        case 'B':
            if (currentDisplay)
                currentDisplay->rotate(1);
            break;
        case ' ':
            if (currentDisplay)
            {
                currentDisplay->button(true);
                currentDisplay->button(false);
            }
            break;
        }
    }
}

class InputDispatcher {
public:
    void rotate(int offset) { if (currentDisplay) currentDisplay->rotate(offset); }
    void button(bool pressed) { if (currentDisplay) currentDisplay->button(pressed); }
};

Rotary<InputDispatcher, rotaryClkPin, rotaryDtPin, rotarySwPin> rotary;

void updateRotate() { rotary.updateRotate(); }
void updateSwitch() { rotary.updateSwitch(); }
}

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.println("setup()");

    tft.init();
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setRotation(0);
    tft.drawString("Booting...", 32, 64, 4);

    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP("bobbycar", "Passwort_123");
    //WiFi.begin("realraum", "r3alraum");
    WiFi.begin("McDonalds Free WiFi 2.4GHz", "Passwort_123");

    bluetoothSerial.begin("bobbycar");

    gasMin = defaultGasMin;
    gasMax = defaultGasMax;
    bremsMin = defaultBremsMin;
    bremsMax = defaultBremsMax;

    front.command.left.enable = defaultEnableFrontLeft;
    front.command.right.enable = defaultEnableFrontRight;
    back.command.left.enable = defaultEnableBackLeft;
    back.command.right.enable = defaultEnableBackRight;

    front.invertLeft = defaultInvertFrontLeft;
    front.invertRight = defaultInvertFrontRight;
    back.invertLeft = defaultInvertBackLeft;
    back.invertRight = defaultInvertBackRight;

    controllers[0].serial.begin(38400, SERIAL_8N1, rxPin1, txPin1);
    controllers[1].serial.begin(38400, SERIAL_8N1, rxPin2, txPin2);

    settings.iMotMax = defaultIMotMax;
    settings.iDcMax = defaultIDcMax;
    settings.nMotMax = defaultNMotMax;
    settings.fieldWeakMax = defaultFieldWeakMax;
    settings.phaseAdvMax = defaultPhaseAdvMax;

    for (auto &controller : controllers)
        controller.command.buzzer = {};

    modes::defaultMode.gas1_wert = defaultDefaultModeGas1Wert;
    modes::defaultMode.gas2_wert = defaultDefaultModeGas2Wert;
    modes::defaultMode.brems1_wert = defaultDefaultModeBrems1Wert;
    modes::defaultMode.brems2_wert = defaultDefaultModeBrems2Wert;

    currentMode = &modes::defaultMode;
    currentDisplay = &mainMenu.m_statusDisplay;

    Serial.print("The size of the main menu is: ");
    Serial.println(sizeof(mainMenu));

    web.server.addHandler(&web.handler);
    web.server.begin();

    attachInterrupt(decltype(rotary)::ClkPin, updateRotate, CHANGE);
    attachInterrupt(decltype(rotary)::SwPin, updateSwitch, CHANGE);
}

void loop()
{
    const auto now = millis();
    if (now - lastUpdate >= 1000/50)
    {
        constexpr auto times = 100;
        const auto read_n_times = [](int pin){
            analogRead(pin);
            double sum{};
            for (int i = 0; i < times; i++)
                sum += analogRead(pin);
            return sum/times;
        };

        raw_gas = read_n_times(gasPin);
        gas = scaleBetween<float>(raw_gas, gasMin, gasMax, 0., 1000.);

        raw_brems = read_n_times(bremsPin);
        brems = scaleBetween<float>(raw_brems, bremsMin, bremsMax, 0., 1000.);

        if (lastMode != currentMode)
        {
            if (lastMode)
                lastMode->stop();
            lastMode = currentMode;
            if (currentMode)
                currentMode->start();
        }

        if (currentMode)
            currentMode->update();

        lastUpdate = now;

        performance.current++;
    }

    if (lastDisplay != currentDisplay)
    {
        if (lastDisplay)
            lastDisplay->stop();
        lastDisplay = currentDisplay;
        if (currentDisplay)
        {
            currentDisplay->start();
            currentDisplay->redraw();
        }
    }

    if (currentDisplay && now - lastRedraw >= 1000/currentDisplay->framerate())
    {
        currentDisplay->redraw();
        lastRedraw = now;
    }

    if (now - performance.lastTime >= 1000)
    {
        performance.last = performance.current;
        performance.current = 0;
        performance.lastTime = now;
    }

    for (auto &controller : controllers)
        controller.parser.update();

    handleDebugSerial();
}
