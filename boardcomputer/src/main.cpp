#include <Arduino.h>
#include <ArduinoJson.h>
#include <HardwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <array>

#include "../../common.h"

bool power_toggle{false};
bool led_toggle{false};

Command command;

StaticJsonDocument<1024> doc;

struct Controller {
    struct {
      unsigned long time = 0;
      int16_t   leftAngle, rightAngle;
      int16_t   leftSpeed, rightSpeed;
      uint16_t  leftError, rightError;
      int16_t   leftCurrent, rightCurrent;
      int16_t   batVoltage;
      int16_t   boardTemp;
      int16_t   hallLA, hallLB, hallLC;
      int16_t   hallRA, hallRB, hallRC;
    } feedback;

    std::array<char, 4096> messageBuffer {};
    std::array<char, 4096>::iterator bufferIter;

    Controller() : bufferIter{messageBuffer.begin()} {}
} first, second;

void Send()
{
    command.start = Command::VALID_HEADER;
    command.checksum = calculateChecksum(command);
    Serial1.write((uint8_t *) &command, sizeof(command));
    Serial2.write((uint8_t *) &command, sizeof(command));
}

int last = millis();

Adafruit_SSD1306 display(128, 64, &Wire, 4);

void setup()
{
    command.left.enable = command.right.enable = true;
    command.left.ctrlMod = command.right.ctrlMod = ControlMode::Torque;

    Serial.begin(115200);
    Serial.println("setup()");

    Serial1.begin(38400, SERIAL_8N1, 25, 27);

    Serial2.begin(38400, SERIAL_8N1, 18, 19);

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
      Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
    }

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.cp437(true);

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Initializing...");
    display.display();
}

enum { ScreenA, ScreenB, ScreenC } screen { ScreenA };
unsigned long lastScreenSwitch = 0;

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

    analogRead(33);
    delay(2);
    const auto raw_gas = analogRead(33);

    analogRead(35);
    delay(2);
    const auto raw_brems = analogRead(35);


    auto gas_hebel = raw_gas/4096.*1000.;
    gas_hebel = (gas_hebel * gas_hebel) / 1000;
    auto brems_hebel = raw_brems/4096.*500.;
    //gas_hebel = (gas_hebel * gas_hebel) / 1000;

    int16_t pwm;
    if (gas_hebel >= 950.)
        pwm = gas_hebel + brems_hebel;
    else
        pwm = gas_hebel - brems_hebel;

    command.left.pwm = pwm;
    command.right.pwm = pwm;

    switch (screen)
    {
    case ScreenA:
        display.printf("potis: %i - %i\n", raw_gas, raw_brems);
        display.printf("filtered: %i - %i\n", (int16_t)gas_hebel, (int16_t)brems_hebel);
        display.printf("pwm: %i\n\n", pwm);
        display.printf("voltage: %i - %i\n", first.feedback.batVoltage, second.feedback.batVoltage);
        display.printf("tempera: %i - %i\n", first.feedback.boardTemp, second.feedback.boardTemp);
        break;
    case ScreenB:
        display.printf("speed: %i - %i\n", first.feedback.leftSpeed, first.feedback.rightSpeed);
        display.printf("       %i - %i\n", second.feedback.leftSpeed, second.feedback.rightSpeed);
        display.printf("current: %i - %i\n", first.feedback.leftCurrent, first.feedback.rightCurrent);
        display.printf("         %i - %i\n", second.feedback.leftCurrent, second.feedback.rightCurrent);
        display.printf("error: %i - %i\n", first.feedback.leftError, first.feedback.rightError);
        display.printf("       %i - %i\n", second.feedback.leftError, second.feedback.rightError);
        break;
    case ScreenC:
        display.printf("angle: %i - %i\n", first.feedback.leftAngle, first.feedback.rightAngle);
        display.printf("       %i - %i\n", second.feedback.leftAngle, second.feedback.rightAngle);
        display.printf("halls: %i %i %i\n", first.feedback.hallLA, first.feedback.hallLB, first.feedback.hallLC);
        display.printf("       %i %i %i\n", first.feedback.hallRA, first.feedback.hallRB, first.feedback.hallRC);
        display.printf("       %i %i %i\n", second.feedback.hallLA, second.feedback.hallLB, second.feedback.hallLC);
        display.printf("       %i %i %i\n", second.feedback.hallRA, second.feedback.hallRB, second.feedback.hallRC);
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
    if (now - last > 50)
    {
        last = now;
        Send();
    }

    if (now - lastScreenSwitch > 2000)
    {
        lastScreenSwitch = now;
        switch(screen)
        {
        case ScreenA: screen = ScreenB; break;
        case ScreenB: screen = ScreenC; break;
        case ScreenC: screen = ScreenA; break;
        }
    }

    const auto handle_serial = [now](HardwareSerial &serial, Controller &controller){
        while (serial.available())
        {
            *controller.bufferIter = char(serial.read());
            if (*controller.bufferIter == '\n')
            {
                DeserializationError error = deserializeJson(doc, controller.messageBuffer.begin(),
                                                             std::distance(controller.messageBuffer.begin(), controller.bufferIter));

                if (error)
                {
                    Serial.print(F("deserializeJson() failed 1: "));
                    Serial.println(error.c_str());
                }
                else
                {
#define FIELD_leftAngle "a"
#define FIELD_rightAngle "b"
#define FIELD_leftSpeed "c"
#define FIELD_rightSpeed "d"
#define FIELD_leftCurrent "e"
#define FIELD_rightCurrent "f"
#define FIELD_leftError "g"
#define FIELD_rightError "h"
#define FIELD_batVoltage "i"
#define FIELD_boardTemp "j"
#define FIELD_hallLA "k"
#define FIELD_hallLB "l"
#define FIELD_hallLC "m"
#define FIELD_hallRA "n"
#define FIELD_hallRB "o"
#define FIELD_hallRC "p"
#define FIELD_chopsL "q"
#define FIELD_chopsR "r"

                    controller.feedback.time = now;
                    controller.feedback.leftAngle = doc[F(FIELD_leftAngle)].as<int16_t>();
                    controller.feedback.rightAngle = doc[F(FIELD_rightAngle)].as<int16_t>();
                    controller.feedback.leftSpeed = doc[F(FIELD_leftSpeed)].as<int16_t>();
                    controller.feedback.rightSpeed = doc[F(FIELD_rightSpeed)].as<int16_t>();
                    controller.feedback.leftCurrent = doc[F(FIELD_leftCurrent)].as<int16_t>();
                    controller.feedback.rightCurrent = doc[F(FIELD_rightCurrent)].as<int16_t>();
                    controller.feedback.leftError =doc[F(FIELD_leftError)].as<uint16_t>();
                    controller.feedback.rightError =doc[F(FIELD_rightError)].as<uint16_t>();
                    controller.feedback.batVoltage = doc[F(FIELD_batVoltage)].as<int16_t>();
                    controller.feedback.boardTemp = doc[F(FIELD_boardTemp)].as<int16_t>();
                    controller.feedback.hallLA = doc[F(FIELD_hallLA)].as<int16_t>();
                    controller.feedback.hallLB = doc[F(FIELD_hallLB)].as<int16_t>();
                    controller.feedback.hallLC = doc[F(FIELD_hallLC)].as<int16_t>();
                    controller.feedback.hallRA = doc[F(FIELD_hallRA)].as<int16_t>();
                    controller.feedback.hallRB = doc[F(FIELD_hallRB)].as<int16_t>();
                    controller.feedback.hallRC = doc[F(FIELD_hallRC)].as<int16_t>();

                    Serial.println("parsed");
                }

                controller.bufferIter = controller.messageBuffer.begin();
            }
            else
                controller.bufferIter++;
        }
    };

    handle_serial(Serial1, first);
    handle_serial(Serial2, second);
}
