#pragma once

namespace {
//BluetoothSettingsMenu
constexpr char TEXT_BLUETOOTHSETTINGS[] = "Bluetooth settings";
constexpr char TEXT_BLUETOOTHBEGIN[] = "begin()";
constexpr char TEXT_BLUETOOTHBEGINMASTER[] = "begin() Master";
constexpr char TEXT_BLUETOOTHFLUSH[] = "flush()";
constexpr char TEXT_BLUETOOTHEND[] = "end()";
constexpr char TEXT_BLUETOOTHDISCONNECT[] = "disconnect()";
constexpr char TEXT_BACK[] = "Back";


//BluetoothModeSettingsMenu
constexpr char TEXT_BLUETOOTHMODESETTINGS[] = "Bluetooth mode settings";
//constexpr char TEXT_BACK[] = "Back";

//MainMenu
constexpr char TEXT_MAINMENU[] = "Main menu";
constexpr char TEXT_STATUS[] = "Status";
constexpr char TEXT_SELECTMODE[] = "Select mode";
constexpr char TEXT_PRESETS[] = "Presets";
constexpr char TEXT_SETTINGS[] = "Settings";
constexpr char TEXT_LOCKVEHICLE[] = "Lock vehicle";
constexpr char TEXT_DEMOS[] = "Demos";
constexpr char TEXT_DEBUG[] = "Debug";
constexpr char TEXT_POWEROFF[] = "Poweroff";

//SettingsMenu
//constexpr char TEXT_SETTINGS[] = "Settings";
constexpr char TEXT_COMMONSETTINGS[] = "Common settings";
constexpr char TEXT_WIFISETTINGS[] = "WiFi settings";
//constexpr char TEXT_BLUETOOTHSETTINGS[] = "Bluetooth settings";
constexpr char TEXT_DEFAULTMODESETTIGNS[] = "Default mode settings";
constexpr char TEXT_TEMPOMATMODESETTINGS[] = "Tempomat mode settings";
//constexpr char TEXT_BLUETOOTHMODESETTINGS[] = "Bluetooth mode settings";
constexpr char TEXT_POTISETTINGS[] = "Poti settings";
constexpr char TEXT_REBOOT[] = "Reboot";
constexpr char TEXT_VERSION[] = "Version";
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
constexpr char TEXT_SETNMOTMAX[] = "Set nMotMax";
constexpr char TEXT_SETFIELDWEAKMAX[] = "Set fieldWeakMax";
constexpr char TEXT_SETPHASEADVMAX[] = "Set phaseAdvMax";
constexpr char TEXT_SETENABLED[] = "Set enabled";
constexpr char TEXT_SETINVERTED[] = "Set inverted";
//constexpr char TEXT_BACK[] = "Back";

//DebugMenu
//constexpr char TEXT_DEBUG[] = "Debug";
constexpr char TEXT_BUZZER[] = "Buzzer";
constexpr char TEXT_SETFRONTLED[] = "Set front LED";
constexpr char TEXT_SETBACKLED[] = "Set back LED";
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

//InvertMenu
//constexpr char TEXT_SETINVERTED[] = "Set inverted";
constexpr char TEXT_INVERTFRONTLEFT[] = "Invert front left";
constexpr char TEXT_INVERTFRONTRIGHT[] = "Invert front right";
constexpr char TEXT_INVERTBACKLEFT[] = "Invert back left";
constexpr char TEXT_INVERTBACKRIGHT[] = "Invert back right";
//constexpr char TEXT_BACK[] = "Back";

//TempomatModeSettingsMenu
//constexpr char TEXT_TEMPOMATMODESETTINGS[] = "Tempomat mode settings";
//constexpr char TEXT_SETCONTROLTYPE[] = "Set control type";
//constexpr char TEXT_SETCONTROLMODE[] = "Set control mode";
//constexpr char TEXT_BACK[] = "Back";

//WiFiSettingsMenu
//constexpr char TEXT_WIFISETTINGS[] = "WiFi settings";
constexpr char TEXT_WIFISCAN[] = "WiFi scan";
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
constexpr char TEXT_BLUETOOTH[] = "Bluetooth";
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
}
