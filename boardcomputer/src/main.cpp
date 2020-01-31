#include <Arduino.h>
#include <HardwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <array>

#include "../../common.h"

namespace {
constexpr auto gasMin = 800., gasMax = 3700.,
               bremsMin = 1300., bremsMax = 4000.;
constexpr auto gasPin = 33, bremsPin = 35;

bool power_toggle{false};
bool led_toggle{false};

Command command;

int lastSendCommand = millis();
int lastAlive = millis();

Adafruit_SSD1306 display(128, 64, &Wire, 4);

enum { ScreenA, ScreenB, ScreenC } screen { ScreenA };
unsigned long lastScreenSwitch = 0;

struct Controller {
    Controller(HardwareSerial &serial) : serial{serial} {}

    HardwareSerial &serial;
    Feedback feedback, newFeedback;

    uint8_t idx = 0;                        // Index for new data pointer
    uint16_t bufStartFrame;                 // Buffer Start Frame
    byte *p;                                // Pointer declaration for the new received data
    byte incomingByte;
    byte incomingBytePrev;
};
std::array<Controller, 2> controllers{Controller{Serial1}, Controller{Serial2}};
Controller &first{controllers[0]},
           &second{controllers[1]};

void sendCommand()
{
    command.start = Command::VALID_HEADER;
    command.checksum = calculateChecksum(command);
    Serial1.write((uint8_t *) &command, sizeof(command));
    Serial2.write((uint8_t *) &command, sizeof(command));
}

void receiveFeedback()
{
    for (Controller &controller : controllers)
    {
        // Check for new data availability in the Serial buffer
        while (controller.serial.available())
        {
            controller.incomingByte    = controller.serial.read();                                // Read the incoming byte
            controller.bufStartFrame = ((uint16_t)(controller.incomingBytePrev) << 8) +  controller.incomingByte; // Construct the start frame

            //Serial.printf("received: %x\r\n", controller.incomingByte);

            // Copy received data
            if (controller.bufStartFrame == Feedback::VALID_HEADER) {                     // Initialize if new data is detected
                controller.p   = (byte *)&controller.newFeedback;
                *controller.p++  = controller.incomingBytePrev;
                *controller.p++  = controller.incomingByte;
                controller.idx  = 2;
            } else if (controller.idx >= 2 && controller.idx < sizeof(controller.feedback)) { // Save the new received data
                *controller.p++  = controller.incomingByte;
                controller.idx++;
            }

            // Check if we reached the end of the package
            if (controller.idx == sizeof(controller.feedback)) {
                uint16_t checksum = calculateChecksum(controller.newFeedback);

                // Check validity of the new data
                if (controller.newFeedback.start == Feedback::VALID_HEADER && checksum == controller.newFeedback.checksum) {
                    // Copy the new data
                    memcpy(&controller.feedback, &controller.newFeedback, sizeof(controller.feedback));

                    Serial.println("parsed");
                } else {
                    Serial.println("Non-valid data skipped");

                    if (controller.newFeedback.start == Feedback::VALID_HEADER)
                        Serial.println("header matched");
                    else
                        Serial.println("header did not match");

                    if (checksum == controller.newFeedback.checksum)
                        Serial.println("checksum matched");
                    else
                        Serial.println("checksum did not match");
                }
                controller.idx = 0; // Reset the index (it prevents to enter in this if condition in the next cycle)
            }

            // Update previous states
            controller.incomingBytePrev  = controller.incomingByte;
        }
    }
}

template<typename T>
T scaleBetween(T x, T in_min, T in_max, T out_min, T out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
template<typename T>
T scaleBetweenWithFixes(T x, T in_min, T in_max, T out_min, T out_max) {
    if (x < in_min)
        x = in_min;
    else if (x > in_max)
        x = in_max;

    return scaleBetween(x, in_min, in_max, out_min, out_max);
}
}

void setup()
{
    command.left.enable = command.right.enable = true;
    command.left.ctrlMod = command.right.ctrlMod = ControlMode::Torque;

    Serial.begin(115200);
    Serial.println("setup()");

    Serial1.begin(38400, SERIAL_8N1, 25, 27);

    Serial2.begin(38400, SERIAL_8N1, 13, 15);

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
      Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
    }

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.cp437(true);
}

void loop()
{

    /*

#define BAT_CELLS               12        // battery number of cells. Normal Hoverboard battery: 10s
#define BAT_LOW_LVL1_ENABLE     0         // to beep or not to beep, 1 or 0
#define BAT_LOW_LVL2_ENABLE     1         // to beep or not to beep, 1 or 0
#define BAT_LOW_LVL1            (360 * BAT_CELLS * BAT_CALIB_ADC) / BAT_CALIB_REAL_VOLTAGE    // gently beeps at this voltage level. [V*100/cell]. In this case 3.60 V/cell
#define BAT_LOW_LVL2            (350 * BAT_CELLS * BAT_CALIB_ADC) / BAT_CALIB_REAL_VOLTAGE    // your battery is almost empty. Charge now! [V*100/cell]. In this case 3.50 V/cell
#define BAT_LOW_DEAD            (337 * BAT_CELLS * BAT_CALIB_ADC) / BAT_CALIB_REAL_VOLTAGE    // undervoltage poweroff. (while not driving) [V*100/cell]. In this case 3.37 V/cell

    // ####### BEEP AND EMERGENCY POWEROFF #######
    if (TEMP_POWEROFF_ENABLE && board_temp_deg_c >= TEMP_POWEROFF) {  // poweroff before mainboard burns OR low bat 3
      poweroff();
    } else if (TEMP_WARNING_ENABLE && board_temp_deg_c >= TEMP_WARNING) {  // beep if mainboard gets hot
      buzzerFreq = 4;
      buzzerPattern = 1;
    } else if (batVoltage < BAT_LOW_LVL1 && batVoltage >= BAT_LOW_LVL2 && BAT_LOW_LVL1_ENABLE) {  // low bat 1: slow beep
      buzzerFreq = 5;
      buzzerPattern = 42;
    } else if (batVoltage < BAT_LOW_LVL2 && batVoltage >= BAT_LOW_DEAD && BAT_LOW_LVL2_ENABLE) {  // low bat 2: fast beep
      buzzerFreq = 5;
      buzzerPattern = 6;
    } else if (errCode_Left || errCode_Right || timeoutFlag) {  // beep in case of Motor error or serial timeout - fast beep
      buzzerFreq = 12;
      buzzerPattern = 1;
    } else if (BEEPS_BACKWARD && speedRL < -50) {  // backward beep
      buzzerFreq = 5;
      buzzerPattern = 1;
    } else {  // do not beep
      buzzerFreq = 0;
      buzzerPattern = 0;
    }

    // ####### INACTIVITY TIMEOUT #######
    if (abs(speedRL) > 50) {
      inactivity_timeout_counter = 0;
    } else {
      inactivity_timeout_counter ++;
    }
    if (inactivity_timeout_counter > (INACTIVITY_TIMEOUT * 60 * 1000) / (DELAY_IN_MAIN_LOOP + 1)) {  // rest of main loop needs maybe 1ms
      poweroff();
    }

    */

    display.clearDisplay();
    display.setCursor(0, 0);

    analogRead(gasPin);
    delay(2);
    const auto raw_gas = analogRead(gasPin);

    analogRead(bremsPin);
    delay(2);
    const auto raw_brems = analogRead(bremsPin);


    auto gas_hebel = scaleBetweenWithFixes<float>(raw_gas, gasMin, gasMax, 0., 1000.);
    gas_hebel = (gas_hebel * gas_hebel) / 1000;

    auto brems_hebel = scaleBetweenWithFixes<float>(raw_brems, bremsMin, bremsMax, 0., 1000.);
    brems_hebel = (brems_hebel * brems_hebel) / 1000;

    int16_t pwm;
    if (gas_hebel >= 950.)
        pwm = gas_hebel + (brems_hebel/2.);
    else
        pwm = gas_hebel - brems_hebel;

    command.left = {};
    command.left.enable=true,
    command.left.pwm=pwm,
    command.left.ctrlTyp=ControlType::FieldOrientedControl,
    command.left.ctrlMod=ControlMode::Torque,
    command.left.iMotMax=20,
    command.left.iDcMax=23,
    command.left.nMotMax=5000,
    command.left.fieldWeakMax=13;

    command.right = command.left;

    command.buzzer = {};

    switch (screen)
    {
    case ScreenA:
        display.printf("potis: %i - %i\n", raw_gas, raw_brems);
        display.printf("filtered: %.1f - %.1f\n", gas_hebel, brems_hebel);
        display.printf("pwm: %i\n\n", pwm);
        display.printf("voltage: %.1fV - %.1fV\n", first.feedback.batVoltage/100., second.feedback.batVoltage/100.);
        display.printf("tempera: %.1fC - %.1fC\n", first.feedback.boardTemp/100., second.feedback.boardTemp/100.);
        break;
    case ScreenB:
        display.printf("speed: %i - %i\n", first.feedback.left.speed, first.feedback.right.speed);
        display.printf("       %i - %i\n", second.feedback.left.speed, second.feedback.right.speed);
        display.printf("current: %i - %i\n", first.feedback.left.current, first.feedback.right.current);
        display.printf("         %i - %i\n", second.feedback.left.current, second.feedback.right.current);
        display.printf("error: %i - %i\n", first.feedback.left.error, first.feedback.right.error);
        display.printf("       %i - %i\n", second.feedback.left.error, second.feedback.right.error);
        break;
    case ScreenC:
        display.printf("angle: %i - %i\n", first.feedback.left.angle, first.feedback.right.angle);
        display.printf("       %i - %i\n", second.feedback.left.angle, second.feedback.right.angle);
        display.printf("halls: %d %d %d\n", first.feedback.left.hallA, first.feedback.left.hallB, first.feedback.left.hallC);
        display.printf("       %d %d %d\n", first.feedback.right.hallA, first.feedback.right.hallB, first.feedback.left.hallC);
        display.printf("       %d %d %d\n", second.feedback.left.hallA, second.feedback.left.hallB, second.feedback.left.hallC);
        display.printf("       %d %d %d\n", second.feedback.right.hallA, second.feedback.right.hallB, second.feedback.left.hallC);
    }

    display.display();

    while(Serial.available())
    {
        switch (Serial.read())
        {
        case 't':
        case 'T':
            power_toggle = !power_toggle;
            Serial.printf("power: %d\n", power_toggle);
            command.poweroff = power_toggle;
            break;
        case 'l':
        case 'L':
            led_toggle = !led_toggle;
            Serial.printf("led: %d\n", led_toggle);
            command.led = led_toggle;
            break;
        case '0': command.buzzer.freq = 0; break;
        case '1': command.buzzer.freq = 1; break;
        case '2': command.buzzer.freq = 2; break;
        case '3': command.buzzer.freq = 3; break;
        case '4': command.buzzer.freq = 4; break;
        case '5': command.buzzer.freq = 5; break;
        case '6': command.buzzer.freq = 6; break;
        case '7': command.buzzer.freq = 7; break;
        case '8': command.buzzer.freq = 8; break;
        case '9': command.buzzer.freq = 9; break;
        }
    }

    const auto now = millis();
    if (now - lastSendCommand > 50)
    {
        lastSendCommand = now;
        sendCommand();
    }

    if (now - lastAlive > 100)
    {
        lastAlive = now;
        Serial.println("alive");
    }

    if (false && now - lastScreenSwitch > 5000)
    {
        lastScreenSwitch = now;
        switch(screen)
        {
        case ScreenA: screen = ScreenB; break;
        case ScreenB: screen = ScreenC; break;
        case ScreenC: screen = ScreenA; break;
        }
    }

    receiveFeedback();
}
