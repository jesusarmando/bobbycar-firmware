#pragma once

namespace {
constexpr auto defaultGasMin = 800, defaultGasMax = 3700,
               defaultBremsMin = 1300, defaultBremsMax = 4000;
constexpr auto defaultInvertFrontLeft = false, defaultInvertFrontRight = true, defaultInvertBackLeft = false, defaultInvertBackRight = true;
constexpr auto defaultEnableFrontLeft = true, defaultEnableFrontRight = true, defaultEnableBackLeft = true, defaultEnableBackRight = true;
constexpr auto defaultIMotMax = 25, defaultIDcMax = 27, defaultFieldWeakMax = 5;
constexpr auto defaultDefaultModeGas1Wert = 1250, defaultDefaultModeGas2Wert = 1250, defaultDefaultModeBrems1Wert = 250, defaultDefaultModeBrems2Wert = 750;
constexpr auto gasPin = 35, bremsPin = 33;
constexpr int rxPin1 = PINS_RX1, txPin1 = PINS_TX1,
              rxPin2 = PINS_RX2, txPin2 = PINS_TX2;
constexpr auto rotaryClkPin = 4, rotaryDtPin = 16, rotarySwPin = 17;
}
