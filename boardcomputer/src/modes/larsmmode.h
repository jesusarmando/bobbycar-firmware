#pragma once

#include "modeinterface.h"
#include "globals.h"
#include "utils.h"

#include "../../common.h"

namespace {
class LarsmMode : public ModeInterface
{
public:
    void start() override;
    void update() override;

    const char *displayName() const override { return "Larsm"; }

    enum class Mode { Mode1, Mode2, Mode3, Mode4 };
    Mode mode{Mode::Mode4};

    uint8_t iterations{5};

private:
    float adc1_filtered;
    float adc2_filtered;
    int speed;
    float weak;
};

namespace modes {
LarsmMode larsmMode;
}

void LarsmMode::start()
{
    adc1_filtered = 0.f;
    adc2_filtered = 0.f;
    speed = 0;
    weak = 0.f;
}

void LarsmMode::update()
{
    for (uint8_t i = 0; i < iterations; i++) // run multiple times to emulate higher refreshrate
    {
        // ####### larsm's bobby car code #######

        // LOW-PASS FILTER (fliessender Mittelwert)
        adc1_filtered = adc1_filtered * 0.9 + gas * 0.1;  // ADC1, TX, rechts, vorwaerts, blau
        adc2_filtered = adc2_filtered * 0.9 + brems * 0.1;  // ADC2, RX, links, rueckwearts, gruen

        // magic numbers die ich nicht mehr nachvollziehen kann, faehrt sich aber gut ;-)
        #define LOSLASS_BREMS_ACC 0.996f  // naeher an 1 = gemaechlicher
        #define DRUECK_ACC2 (1.0f - LOSLASS_BREMS_ACC + 0.001f)  // naeher an 0 = gemaechlicher
        #define DRUECK_ACC1 (1.0f - LOSLASS_BREMS_ACC + 0.001f)  // naeher an 0 = gemaechlicher
        //die + 0.001f gleichen float ungenauigkeiten aus.

        #define ADC1_MIN 0
        #define ADC2_MIN 0
        #define ADC1_MAX 1000
        #define ADC2_MAX 1000

        #define ADC2_DELTA (ADC2_MAX - ADC2_MIN)
        #define ADC1_DELTA (ADC1_MAX - ADC1_MIN)

        #define CLAMP(x, low, high) (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

        if (mode == Mode::Mode1) {  // Mode 1, links: 3 kmh
          speed = (float)speed * LOSLASS_BREMS_ACC  // bremsen wenn kein poti gedrueckt
                  - (CLAMP(brems - ADC2_MIN, 0, ADC2_DELTA) / (ADC2_DELTA / 280.0f)) * DRUECK_ACC2   // links gedrueckt = zusatzbremsen oder rueckwaertsfahren
                  + (CLAMP(gas - ADC1_MIN, 0, ADC1_DELTA) / (ADC1_DELTA / 350.0f)) * DRUECK_ACC1;  // vorwaerts gedrueckt = beschleunigen 12s: 350=3kmh
          weak = 0;

        } else if (mode == Mode::Mode2) { // Mode 2, default: 6 kmh
          speed = (float)speed * LOSLASS_BREMS_ACC
                  - (CLAMP(brems - ADC2_MIN, 0, ADC2_DELTA) / (ADC2_DELTA / 310.0f)) * DRUECK_ACC2
                  + (CLAMP(gas - ADC1_MIN, 0, ADC1_DELTA) / (ADC1_DELTA / 420.0f)) * DRUECK_ACC1;  // 12s: 400=5-6kmh 450=7kmh
          weak = 0;

        } else if (mode == Mode::Mode3) { // Mode 3, rechts: 12 kmh
          speed = (float)speed * LOSLASS_BREMS_ACC
                  - (CLAMP(brems - ADC2_MIN, 0, ADC2_DELTA) / (ADC2_DELTA / 340.0f)) * DRUECK_ACC2
                  + (CLAMP(gas - ADC1_MIN, 0, ADC1_DELTA) / (ADC1_DELTA / 600.0f)) * DRUECK_ACC1;  // 12s: 600=12kmh
          weak = 0;

        } else if (mode == Mode::Mode4) { // Mode 4, l + r: full kmh
          // Feldschwaechung wird nur aktiviert wenn man schon sehr schnell ist. So gehts: Rechts voll druecken und warten bis man schnell ist, dann zusaetzlich links schnell voll druecken.
          if (adc2_filtered > (ADC2_MAX - 450) && speed > 800) { // field weakening at high speeds
            speed = (float)speed * LOSLASS_BREMS_ACC
                  + (CLAMP(gas - ADC1_MIN, 0, ADC1_DELTA) / (ADC1_DELTA / 1000.0f)) * DRUECK_ACC1;
            weak = weak * 0.95 + 400.0 * 0.05;  // sanftes hinzuschalten des turbos, 12s: 400=29kmh
          } else { //normale fahrt ohne feldschwaechung
            speed = (float)speed * LOSLASS_BREMS_ACC
                  - (CLAMP(brems - ADC2_MIN, 0, ADC2_DELTA) / (ADC2_DELTA / 340.0f)) * DRUECK_ACC2
                  + (CLAMP(gas - ADC1_MIN, 0, ADC1_DELTA) / (ADC1_DELTA / 1000.0f)) * DRUECK_ACC1;  // 12s: 1000=22kmh
            weak = weak * 0.95;  // sanftes abschalten des turbos
          }
          // weak should never exceed 400 or 450 MAX!!
        }

        speed = CLAMP(speed, -1000, 1000);  // clamp output
    }

    for (MotorState &motor : motors())
    {
        motor.ctrlTyp = ControlType::Commutation;
        motor.ctrlMod = ControlMode::Voltage;
        motor.pwm = speed + weak;
    }

    fixCommonParams();

    sendCommands();
}
}
