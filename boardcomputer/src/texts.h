#pragma once

namespace {
//AboutMenu
constexpr char TEXT_ABOUT[] = "About";
constexpr char TEXT_BACK[] = "Back";

//AccessPointWifiSettingsMenu
constexpr char TEXT_ACCESSPOINTWIFISETTINGS[] = "Access Point WiFi settings";
constexpr char TEXT_WIFISOFTAPENABLEIPV6[] = "softAPenableIpV6()";
//constexpr char TEXT_BACK[] = "Back";

//BluetoothSettingsMenu
constexpr char TEXT_BLUETOOTHSETTINGS[] = "Bluetooth settings";
constexpr char TEXT_BLUETOOTHBEGIN[] = "begin()";
constexpr char TEXT_BLUETOOTHBEGINMASTER[] = "begin() Master";
constexpr char TEXT_BLUETOOTHFLUSH[] = "flush()";
constexpr char TEXT_BLUETOOTHEND[] = "end()";
constexpr char TEXT_BLUETOOTHDISCONNECT[] = "disconnect()";
//constexpr char TEXT_BACK[] = "Back";


//BluetoothModeSettingsMenu
constexpr char TEXT_BLUETOOTHMODESETTINGS[] = "Bluetooth mode settings";
//constexpr char TEXT_BACK[] = "Back";

//DebugMenu
constexpr char TEXT_FRONTCOMMAND[] = "Front command";
constexpr char TEXT_BACKCOMMAND[] = "Back command";
constexpr char TEXT_FRONTLEFTCOMMAND[] = "Front left command";
constexpr char TEXT_FRONTRIGHTCOMMAND[] = "Front right command";
constexpr char TEXT_BACKLEFTCOMMAND[] = "Back left command";
constexpr char TEXT_BACKRIGHTCOMMAND[] = "Back right command";
constexpr char TEXT_FRONTFEEDBACK[] = "Front feedback";
constexpr char TEXT_BACKFEEDBACK[] = "Back feedback";
constexpr char TEXT_FRONTLEFTFEEDBACK[] = "Front left feedback";
constexpr char TEXT_FRONTRIGHTFEEDBACK[] = "Front right feedback";
constexpr char TEXT_BACKLEFTFEEDBACK[] = "Back left feedback";
constexpr char TEXT_BACKRIGHTFEEDBACK[] = "Back right feedback";
//constexpr char TEXT_BACK[] = "Back";

//MainMenu
constexpr char TEXT_MAINMENU[] = "Main menu";
constexpr char TEXT_STATUS[] = "Status";
constexpr char TEXT_SELECTMODE[] = "Select mode";
constexpr char TEXT_PRESETS[] = "Presets";
constexpr char TEXT_SETTINGS[] = "Settings";
constexpr char TEXT_LOCKVEHICLE[] = "Lock vehicle";
constexpr char TEXT_DEMOS[] = "Demos";
constexpr char TEXT_POWEROFF[] = "Poweroff";
constexpr char TEXT_REBOOT[] = "Reboot";
constexpr char TEXT_DEBUG[] = "Debug";

//SettingsMenu
//constexpr char TEXT_SETTINGS[] = "Settings";
constexpr char TEXT_COMMONSETTINGS[] = "Common settings";
constexpr char TEXT_WIFISETTINGS[] = "WiFi settings";
//constexpr char TEXT_BLUETOOTHSETTINGS[] = "Bluetooth settings";
constexpr char TEXT_MODESSETTINGS[] = "Modes settings";
constexpr char TEXT_POTISETTINGS[] = "Poti settings";
constexpr char TEXT_SWAPFRONTBACK[] = "Swap front/back";
constexpr char TEXT_BUZZER[] = "Buzzer";
constexpr char TEXT_SETFRONTLED[] = "Set front LED";
constexpr char TEXT_SETBACKLED[] = "Set back LED";
//constexpr char TEXT_ABOUT[] = "About";
//constexpr char TEXT_BACK[] = "Back";

//StationWifiSettingsMenu
constexpr char TEXT_STATIONWIFISETTINGS[] = "Station WiFi settings";
constexpr char TEXT_WIFIRECONNECT[] = "reconnect()";
constexpr char TEXT_WIFIDISCONNECT[] = "disconnect()";
constexpr char TEXT_WIFICHANGEAUTOCONNECT[] = "Change auto connect";
constexpr char TEXT_WIFICHANGEAUTORECONNECT[] = "Change auto reconnect";
constexpr char TEXT_WIFIENABLEIPV6[] = "enableIpV6()";
//constexpr char TEXT_BACK[] = "Back";

//DemosMenu
//constexpr char TEXT_DEMOS[] = "Demos";
constexpr char TEXT_STARFIELD[] = "Starfield";
constexpr char TEXT_PINGPONG[] = "PingPong";
constexpr char TEXT_SPIRO[] = "Spiro";
constexpr char TEXT_GAMEOFLIFE[] = "GameOfLife";
constexpr char TEXT_METERS[] = "Meters";
constexpr char TEXT_MATRIX[] = "Matrix";
//constexpr char TEXT_BACK[] = "Back";

//BuzzerMenu
//constexpr char TEXT_BUZZER[] = "Buzzer";
constexpr char TEXT_SETFRONTFREQ[] = "Set front freq";
constexpr char TEXT_SETFRONTPATTERN[] = "Set front pattern";
constexpr char TEXT_SETBACKFREQ[] = "Set back freq";
constexpr char TEXT_SETBACKPATTERN[] = "Set back pattern";
//constexpr char TEXT_BACK[] = "Back";

//CommonSettingsMenu
//constexpr char TEXT_COMMONSETTINGS[] = "Common settings";
constexpr char TEXT_SETIMOTMAX[] = "Set iMotMax";
constexpr char TEXT_SETIDCMAX[] = "Set iDcMax";
constexpr char TEXT_SETNMOTMAXKMH[] = "Set nMotMax (kmh)";
constexpr char TEXT_SETNMOTMAX[] = "Set nMotMax";
constexpr char TEXT_SETFIELDWEAKMAX[] = "Set fieldWeakMax";
constexpr char TEXT_SETPHASEADVMAX[] = "Set phaseAdvMax";
constexpr char TEXT_SETENABLED[] = "Set enabled";
constexpr char TEXT_SETINVERTED[] = "Set inverted";
//constexpr char TEXT_BACK[] = "Back";

//DebugMenu
//constexpr char TEXT_DEBUG[] = "Debug";
constexpr char TEXT_DYNAMICMENU[] = "Dynamic menu";
//constexpr char TEXT_BACK[] = "Back";

//DefaultModeSettingsMenu
//constexpr char TEXT_DEFAULTMODESETTINGS[] = "Default mode settings";
constexpr char TEXT_SETCONTROLTYPE[] = "Set control type";
constexpr char TEXT_SETCONTROLMODE[] = "Set control mode";
constexpr char TEXT_ENABLEWEAKENINGSMOOTHENING[] = "Enable weakening smoothening";
constexpr char TEXT_SETWEAKINGSMOOTHENING[] = "Set weaking smoothening";
constexpr char TEXT_SETFRONTPERCENTAGE[] = "Set front percentage";
constexpr char TEXT_SETBACKPERCENTAGE[] = "Set back percentage";
constexpr char TEXT_SETADDSCHWELLE[] = "Set add Schwelle";
constexpr char TEXT_SETGAS1WERT[] = "Set Gas 1 Wert";
constexpr char TEXT_SETGAS2WERT[] = "Set Gas 2 Wert";
constexpr char TEXT_SETBREMS1WERT[] = "Set Brems 1 Wert";
constexpr char TEXT_SETBREMS2WERT[] = "Set Brems 2 Wert";
//constexpr char TEXT_BACK[] = "Back";

//DynamicDebugMenu
//constexpr char TEXT_DYNAMICMENU[] = "Dynamic menu";
//constexpr char TEXT_BACK[] = "Back";

//EnableMenu
//constexpr char TEXT_SETENABLED[] = "Set enabled";
constexpr char TEXT_ENABLEFRONTLEFT[] = "Enable front left";
constexpr char TEXT_ENABLEFRONTRIGHT[] = "Enable front right";
constexpr char TEXT_ENABLEBACKLEFT[] = "Enable back left";
constexpr char TEXT_ENABLEBACKRIGHT[] = "Enable back right";
//constexpr char TEXT_BACK[] = "Back";

//GenericWifiSettingsMenu
constexpr char TEXT_GENERICWIFISETTINGS[] = "Generic WiFi settings";
constexpr char TEXT_WIFICHANGEMODE[] = "Change mode";
constexpr char TEXT_WIFICHANGESLEEP[] = "Change sleep";
constexpr char TEXT_WIFICHANGETXPOWER[] = "Change tx power";
constexpr char TEXT_WIFISCAN[] = "WiFi scan";
//constexpr char TEXT_BACK[] = "Back";

//InvertMenu
//constexpr char TEXT_SETINVERTED[] = "Set inverted";
constexpr char TEXT_INVERTFRONTLEFT[] = "Invert front left";
constexpr char TEXT_INVERTFRONTRIGHT[] = "Invert front right";
constexpr char TEXT_INVERTBACKLEFT[] = "Invert back left";
constexpr char TEXT_INVERTBACKRIGHT[] = "Invert back right";
//constexpr char TEXT_BACK[] = "Back";

//LarsmModeSettingsMenu
constexpr char TEXT_LARSMMODESETTINGS[] = "Larsm mode settings";
constexpr char TEXT_LARSMMODECHANGEMODE[] = "Change mode";
constexpr char TEXT_LARSMMODECHANGEITERATIONS[] = "Change iterations";
//constexpr char TEXT_BACK[] = "Back";

//ModesSettingsMenu
//constexpr char TEXT_MODESSETTINGS[] = "Modes settings";
constexpr char TEXT_DEFAULTMODESETTIGNS[] = "Default mode settings";
constexpr char TEXT_TEMPOMATMODESETTINGS[] = "Tempomat mode settings";
//constexpr char TEXT_LARSMMODESETTINGS[] = "Larsm mode settings";
//constexpr char TEXT_BLUETOOTHMODESETTINGS[] = "Bluetooth mode settings";
constexpr char TEXT_WEBSOCKETMODESETTINGS[] = "Websocket mode settings";
//constexpr char TEXT_BACK[] = "Back";

//TempomatModeSettingsMenu
//constexpr char TEXT_TEMPOMATMODESETTINGS[] = "Tempomat mode settings";
//constexpr char TEXT_SETCONTROLTYPE[] = "Set control type";
//constexpr char TEXT_SETCONTROLMODE[] = "Set control mode";
//constexpr char TEXT_BACK[] = "Back";

//WiFiSettingsMenu
//constexpr char TEXT_WIFISETTINGS[] = "WiFi settings";
//constexpr char TEXT_GENERICWIFISETTINGS[] = "Generic WiFi settings";
//constexpr char TEXT_BACK[] = "Back";

//PotiSettingsMenu
//constexpr char TEXT_POTISETTINGS[] = "Poti settings";
constexpr char TEXT_SETGASMIN[] = "Set gasMin";
constexpr char TEXT_SETGASMAX[] = "Set gasMax";
constexpr char TEXT_SETBREMSMIN[] = "Set bremsMin";
constexpr char TEXT_SETBREMSMAX[] = "Set bremsMax";
constexpr char TEXT_CALIBRATE[] = "Calibrate";
//constexpr char TEXT_BACK[] = "Back";

//PresetsMenu
//constexpr char TEXT_PRESETS[] = "Presets";
constexpr char TEXT_STREET[] = "Street";
constexpr char TEXT_SIDEWALK[] = "Sidewalk";
constexpr char TEXT_POLICE[] = "Police";
constexpr char TEXT_RACE[] = "Race";

//SelectModeMenu
//constexpr char TEXT_SELECTMODE[] = "Select mode";
constexpr char TEXT_DEFAULT[] = "Default";
constexpr char TEXT_TEMPOMAT[] = "Tempomat";
constexpr char TEXT_LARSM[] = "Larsm";
constexpr char TEXT_BLUETOOTH[] = "Bluetooth";
constexpr char TEXT_WEBSOCKET[] = "Websocket";
//constexpr char TEXT_BACK[] = "Back";

//ChangeValueDisplay<bool>
constexpr char TEXT_TRUE[] = "true";
constexpr char TEXT_FALSE[] = "false";
//constexpr char TEXT_BACK[] = "Back";

//ChangeValueDisplay<ControlMode>
constexpr char TEXT_OPENMODE[] = "Open mode";
constexpr char TEXT_VOLTAGE[] = "Voltage";
constexpr char TEXT_SPEED[] = "Speed";
constexpr char TEXT_TORQUE[] = "Torque";
//constexpr char TEXT_BACK[] = "Back";

//ChangeValueDisplay<ControlType>
constexpr char TEXT_COMMUTATION[] = "Commutation";
constexpr char TEXT_SINUSOIDAL[] = "Sinusoidal";
constexpr char TEXT_FIELDORIENTEDCONTROL[] = "Field oriented control";
//constexpr char TEXT_BACK[] = "Back";

//ChangeValueDisplay<LarsmMode::Mode>
constexpr char TEXT_LARSMMODE1[] = "Mode1";
constexpr char TEXT_LARSMMODE2[] = "Mode2";
constexpr char TEXT_LARSMMODE3[] = "Mode3";
constexpr char TEXT_LARSMMODE4[] = "Mode4";
//constexpr char TEXT_BACK[] = "Back";

//ChangeValueDisplay<wifi_mode_t>
constexpr char TEXT_WIFI_MODE_NULL[] = "WIFI_MODE_NULL";
constexpr char TEXT_WIFI_MODE_STA[] = "WIFI_MODE_STA";
constexpr char TEXT_WIFI_MODE_AP[] = "WIFI_MODE_AP";
constexpr char TEXT_WIFI_MODE_APSTA[] = "WIFI_MODE_APSTA";
//constexpr char TEXT_BACK[] = "Back";

//ChangeValueDisplay<wifi_power_t>
constexpr char TEXT_WIFI_POWER_19_5dBm[] = "19.5dBm";
constexpr char TEXT_WIFI_POWER_19dBm[] = "19dBm";
constexpr char TEXT_WIFI_POWER_18_5dBm[] = "18.5dBm";
constexpr char TEXT_WIFI_POWER_17dBm[] = "17dBm";
constexpr char TEXT_WIFI_POWER_15dBm[] = "15dBm";
constexpr char TEXT_WIFI_POWER_13dBm[] = "13dBm";
constexpr char TEXT_WIFI_POWER_11dBm[] = "11dBm";
constexpr char TEXT_WIFI_POWER_8_5dBm[] = "8.5dBm";
constexpr char TEXT_WIFI_POWER_7dBm[] = "7dBm";
constexpr char TEXT_WIFI_POWER_5dBm[] = "5dBm";
constexpr char TEXT_WIFI_POWER_2dBm[] = "2dBm";
constexpr char TEXT_WIFI_POWER_MINUS_1dBm[] = "-1dBm";
//constexpr char TEXT_BACK[] = "Back";
}
