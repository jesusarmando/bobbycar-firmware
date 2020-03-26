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

#include "rotary.h"

namespace {
union X {
    X() {}
    ~X() { ((Display&)statusDisplay).~Display(); }

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

    GameOfLifeDisplay<DemosMenu> gameOfLifeDisplay;
    MetersDisplay<DemosMenu> metersDisplay;
    PingPongDisplay<DemosMenu> pingPongDisplay;
    SpiroDisplay<DemosMenu> spiroDisplay;
    StarfieldDisplay<DemosMenu> starFieldDisplay;
    StatusDisplay<MainMenu> statusDisplay;

    ChangeValueDisplay<uint8_t, FrontFreqAccessor, BuzzerMenu, TEXT_SETFRONTFREQ> changeFrontFreq;
    ChangeValueDisplay<uint8_t, FrontPatternAccessor, BuzzerMenu, TEXT_SETFRONTPATTERN> changeFrontPattern;
    ChangeValueDisplay<uint8_t, BackFreqAccessor, BuzzerMenu, TEXT_SETBACKFREQ> changeBackFreq;
    ChangeValueDisplay<uint8_t, BackPatternAccessor, BuzzerMenu, TEXT_SETBACKPATTERN> changeBackPattern;
    ChangeValueDisplay<int16_t, IMotMaxAccessor, CommonSettingsMenu, TEXT_SETIMOTMAX> changeIMotMax;
    ChangeValueDisplay<int16_t, IDcMaxAccessor, CommonSettingsMenu, TEXT_SETIDCMAX> changeIDcMax;
    ChangeValueDisplay<int16_t, NMotMaxAccessor, CommonSettingsMenu, TEXT_SETNMOTMAX> changeNMotMax;
    ChangeValueDisplay<int16_t, FieldWeakMaxAccessor, CommonSettingsMenu, TEXT_SETFIELDWEAKMAX> changeFieldWeakMax;
    ChangeValueDisplay<int16_t, PhaseAdvMaxAccessor, CommonSettingsMenu, TEXT_SETPHASEADVMAX> changePhaseAdvMax;
    ChangeValueDisplay<ControlType, DefaultModeCtrlTypAccessor, DefaultModeSettingsMenu, TEXT_SETCONTROLTYPE> changeDefaultModeCtrlTyp;
    ChangeValueDisplay<ControlMode, DefaultModeCtrlModAccessor, DefaultModeSettingsMenu, TEXT_SETCONTROLMODE> changeDefaultModeCtrlMod;
    ChangeValueDisplay<bool, DefaultModeEnableFieldWeakeningSmootheningAccessor, DefaultModeSettingsMenu, TEXT_ENABLEWEAKENINGSMOOTHENING> changeDefaultModeEnableFieldWeakeningSmoothening;
    ChangeValueDisplay<int16_t, DefaultModeWeakeningSmootheningAccessor, DefaultModeSettingsMenu, TEXT_SETWEAKINGSMOOTHENING> changeDefaultModeWeakeningSmoothening;
    ChangeValueDisplay<int16_t, DefaultModeFrontPercentageAccessor, DefaultModeSettingsMenu, TEXT_SETFRONTPERCENTAGE> changeDefaultModeFrontPercentage;
    ChangeValueDisplay<int16_t, DefaultModeBackPercentageAccessor, DefaultModeSettingsMenu, TEXT_SETBACKPERCENTAGE> changeDefaultModeBackPercentage;
    ChangeValueDisplay<int16_t, DefaultModeAddSchwelleAccessor, DefaultModeSettingsMenu, TEXT_SETADDSCHWELLE> changeDefaultModeAddSchwelle;
    ChangeValueDisplay<int16_t, DefaultModeGas1WertAccessor, DefaultModeSettingsMenu, TEXT_SETGAS1WERT> changeDefaultModeGas1Wert;
    ChangeValueDisplay<int16_t, DefaultModeGas2WertAccessor, DefaultModeSettingsMenu, TEXT_SETGAS2WERT> changeDefaultModeGas2Wert;
    ChangeValueDisplay<int16_t, DefaultModeBrems1WertAccessor, DefaultModeSettingsMenu, TEXT_SETBREMS1WERT> changeDefaultModeBrems1Wert;
    ChangeValueDisplay<int16_t, DefaultModeBrems2WertAccessor, DefaultModeSettingsMenu, TEXT_SETBREMS2WERT> changeDefaultModeBrems2Wert;
    ChangeValueDisplay<bool, FrontLeftEnabledAccessor, EnableMenu, TEXT_ENABLEFRONTLEFT> changeFrontLeftEnabled;
    ChangeValueDisplay<bool, FrontRightEnabledAccessor, EnableMenu, TEXT_ENABLEFRONTRIGHT> changeFrontRightEnabled;
    ChangeValueDisplay<bool, BackLeftEnabledAccessor, EnableMenu, TEXT_ENABLEBACKLEFT> changeBackLeftEnabled;
    ChangeValueDisplay<bool, BackRightEnabledAccessor, EnableMenu, TEXT_ENABLEBACKRIGHT> changeBackRightEnabled;
    ChangeValueDisplay<bool, FrontLeftInvertedAccessor, InvertMenu, TEXT_INVERTFRONTLEFT> changeFrontLeftInverted;
    ChangeValueDisplay<bool, FrontRightInvertedAccessor, InvertMenu, TEXT_INVERTFRONTRIGHT> changeFrontRightInverted;
    ChangeValueDisplay<bool, BackLeftInvertedAccessor, InvertMenu, TEXT_INVERTBACKLEFT> changeBackLeftInverted;
    ChangeValueDisplay<bool, BackRightInvertedAccessor, InvertMenu, TEXT_INVERTBACKRIGHT> changeBackRightInverted;
    ChangeValueDisplay<bool, FrontLedAccessor, MainMenu, TEXT_SETFRONTLED> changeFrontLed;
    ChangeValueDisplay<bool, BackLedAccessor, MainMenu, TEXT_SETBACKLED> changeBackLed;
    ChangeValueDisplay<ControlType, ManualModeCtrlTypAccessor, ManualModeSettingsMenu, TEXT_SETCONTROLMODE> changeManualModeCtrlTyp;
    ChangeValueDisplay<ControlMode, ManualModeCtrlModAccessor, ManualModeSettingsMenu, TEXT_SETCONTROLMODE> changeManualModeCtrlMod;
    ChangeValueDisplay<int16_t, GasMinAccessor, PotiSettingsMenu, TEXT_SETGASMIN> changeGasMin;
    ChangeValueDisplay<int16_t, GasMaxAccessor, PotiSettingsMenu, TEXT_SETGASMAX> changeGasMax;
    ChangeValueDisplay<int16_t, BremsMinAccessor, PotiSettingsMenu, TEXT_SETBREMSMIN> changeBremsMin;
    ChangeValueDisplay<int16_t, BremsMaxAccessor, PotiSettingsMenu, TEXT_SETBREMSMAX> changeBremsMax;
} displays;

using DefaultScreen = decltype(displays.statusDisplay);
//using DefaultScreen = decltype(displays.changeNMotMax);

template<typename T> T &getRefByType() = delete;
template<> BluetoothModeSettingsMenu &getRefByType<BluetoothModeSettingsMenu>() { return displays.bluetoothModeSettingsMenu; }
template<> BuzzerMenu &getRefByType<BuzzerMenu>() { return displays.buzzerMenu; }
template<> CommonSettingsMenu &getRefByType<CommonSettingsMenu>() { return displays.commonSettingsMenu; }
template<> DefaultModeSettingsMenu &getRefByType<DefaultModeSettingsMenu>() { return displays.defaultModeSettingsMenu; }
template<> DemosMenu &getRefByType<DemosMenu>() { return displays.demosMenu; }
template<> EnableMenu &getRefByType<EnableMenu>() { return displays.enableMenu; }
template<> InvertMenu &getRefByType<InvertMenu>() { return displays.invertMenu; }
template<> MainMenu &getRefByType<MainMenu>() { return displays.mainMenu; }
template<> ManualModeSettingsMenu &getRefByType<ManualModeSettingsMenu>() { return displays.manualModeSettingsMenu; }
template<> PotiSettingsMenu &getRefByType<PotiSettingsMenu>() { return displays.potiSettingsMenu; }
template<> SelectModeMenu &getRefByType<SelectModeMenu>() { return displays.selectModeMenu; }
template<> SettingsMenu &getRefByType<SettingsMenu>() { return displays.settingsMenu; }
template<> GameOfLifeDisplay<DemosMenu> &getRefByType<GameOfLifeDisplay<DemosMenu>>() { return displays.gameOfLifeDisplay; }
template<> MetersDisplay<DemosMenu> &getRefByType<MetersDisplay<DemosMenu>>() { return displays.metersDisplay; }
template<> PingPongDisplay<DemosMenu> &getRefByType<PingPongDisplay<DemosMenu>>() { return displays.pingPongDisplay; }
template<> SpiroDisplay<DemosMenu> &getRefByType<SpiroDisplay<DemosMenu>>() { return displays.spiroDisplay; }
template<> StarfieldDisplay<DemosMenu> &getRefByType<StarfieldDisplay<DemosMenu>>() { return displays.starFieldDisplay; }
template<> StatusDisplay<MainMenu> &getRefByType<StatusDisplay<MainMenu>>() { return displays.statusDisplay; }
template<> ChangeValueDisplay<uint8_t, FrontFreqAccessor, BuzzerMenu, TEXT_SETFRONTFREQ> &getRefByType<ChangeValueDisplay<uint8_t, FrontFreqAccessor, BuzzerMenu, TEXT_SETFRONTFREQ>>() { return displays.changeFrontFreq; }
template<> ChangeValueDisplay<uint8_t, FrontPatternAccessor, BuzzerMenu, TEXT_SETFRONTPATTERN> &getRefByType<ChangeValueDisplay<uint8_t, FrontPatternAccessor, BuzzerMenu, TEXT_SETFRONTPATTERN>>() { return displays.changeFrontPattern; }
template<> ChangeValueDisplay<uint8_t, BackFreqAccessor, BuzzerMenu, TEXT_SETBACKFREQ> &getRefByType<ChangeValueDisplay<uint8_t, BackFreqAccessor, BuzzerMenu, TEXT_SETBACKFREQ>>() { return displays.changeBackFreq; }
template<> ChangeValueDisplay<uint8_t, BackPatternAccessor, BuzzerMenu, TEXT_SETBACKPATTERN> &getRefByType<ChangeValueDisplay<uint8_t, BackPatternAccessor, BuzzerMenu, TEXT_SETBACKPATTERN>>() { return displays.changeBackPattern; }
template<> ChangeValueDisplay<int16_t, IMotMaxAccessor, CommonSettingsMenu, TEXT_SETIMOTMAX> &getRefByType<ChangeValueDisplay<int16_t, IMotMaxAccessor, CommonSettingsMenu, TEXT_SETIMOTMAX>>() { return displays.changeIMotMax; }
template<> ChangeValueDisplay<int16_t, IDcMaxAccessor, CommonSettingsMenu, TEXT_SETIDCMAX> &getRefByType<ChangeValueDisplay<int16_t, IDcMaxAccessor, CommonSettingsMenu, TEXT_SETIDCMAX>>() { return displays.changeIDcMax; }
template<> ChangeValueDisplay<int16_t, NMotMaxAccessor, CommonSettingsMenu, TEXT_SETNMOTMAX> &getRefByType<ChangeValueDisplay<int16_t, NMotMaxAccessor, CommonSettingsMenu, TEXT_SETNMOTMAX>>() { return displays.changeNMotMax; }
template<> ChangeValueDisplay<int16_t, FieldWeakMaxAccessor, CommonSettingsMenu, TEXT_SETFIELDWEAKMAX> &getRefByType<ChangeValueDisplay<int16_t, FieldWeakMaxAccessor, CommonSettingsMenu, TEXT_SETFIELDWEAKMAX>>() { return displays.changeFieldWeakMax; }
template<> ChangeValueDisplay<int16_t, PhaseAdvMaxAccessor, CommonSettingsMenu, TEXT_SETPHASEADVMAX> &getRefByType<ChangeValueDisplay<int16_t, PhaseAdvMaxAccessor, CommonSettingsMenu, TEXT_SETPHASEADVMAX>>() { return displays.changePhaseAdvMax; }
template<> ChangeValueDisplay<ControlType, DefaultModeCtrlTypAccessor, DefaultModeSettingsMenu, TEXT_SETCONTROLTYPE> &getRefByType<ChangeValueDisplay<ControlType, DefaultModeCtrlTypAccessor, DefaultModeSettingsMenu, TEXT_SETCONTROLTYPE>>() { return displays.changeDefaultModeCtrlTyp; }
template<> ChangeValueDisplay<ControlMode, DefaultModeCtrlModAccessor, DefaultModeSettingsMenu, TEXT_SETCONTROLMODE> &getRefByType<ChangeValueDisplay<ControlMode, DefaultModeCtrlModAccessor, DefaultModeSettingsMenu, TEXT_SETCONTROLMODE>>() { return displays.changeDefaultModeCtrlMod; }
template<> ChangeValueDisplay<bool, DefaultModeEnableFieldWeakeningSmootheningAccessor, DefaultModeSettingsMenu, TEXT_ENABLEWEAKENINGSMOOTHENING> &getRefByType<ChangeValueDisplay<bool, DefaultModeEnableFieldWeakeningSmootheningAccessor, DefaultModeSettingsMenu, TEXT_ENABLEWEAKENINGSMOOTHENING>>() { return displays.changeDefaultModeEnableFieldWeakeningSmoothening; }
template<> ChangeValueDisplay<int16_t, DefaultModeWeakeningSmootheningAccessor, DefaultModeSettingsMenu, TEXT_SETWEAKINGSMOOTHENING> &getRefByType<ChangeValueDisplay<int16_t, DefaultModeWeakeningSmootheningAccessor, DefaultModeSettingsMenu, TEXT_SETWEAKINGSMOOTHENING>>() { return displays.changeDefaultModeWeakeningSmoothening; }
template<> ChangeValueDisplay<int16_t, DefaultModeFrontPercentageAccessor, DefaultModeSettingsMenu, TEXT_SETFRONTPERCENTAGE> &getRefByType<ChangeValueDisplay<int16_t, DefaultModeFrontPercentageAccessor, DefaultModeSettingsMenu, TEXT_SETFRONTPERCENTAGE>>() { return displays.changeDefaultModeFrontPercentage; }
template<> ChangeValueDisplay<int16_t, DefaultModeBackPercentageAccessor, DefaultModeSettingsMenu, TEXT_SETBACKPERCENTAGE> &getRefByType<ChangeValueDisplay<int16_t, DefaultModeBackPercentageAccessor, DefaultModeSettingsMenu, TEXT_SETBACKPERCENTAGE>>() { return displays.changeDefaultModeBackPercentage; }
template<> ChangeValueDisplay<int16_t, DefaultModeAddSchwelleAccessor, DefaultModeSettingsMenu, TEXT_SETADDSCHWELLE> &getRefByType<ChangeValueDisplay<int16_t, DefaultModeAddSchwelleAccessor, DefaultModeSettingsMenu, TEXT_SETADDSCHWELLE>>() { return displays.changeDefaultModeAddSchwelle; }
template<> ChangeValueDisplay<int16_t, DefaultModeGas1WertAccessor, DefaultModeSettingsMenu, TEXT_SETGAS1WERT> &getRefByType<ChangeValueDisplay<int16_t, DefaultModeGas1WertAccessor, DefaultModeSettingsMenu, TEXT_SETGAS1WERT>>() { return displays.changeDefaultModeGas1Wert; }
template<> ChangeValueDisplay<int16_t, DefaultModeGas2WertAccessor, DefaultModeSettingsMenu, TEXT_SETGAS2WERT> &getRefByType<ChangeValueDisplay<int16_t, DefaultModeGas2WertAccessor, DefaultModeSettingsMenu, TEXT_SETGAS2WERT>>() { return displays.changeDefaultModeGas2Wert; }
template<> ChangeValueDisplay<int16_t, DefaultModeBrems1WertAccessor, DefaultModeSettingsMenu, TEXT_SETBREMS1WERT> &getRefByType<ChangeValueDisplay<int16_t, DefaultModeBrems1WertAccessor, DefaultModeSettingsMenu, TEXT_SETBREMS1WERT>>() { return displays.changeDefaultModeBrems1Wert; }
template<> ChangeValueDisplay<int16_t, DefaultModeBrems2WertAccessor, DefaultModeSettingsMenu, TEXT_SETBREMS2WERT> &getRefByType<ChangeValueDisplay<int16_t, DefaultModeBrems2WertAccessor, DefaultModeSettingsMenu, TEXT_SETBREMS2WERT>>() { return displays.changeDefaultModeBrems2Wert; }
template<> ChangeValueDisplay<bool, FrontLeftEnabledAccessor, EnableMenu, TEXT_ENABLEFRONTLEFT> &getRefByType<ChangeValueDisplay<bool, FrontLeftEnabledAccessor, EnableMenu, TEXT_ENABLEFRONTLEFT>>() { return displays.changeFrontLeftEnabled; }
template<> ChangeValueDisplay<bool, FrontRightEnabledAccessor, EnableMenu, TEXT_ENABLEFRONTRIGHT> &getRefByType<ChangeValueDisplay<bool, FrontRightEnabledAccessor, EnableMenu, TEXT_ENABLEFRONTRIGHT>>() { return displays.changeFrontRightEnabled; }
template<> ChangeValueDisplay<bool, BackLeftEnabledAccessor, EnableMenu, TEXT_ENABLEBACKLEFT> &getRefByType<ChangeValueDisplay<bool, BackLeftEnabledAccessor, EnableMenu, TEXT_ENABLEBACKLEFT>>() { return displays.changeBackLeftEnabled; }
template<> ChangeValueDisplay<bool, BackRightEnabledAccessor, EnableMenu, TEXT_ENABLEBACKRIGHT> &getRefByType<ChangeValueDisplay<bool, BackRightEnabledAccessor, EnableMenu, TEXT_ENABLEBACKRIGHT>>() { return displays.changeBackRightEnabled; }
template<> ChangeValueDisplay<bool, FrontLeftInvertedAccessor, InvertMenu, TEXT_INVERTFRONTLEFT> &getRefByType<ChangeValueDisplay<bool, FrontLeftInvertedAccessor, InvertMenu, TEXT_INVERTFRONTLEFT>>() { return displays.changeFrontLeftInverted; }
template<> ChangeValueDisplay<bool, FrontRightInvertedAccessor, InvertMenu, TEXT_INVERTFRONTRIGHT> &getRefByType<ChangeValueDisplay<bool, FrontRightInvertedAccessor, InvertMenu, TEXT_INVERTFRONTRIGHT>>() { return displays.changeFrontRightInverted; }
template<> ChangeValueDisplay<bool, BackLeftInvertedAccessor, InvertMenu, TEXT_INVERTBACKLEFT> &getRefByType<ChangeValueDisplay<bool, BackLeftInvertedAccessor, InvertMenu, TEXT_INVERTBACKLEFT>>() { return displays.changeBackLeftInverted; }
template<> ChangeValueDisplay<bool, BackRightInvertedAccessor, InvertMenu, TEXT_INVERTBACKRIGHT> &getRefByType<ChangeValueDisplay<bool, BackRightInvertedAccessor, InvertMenu, TEXT_INVERTBACKRIGHT>>() { return displays.changeBackRightInverted; }
template<> ChangeValueDisplay<bool, FrontLedAccessor, MainMenu, TEXT_SETFRONTLED> &getRefByType<ChangeValueDisplay<bool, FrontLedAccessor, MainMenu, TEXT_SETFRONTLED>>() { return displays.changeFrontLed; }
template<> ChangeValueDisplay<bool, BackLedAccessor, MainMenu, TEXT_SETBACKLED> &getRefByType<ChangeValueDisplay<bool, BackLedAccessor, MainMenu, TEXT_SETBACKLED>>() { return displays.changeBackLed; }
template<> ChangeValueDisplay<ControlType, ManualModeCtrlTypAccessor, ManualModeSettingsMenu, TEXT_SETCONTROLMODE> &getRefByType<ChangeValueDisplay<ControlType, ManualModeCtrlTypAccessor, ManualModeSettingsMenu, TEXT_SETCONTROLMODE>>() { return displays.changeManualModeCtrlTyp; }
template<> ChangeValueDisplay<ControlMode, ManualModeCtrlModAccessor, ManualModeSettingsMenu, TEXT_SETCONTROLMODE> &getRefByType<ChangeValueDisplay<ControlMode, ManualModeCtrlModAccessor, ManualModeSettingsMenu, TEXT_SETCONTROLMODE>>() { return displays.changeManualModeCtrlMod; }
template<> ChangeValueDisplay<int16_t, GasMinAccessor, PotiSettingsMenu, TEXT_SETGASMIN> &getRefByType<ChangeValueDisplay<int16_t, GasMinAccessor, PotiSettingsMenu, TEXT_SETGASMIN>>() { return displays.changeGasMin; }
template<> ChangeValueDisplay<int16_t, GasMaxAccessor, PotiSettingsMenu, TEXT_SETGASMAX> &getRefByType<ChangeValueDisplay<int16_t, GasMaxAccessor, PotiSettingsMenu, TEXT_SETGASMAX>>() { return displays.changeGasMax; }
template<> ChangeValueDisplay<int16_t, BremsMinAccessor, PotiSettingsMenu, TEXT_SETBREMSMIN> &getRefByType<ChangeValueDisplay<int16_t, BremsMinAccessor, PotiSettingsMenu, TEXT_SETBREMSMIN>>() { return displays.changeBremsMin; }
template<> ChangeValueDisplay<int16_t, BremsMaxAccessor, PotiSettingsMenu, TEXT_SETBREMSMAX> &getRefByType<ChangeValueDisplay<int16_t, BremsMaxAccessor, PotiSettingsMenu, TEXT_SETBREMSMAX>>() { return displays.changeBremsMax; }

Display *currentDisplay{};

template<typename T> void switchScreen()
{
    if (currentDisplay)
    {
        currentDisplay->~Display();
        currentDisplay = nullptr;
    }

    T &ref = getRefByType<T>();
    new (&ref) T;
    currentDisplay = &ref;
    ref.start();
    ref.update();
}

class InputDispatcher {
public:
    static void rotate(int offset) { currentDisplay->rotate(offset); }
    static void button(bool pressed) { currentDisplay->button(pressed); }
};

Rotary<InputDispatcher, rotaryClkPin, rotaryDtPin, rotarySwPin> rotary;

void updateRotate() { rotary.updateRotate(); }
void updateSwitch() { rotary.updateSwitch(); }

void initRotary()
{
    attachInterrupt(decltype(rotary)::ClkPin, updateRotate, CHANGE);
    attachInterrupt(decltype(rotary)::SwPin, updateSwitch, CHANGE);
}

void initScreen()
{
    switchScreen<DefaultScreen>();
}

void updateScreen()
{
    currentDisplay->update();
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
