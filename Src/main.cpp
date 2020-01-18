/*
* This file is part of the hoverboard-firmware-hack project.
*
* Copyright (C) 2017-2018 Rene Hopf <renehopf@mac.com>
* Copyright (C) 2017-2018 Nico Stute <crinq@crinq.de>
* Copyright (C) 2017-2018 Niklas Fauth <niklas.fauth@kit.fail>
* Copyright (C) 2019-2020 Emanuel FERU <aerdronix@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <algorithm>

#include "stm32f1xx_hal.h"

#include "defines.h"
#include "config.h"

extern "C" {
#include "BLDC_controller.h"
}

TIM_HandleTypeDef htim_right;
TIM_HandleTypeDef htim_left;
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
UART_HandleTypeDef huart2;
//UART_HandleTypeDef huart3;

DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;

//DMA_HandleTypeDef hdma_usart3_rx;
//DMA_HandleTypeDef hdma_usart3_tx;

volatile struct {
    uint16_t dcr;
    uint16_t dcl;
    uint16_t rl1;
    uint16_t rl2;
    uint16_t rr1;
    uint16_t rr2;
    uint16_t batt1;
    uint16_t l_tx2;
    uint16_t temp;
    uint16_t l_rx2;
} adc_buffer;

// ###############################################################################

volatile uint32_t timeout;

uint8_t buzzerFreq       = 0;
uint8_t buzzerFreqReq    = 0;
uint8_t buzzerPattern    = 0;
uint8_t buzzerPatternReq = 0;

uint32_t buzzerTimer = 0;

uint16_t offsetcount = 0;
int16_t offsetrl1    = 2000;
int16_t offsetrl2    = 2000;
int16_t offsetrr1    = 2000;
int16_t offsetrr2    = 2000;
int16_t offsetdcl    = 2000;
int16_t offsetdcr    = 2000;

int16_t batVoltage       = (400 * BAT_CELLS * BAT_CALIB_ADC) / BAT_CALIB_REAL_VOLTAGE;
int32_t batVoltageFixdt  = (400 * BAT_CELLS * BAT_CALIB_ADC) / BAT_CALIB_REAL_VOLTAGE << 20;  // Fixed-point filter output initialized at 400 V*100/cell = 4 V/cell converted to fixed-point

// Matlab includes and defines - from auto-code generation
// ###############################################################################
#include "BLDC_controller.h"      /* Model's header file */
#include "rtwtypes.h"

struct {
    RT_MODEL rtM; /* Real-time model */
    P     rtP;    /* Block parameters (auto storage) */
    DW    rtDW;   /* Observable states */
    ExtU  rtU;    /* External inputs */
    ExtY  rtY;    /* External outputs */

    struct {
        bool enable = false;
        int pwm = 0;
        uint8_t ctrlTyp = CTRL_TYP_SEL;
        uint8_t ctrlMod = CTRL_MOD_REQ;
    } actual, requested;
} left, right;

extern "C" const P rtP_Left; // default settings defined in BLDC_controller_data.c

volatile struct {
    uint16_t start;

    int16_t enableL, enableR;
    int16_t pwmL, pwmR;
    int16_t ctrlTypL, ctrlTypR;
    int16_t ctrlModL, ctrlModR;
    int16_t iMotMaxL, iMotMaxR;
    int16_t iDcMaxL, iDcMaxR;
    int16_t nMotMaxL, nMotMaxR;
    int16_t phaseAdvMaxL, phaseAdvMaxR;
    int16_t fieldWeakMaxL, fieldWeakMaxR;

    int16_t buzzerFreq, buzzerPattern, poweroff;

    uint16_t  checksum;
} command;

int16_t timeoutCntSerial   = 0;  // Timeout counter for Rx Serial command
uint8_t timeoutFlagSerial  = 0;  // Timeout Flag for Rx Serial command: 0 = OK, 1 = Problem detected (line disconnected or wrong Rx data)

int16_t iMotMaxLReq = I_MOT_MAX;
volatile int16_t iMotMaxL = I_MOT_MAX;
int16_t iMotMaxRReq = I_MOT_MAX;
volatile int16_t iMotMaxR = I_MOT_MAX;

int16_t iDcMaxLReq = I_DC_MAX;
volatile int16_t iDcMaxL = I_DC_MAX;
int16_t iDcMaxRReq = I_DC_MAX;
volatile int16_t iDcMaxR = I_DC_MAX;

int16_t nMotMaxLReq = N_MOT_MAX;
volatile int16_t nMotMaxL = N_MOT_MAX;
int16_t nMotMaxRReq = N_MOT_MAX;
volatile int16_t nMotMaxR = N_MOT_MAX;

int16_t fieldWeakMaxLReq = FIELD_WEAK_MAX;
volatile int16_t fieldWeakMaxL = FIELD_WEAK_MAX;
int16_t fieldWeakMaxRReq = FIELD_WEAK_MAX;
volatile int16_t fieldWeakMaxR = FIELD_WEAK_MAX;

int16_t phaseAdvMaxLReq = PHASE_ADV_MAX;
volatile int16_t phaseAdvMaxL = PHASE_ADV_MAX;
int16_t phaseAdvMaxRReq = PHASE_ADV_MAX;
volatile int16_t phaseAdvMaxR = PHASE_ADV_MAX;

uint32_t inactivity_timeout_counter;
uint32_t main_loop_counter;

uint32_t chopsL = 0;
uint32_t chopsR = 0;

namespace {
void filtLowPass32(int16_t u, uint16_t coef, int32_t *y);

void rateLimiter16(int16_t u, int16_t rate, int16_t *y);

void SystemClock_Config();

void UART2_Init();

//void UART3_Init();

void MX_GPIO_Init();

void MX_TIM_Init();

void MX_ADC1_Init();

void MX_ADC2_Init();

void poweroff();

} // anonymous namespace

int main() {

  HAL_Init();
  __HAL_RCC_AFIO_CLK_ENABLE();
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
  /* System interrupt init*/
  /* MemoryManagement_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
  /* BusFault_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
  /* UsageFault_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
  /* SVCall_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
  /* DebugMonitor_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
  /* PendSV_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);
  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

  SystemClock_Config();

  __HAL_RCC_DMA1_CLK_DISABLE();
  MX_GPIO_Init();
  MX_TIM_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();

  HAL_GPIO_WritePin(OFF_PORT, OFF_PIN, GPIO_PIN_SET);

  HAL_ADC_Start(&hadc1);
  HAL_ADC_Start(&hadc2);

// Matlab Init
// ###############################################################################
  
  /* Set BLDC controller parameters */ 
  left.rtP = rtP_Left;
  left.rtP.b_selPhaABCurrMeas   = 1;            // Left motor measured current phases = {iA, iB} -> do NOT change
  left.rtP.z_ctrlTypSel         = left.actual.ctrlTyp;
  left.rtP.b_diagEna            = DIAG_ENA;
  left.rtP.i_max                = (iMotMaxL * A2BIT_CONV) << 4;        // fixdt(1,16,4)
  left.rtP.n_max                = nMotMaxL << 4;                       // fixdt(1,16,4)
  left.rtP.b_fieldWeakEna       = FIELD_WEAK_ENA;
  left.rtP.id_fieldWeakMax      = (fieldWeakMaxL * A2BIT_CONV) << 4;   // fixdt(1,16,4)
  left.rtP.a_phaAdvMax          = phaseAdvMaxL << 4;                   // fixdt(1,16,4)
  left.rtP.r_fieldWeakHi        = FIELD_WEAK_HI << 4;                   // fixdt(1,16,4)
  left.rtP.r_fieldWeakLo        = FIELD_WEAK_LO << 4;                   // fixdt(1,16,4)

  right.rtP = rtP_Left;
  right.rtP.b_selPhaABCurrMeas  = 0;            // Left motor measured current phases = {iB, iC} -> do NOT change
  right.rtP.z_ctrlTypSel         = right.actual.ctrlTyp;
  right.rtP.b_diagEna            = DIAG_ENA;
  right.rtP.i_max                = (iMotMaxR * A2BIT_CONV) << 4;        // fixdt(1,16,4)
  right.rtP.n_max                = nMotMaxR << 4;                       // fixdt(1,16,4)
  right.rtP.b_fieldWeakEna       = FIELD_WEAK_ENA;
  right.rtP.id_fieldWeakMax      = (fieldWeakMaxR * A2BIT_CONV) << 4;   // fixdt(1,16,4)
  right.rtP.a_phaAdvMax          = phaseAdvMaxR << 4;                   // fixdt(1,16,4)
  right.rtP.r_fieldWeakHi        = FIELD_WEAK_HI << 4;                   // fixdt(1,16,4)
  right.rtP.r_fieldWeakLo        = FIELD_WEAK_LO << 4;                   // fixdt(1,16,4)

  /* Pack LEFT motor data into RTM */
  left.rtM.defaultParam        = &left.rtP;
  left.rtM.dwork               = &left.rtDW;
  left.rtM.inputs              = &left.rtU;
  left.rtM.outputs             = &left.rtY;

  /* Pack RIGHT motor data into RTM */
  right.rtM.defaultParam       = &right.rtP;
  right.rtM.dwork              = &right.rtDW;
  right.rtM.inputs             = &right.rtU;
  right.rtM.outputs            = &right.rtY;

  /* Initialize BLDC controllers */
  BLDC_controller_initialize(&left.rtM);
  BLDC_controller_initialize(&right.rtM);

// ###############################################################################

  for (int i = 8; i >= 0; i--) {
    buzzerFreq = (uint8_t)i;
    HAL_Delay(100);
  }
  buzzerFreq = 0;

  HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);

  UART2_Init();
  //UART3_Init();

  HAL_UART_Receive_DMA(&huart2, (uint8_t *)&command, sizeof(command));

  int32_t board_temp_adcFixdt = adc_buffer.temp << 20;  // Fixed-point filter output initialized with current ADC converted to fixed-point
  int16_t board_temp_adcFilt  = adc_buffer.temp;
  int16_t board_temp_deg_c;

  while(1) {
    HAL_Delay(DELAY_IN_MAIN_LOOP); //delay in ms

    uint16_t checksum = command.start ^
            command.enableL ^ command.enableR ^
            command.pwmL ^ command.pwmR ^
            command.ctrlTypL ^ command.ctrlTypR ^
            command.ctrlModL ^ command.ctrlModR ^
            command.iMotMaxL ^ command.iMotMaxR ^
            command.iDcMaxL ^ command.iDcMaxR ^
            command.nMotMaxL ^ command.nMotMaxR ^
            command.phaseAdvMaxL ^ command.phaseAdvMaxR ^
            command.fieldWeakMaxL ^ command.fieldWeakMaxR ^
            command.buzzerFreq ^ command.buzzerPattern ^ command.poweroff;
    if (command.start == START_FRAME && command.checksum == checksum)
    {
        if (timeoutFlagSerial)                        // Check for previous timeout flag
        {
            if (timeoutCntSerial-- <= 0)              // Timeout de-qualification
                timeoutFlagSerial = 0;                // Timeout flag cleared
        }
        else
        {
            left.requested.enable = command.enableL;
            right.requested.enable = command.enableR;

            left.requested.pwm = command.pwmL;
            right.requested.pwm = command.pwmR;

            left.requested.ctrlTyp = command.ctrlTypL;
            right.requested.ctrlTyp = command.ctrlTypR;

            left.requested.ctrlMod = command.ctrlModL;
            right.requested.ctrlMod = command.ctrlModR;

            buzzerFreqReq = command.buzzerFreq;
            buzzerPatternReq = command.buzzerPattern;

            iMotMaxLReq = command.iMotMaxL;
            iMotMaxRReq = command.iMotMaxR;

            iDcMaxLReq = command.iDcMaxL;
            iDcMaxRReq = command.iDcMaxR;

            nMotMaxLReq = command.nMotMaxL;
            nMotMaxRReq = command.nMotMaxR;

            fieldWeakMaxLReq = command.fieldWeakMaxL;
            fieldWeakMaxRReq = command.fieldWeakMaxR;

            phaseAdvMaxLReq = command.phaseAdvMaxL;
            phaseAdvMaxRReq = command.phaseAdvMaxR;

            if (command.poweroff)
                poweroff();

            command.start     = 0xFFFF;                 // Change the Start Frame for timeout detection in the next cycle
            timeoutCntSerial  = 0;                      // Reset the timeout counter
        }
    }
    else
    {
        if (timeoutCntSerial++ >= SERIAL_TIMEOUT) // Timeout qualification
        {
            timeoutFlagSerial = 1;                      // Timeout detected
            timeoutCntSerial  = SERIAL_TIMEOUT;         // Limit timout counter value
        }

        // Check periodically the received Start Frame. If it is NOT OK, most probably we are out-of-sync. Try to re-sync by reseting the DMA
        if (main_loop_counter % 25 == 0 && command.start != START_FRAME && command.start != 0xFFFF)
        {
            HAL_UART_DMAStop(&huart2);
            HAL_UART_Receive_DMA(&huart2, (uint8_t *)&command, sizeof(command));
        }
    }

    if (timeoutFlagSerial)
    {
        left.actual.enable = 1;
        right.actual.enable = 1;

        left.actual.pwm = 0;
        right.actual.pwm = 0;

        left.actual.ctrlTyp = 2;
        right.actual.ctrlTyp = 2;

        left.actual.ctrlMod = 0;                                // OPEN_MODE request. This will bring the motor power to 0 in a controlled way
        right.actual.ctrlMod = 0;                                // OPEN_MODE request. This will bring the motor power to 0 in a controlled way

        buzzerFreq    = 24;
        buzzerPattern = 1;

        iMotMaxL = I_MOT_MAX;
        iMotMaxR = I_MOT_MAX;

        iDcMaxL = I_DC_MAX;
        iDcMaxR = I_DC_MAX;

        nMotMaxL = N_MOT_MAX;
        nMotMaxR = N_MOT_MAX;

        fieldWeakMaxL = FIELD_WEAK_MAX;
        fieldWeakMaxR = FIELD_WEAK_MAX;

        phaseAdvMaxL = PHASE_ADV_MAX;
        phaseAdvMaxR = PHASE_ADV_MAX;
    }
    else
    {
        left.actual.enable = left.requested.enable;
        right.actual.enable = right.requested.enable;

        left.actual.pwm = left.requested.pwm;
        right.actual.pwm = right.requested.pwm;

        left.actual.ctrlTyp = left.requested.ctrlTyp;
        right.actual.ctrlTyp = right.requested.ctrlTyp;

        left.actual.ctrlMod = left.requested.ctrlMod;
        right.actual.ctrlMod = right.requested.ctrlMod;

        buzzerFreq = buzzerFreqReq;
        buzzerPattern = buzzerPatternReq;

        iMotMaxL = iMotMaxLReq;
        iMotMaxR = iMotMaxRReq;

        iDcMaxL = iDcMaxLReq;
        iDcMaxR = iDcMaxRReq;

        nMotMaxL = nMotMaxLReq;
        nMotMaxR = nMotMaxRReq;

        fieldWeakMaxL = fieldWeakMaxLReq;
        fieldWeakMaxR = fieldWeakMaxRReq;

        phaseAdvMaxL = phaseAdvMaxLReq;
        phaseAdvMaxR = phaseAdvMaxRReq;
    }
    timeout = 0;


    // ####### CALC BOARD TEMPERATURE #######
    filtLowPass32(adc_buffer.temp, TEMP_FILT_COEF, &board_temp_adcFixdt);
    board_temp_adcFilt  = (int16_t)(board_temp_adcFixdt >> 20);  // convert fixed-point to integer
    board_temp_deg_c    = (TEMP_CAL_HIGH_DEG_C - TEMP_CAL_LOW_DEG_C) * (board_temp_adcFilt - TEMP_CAL_LOW_ADC) / (TEMP_CAL_HIGH_ADC - TEMP_CAL_LOW_ADC) + TEMP_CAL_LOW_DEG_C;

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

    if (main_loop_counter % 25 == 0) {    // Send data periodically
        if(UART_DMA_CHANNEL->CNDTR == 0) {
                  int strLength;
                  char uart_buf[512];
                  strLength = sprintf((char *)(uintptr_t)uart_buf,
                                        "{ "
                                          "\"" FIELD_leftAngle "\": %i, "
                                          "\"" FIELD_rightAngle "\": %i, "
                                          "\"" FIELD_leftSpeed "\": %i, "
                                          "\"" FIELD_rightSpeed "\": %i, "
                                          "\"" FIELD_leftCurrent "\": %i, "
                                          "\"" FIELD_rightCurrent "\": %i, "
                                          "\"" FIELD_leftError "\": %i, "
                                          "\"" FIELD_rightError "\": %i, "
                                          "\"" FIELD_batVoltage "\": %i, "
                                          "\"" FIELD_boardTemp "\": %i, "
                                          "\"" FIELD_hallLA "\": %i, "
                                          "\"" FIELD_hallLB "\": %i, "
                                          "\"" FIELD_hallLC "\": %i, "
                                          "\"" FIELD_hallRA "\": %i, "
                                          "\"" FIELD_hallRB "\": %i, "
                                          "\"" FIELD_hallRC "\": %i, "
                                          "\"" FIELD_chopsL "\": %i, "
                                          "\"" FIELD_chopsR "\": %i "
                                        "}\n",
                                        left.rtY.a_elecAngle, right.rtY.a_elecAngle,
                                        left.rtY.n_mot, right.rtY.n_mot,
                                        left.rtU.i_DCLink, right.rtU.i_DCLink,
                                        left.rtY.z_errCode, right.rtY.z_errCode,
                                        (batVoltage * BAT_CALIB_REAL_VOLTAGE / BAT_CALIB_ADC),
                                        board_temp_deg_c,
                                        left.rtU.b_hallA, left.rtU.b_hallB, left.rtU.b_hallC,
                                        right.rtU.b_hallA, right.rtU.b_hallB, right.rtU.b_hallC,
                                        chopsL, chopsR);
                  chopsL = 0;
                  chopsR = 0;

                  if(UART_DMA_CHANNEL->CNDTR == 0) {
                    UART_DMA_CHANNEL->CCR    &= ~DMA_CCR_EN;
                    UART_DMA_CHANNEL->CNDTR   = strLength;
                    UART_DMA_CHANNEL->CMAR    = uint64_t(&uart_buf);
                    UART_DMA_CHANNEL->CCR    |= DMA_CCR_EN;
                  }
                }
    }    

    HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
    // ####### POWEROFF BY POWER-BUTTON #######
    if (HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN)) {
      left.actual.enable = right.actual.enable = 0;                                             // disable motors
      while (HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN)) {}    // wait until button is released
      if(__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST)) {               // do not power off after software reset (from a programmer/debugger)
        __HAL_RCC_CLEAR_RESET_FLAGS();                        // clear reset flags
      } else {
        poweroff();                                           // release power-latch
      }
    }

    main_loop_counter++;
    timeout++;
  }
}

// =================================
// DMA interrupt frequency =~ 16 kHz
// =================================
extern "C" void DMA1_Channel1_IRQHandler() {

  DMA1->IFCR = DMA_IFCR_CTCIF1;
  // HAL_GPIO_WritePin(LED_PORT, LED_PIN, 1);
  // HAL_GPIO_TogglePin(LED_PORT, LED_PIN);

  if(offsetcount < 2000) {  // calibrate ADC offsets
    offsetcount++;
    offsetrl1 = (adc_buffer.rl1 + offsetrl1) / 2;
    offsetrl2 = (adc_buffer.rl2 + offsetrl2) / 2;
    offsetrr1 = (adc_buffer.rr1 + offsetrr1) / 2;
    offsetrr2 = (adc_buffer.rr2 + offsetrr2) / 2;
    offsetdcl = (adc_buffer.dcl + offsetdcl) / 2;
    offsetdcr = (adc_buffer.dcr + offsetdcr) / 2;
    return;
  }

  if (buzzerTimer % 1000 == 0) {  // because you get float rounding errors if it would run every time -> not any more, everything converted to fixed-point
    filtLowPass32(adc_buffer.batt1, BAT_FILT_COEF, &batVoltageFixdt);
    batVoltage = (int16_t)(batVoltageFixdt >> 20);  // convert fixed-point to integer
  }

  // Get Left motor currents
  int16_t curL_phaA = (int16_t)(offsetrl1 - adc_buffer.rl1);
  int16_t curL_phaB = (int16_t)(offsetrl2 - adc_buffer.rl2);
  int16_t curL_DC   = (int16_t)(offsetdcl - adc_buffer.dcl);

  // Get Right motor currents
  int16_t curR_phaB = (int16_t)(offsetrr1 - adc_buffer.rr1);
  int16_t curR_phaC = (int16_t)(offsetrr2 - adc_buffer.rr2);
  int16_t curR_DC   = (int16_t)(offsetdcr - adc_buffer.dcr);

  const int8_t chopL = std::abs(curL_DC) > (iDcMaxL * A2BIT_CONV);
  if (chopL)
      chopsL++;

  // Disable PWM when current limit is reached (current chopping)
  // This is the Level 2 of current protection. The Level 1 should kick in first given by I_MOT_MAX
  if(chopL || timeout > TIMEOUT || left.actual.enable == 0) {
    LEFT_TIM->BDTR &= ~TIM_BDTR_MOE;
  } else {
    LEFT_TIM->BDTR |= TIM_BDTR_MOE;
  }

  const int8_t chopR = std::abs(curR_DC) > (iDcMaxR * A2BIT_CONV);
  if (chopR)
      chopsR++;

  if(chopR || timeout > TIMEOUT || right.actual.enable == 0) {
    RIGHT_TIM->BDTR &= ~TIM_BDTR_MOE;
  } else {
    RIGHT_TIM->BDTR |= TIM_BDTR_MOE;
  }

  //create square wave for buzzer
  buzzerTimer++;
  if (buzzerFreq != 0 && (buzzerTimer / 5000) % (buzzerPattern + 1) == 0) {
    if (buzzerTimer % buzzerFreq == 0) {
      HAL_GPIO_TogglePin(BUZZER_PORT, BUZZER_PIN);
    }
  } else {
      HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
  }

  // ############################### MOTOR CONTROL ###############################

  static boolean_T OverrunFlag = false;

  /* Check for overrun */
  if (OverrunFlag) {
    return;
  }
  OverrunFlag = true;

  constexpr int32_t pwm_res  = 64000000 / 2 / PWM_FREQ; // = 2000
  constexpr int32_t pwm_margin = 100;        /* This margin allows to always have a window in the PWM signal for proper Phase currents measurement */

  /* Make sure to stop BOTH motors in case of an error */
  const bool enableLFin = left.actual.enable && left.rtY.z_errCode == 0 && right.rtY.z_errCode == 0;
  const bool enableRFin = right.actual.enable && left.rtY.z_errCode == 0 && right.rtY.z_errCode == 0;

  // ========================= LEFT MOTOR ============================
    // Get hall sensors values
    uint8_t hall_ul = !(LEFT_HALL_U_PORT->IDR & LEFT_HALL_U_PIN);
    uint8_t hall_vl = !(LEFT_HALL_V_PORT->IDR & LEFT_HALL_V_PIN);
    uint8_t hall_wl = !(LEFT_HALL_W_PORT->IDR & LEFT_HALL_W_PIN);

    /* Set motor inputs here */
    left.rtP.z_ctrlTypSel         = left.actual.ctrlTyp;
    left.rtP.i_max                = (iMotMaxL * A2BIT_CONV) << 4;        // fixdt(1,16,4)
    left.rtP.n_max                = nMotMaxL << 4;                       // fixdt(1,16,4)
    left.rtP.id_fieldWeakMax      = (fieldWeakMaxL * A2BIT_CONV) << 4;   // fixdt(1,16,4)
    left.rtP.a_phaAdvMax          = phaseAdvMaxL << 4;                   // fixdt(1,16,4)

    left.rtU.b_motEna     = enableLFin;
    left.rtU.z_ctrlModReq = left.actual.ctrlMod;
    left.rtU.r_inpTgt     = left.actual.pwm;
    left.rtU.b_hallA      = hall_ul;
    left.rtU.b_hallB      = hall_vl;
    left.rtU.b_hallC      = hall_wl;
    left.rtU.i_phaAB      = curL_phaA;
    left.rtU.i_phaBC      = curL_phaB;
    left.rtU.i_DCLink     = curL_DC;

    /* Step the controller */
    BLDC_controller_step(&left.rtM);

    /* Get motor outputs here */
    int ul            = left.rtY.DC_phaA;
    int vl            = left.rtY.DC_phaB;
    int wl            = left.rtY.DC_phaC;

    /* Apply commands */
    LEFT_TIM->LEFT_TIM_U    = (uint16_t)std::clamp(ul + pwm_res / 2, pwm_margin, pwm_res-pwm_margin);
    LEFT_TIM->LEFT_TIM_V    = (uint16_t)std::clamp(vl + pwm_res / 2, pwm_margin, pwm_res-pwm_margin);
    LEFT_TIM->LEFT_TIM_W    = (uint16_t)std::clamp(wl + pwm_res / 2, pwm_margin, pwm_res-pwm_margin);
  // =================================================================


  // ========================= RIGHT MOTOR ===========================
    // Get hall sensors values
    uint8_t hall_ur = !(RIGHT_HALL_U_PORT->IDR & RIGHT_HALL_U_PIN);
    uint8_t hall_vr = !(RIGHT_HALL_V_PORT->IDR & RIGHT_HALL_V_PIN);
    uint8_t hall_wr = !(RIGHT_HALL_W_PORT->IDR & RIGHT_HALL_W_PIN);

    /* Set motor inputs here */
    right.rtP.z_ctrlTypSel         = right.actual.ctrlTyp;
    right.rtP.i_max                = (iMotMaxR * A2BIT_CONV) << 4;        // fixdt(1,16,4)
    right.rtP.n_max                = nMotMaxR << 4;                       // fixdt(1,16,4)
    right.rtP.id_fieldWeakMax      = (fieldWeakMaxR * A2BIT_CONV) << 4;   // fixdt(1,16,4)
    right.rtP.a_phaAdvMax          = phaseAdvMaxR << 4;                   // fixdt(1,16,4)

    right.rtU.b_motEna      = enableRFin;
    right.rtU.z_ctrlModReq  = right.actual.ctrlMod;
    right.rtU.r_inpTgt      = right.actual.pwm;
    right.rtU.b_hallA       = hall_ur;
    right.rtU.b_hallB       = hall_vr;
    right.rtU.b_hallC       = hall_wr;
    right.rtU.i_phaAB       = curR_phaB;
    right.rtU.i_phaBC       = curR_phaC;
    right.rtU.i_DCLink      = curR_DC;

    /* Step the controller */
    BLDC_controller_step(&right.rtM);

    /* Get motor outputs here */
    int ur            = right.rtY.DC_phaA;
    int vr            = right.rtY.DC_phaB;
    int wr            = right.rtY.DC_phaC;

    /* Apply commands */
    RIGHT_TIM->RIGHT_TIM_U  = (uint16_t)std::clamp(ur + pwm_res / 2, pwm_margin, pwm_res-pwm_margin);
    RIGHT_TIM->RIGHT_TIM_V  = (uint16_t)std::clamp(vr + pwm_res / 2, pwm_margin, pwm_res-pwm_margin);
    RIGHT_TIM->RIGHT_TIM_W  = (uint16_t)std::clamp(wr + pwm_res / 2, pwm_margin, pwm_res-pwm_margin);
  // =================================================================

  /* Indicate task complete */
  OverrunFlag = false;
}

namespace {
// ===========================================================
  /* Low pass filter fixed-point 32 bits: fixdt(1,32,20)
  * Max:  2047.9375
  * Min: -2048
  * Res:  0.0625
  * 
  * Inputs:       u     = int16
  * Outputs:      y     = fixdt(1,32,20)
  * Parameters:   coef  = fixdt(0,16,16) = [0,65535U]
  * 
  * Example: 
  * If coef = 0.8 (in floating point), then coef = 0.8 * 2^16 = 52429 (in fixed-point)
  * filtLowPass16(u, 52429, &y);
  * yint = (int16_t)(y >> 20); // the integer output is the fixed-point ouput shifted by 20 bits
  */
void filtLowPass32(int16_t u, uint16_t coef, int32_t *y)
{
  int
          tmp;
  
  tmp = (int16_t)(u << 4) - (*y >> 16);  
  tmp = std::clamp(tmp, -32768, 32767);  // Overflow protection
  *y  = coef * tmp + (*y);
}

// ===========================================================
  /* rateLimiter16(int16_t u, int16_t rate, int16_t *y);
  * Inputs:       u     = int16
  * Outputs:      y     = fixdt(1,16,4)
  * Parameters:   rate  = fixdt(1,16,4) = [0, 32767] Do NOT make rate negative (>32767)
  */
void rateLimiter16(int16_t u, int16_t rate, int16_t *y)
{
  int16_t q0;
  int16_t q1;

  q0 = (u << 4)  - *y;

  if (q0 > rate) {
    q0 = rate;
  } else {
    q1 = -rate;
    if (q0 < q1) {
      q0 = q1;
    }
  }

  *y = q0 + *y;
}

// ===========================================================

/** System Clock Configuration
*/
void SystemClock_Config() {
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState            = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL          = RCC_PLL_MUL16;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_ClkInitStruct.ClockType           = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource        = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider       = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider      = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider      = RCC_HCLK_DIV1;

  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

  PeriphClkInit.PeriphClockSelection    = RCC_PERIPHCLK_ADC;
  // PeriphClkInit.AdcClockSelection    = RCC_ADCPCLK2_DIV8;  // 8 MHz
  PeriphClkInit.AdcClockSelection       = RCC_ADCPCLK2_DIV4;  // 16 MHz
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

  /**Configure the Systick interrupt time
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

  /**Configure the Systick
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void UART2_Init() {

  /* The code below is commented out - otwerwise Serial Receive does not work */
  // #ifdef CONTROL_SERIAL_USART2
  //   /* DMA1_Channel6_IRQn interrupt configuration */
  //   HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 5, 6);
  //   HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
  //   /* DMA1_Channel7_IRQn interrupt configuration */
  //   HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 5, 7);
  //   HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);
  // #endif

  // Disable serial interrupt - it is not needed
  HAL_NVIC_DisableIRQ(DMA1_Channel6_IRQn);    // Rx Channel
  HAL_NVIC_DisableIRQ(DMA1_Channel7_IRQn);    // Tx Channel

  __HAL_RCC_DMA1_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_USART2_CLK_ENABLE();

  huart2.Instance           = USART2;
  huart2.Init.BaudRate      = USART2_BAUD;
  huart2.Init.WordLength    = USART2_WORDLENGTH;
  huart2.Init.StopBits      = UART_STOPBITS_1;
  huart2.Init.Parity        = UART_PARITY_NONE;
  huart2.Init.HwFlowCtl     = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling  = UART_OVERSAMPLING_16;
  huart2.Init.Mode        = UART_MODE_TX_RX;
  HAL_UART_Init(&huart2);
  USART2->CR3 |= USART_CR3_DMAT;  // | USART_CR3_DMAR | USART_CR3_OVRDIS;

  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin       = GPIO_PIN_2;
  GPIO_InitStruct.Pull      = GPIO_PULLUP; //GPIO_NOPULL;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin     = GPIO_PIN_3;
    GPIO_InitStruct.Mode    = GPIO_MODE_INPUT; //GPIO_MODE_AF_PP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Peripheral DMA init*/
    hdma_usart2_rx.Instance                 = DMA1_Channel6;
    hdma_usart2_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    hdma_usart2_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
    hdma_usart2_rx.Init.MemInc              = DMA_MINC_ENABLE;
    hdma_usart2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
    hdma_usart2_rx.Init.Mode                = DMA_CIRCULAR; //DMA_NORMAL;
    hdma_usart2_rx.Init.Priority            = DMA_PRIORITY_LOW;
    HAL_DMA_Init(&hdma_usart2_rx);
    __HAL_LINKDMA(&huart2, hdmarx, hdma_usart2_rx);

  hdma_usart2_tx.Instance                   = DMA1_Channel7;
  hdma_usart2_tx.Init.Direction             = DMA_MEMORY_TO_PERIPH;
  hdma_usart2_tx.Init.PeriphInc             = DMA_PINC_DISABLE;
  hdma_usart2_tx.Init.MemInc                = DMA_MINC_ENABLE;
  hdma_usart2_tx.Init.PeriphDataAlignment   = DMA_PDATAALIGN_BYTE;
  hdma_usart2_tx.Init.MemDataAlignment      = DMA_MDATAALIGN_BYTE;
  hdma_usart2_tx.Init.Mode                  = DMA_NORMAL;
  hdma_usart2_tx.Init.Priority              = DMA_PRIORITY_LOW;
  HAL_DMA_Init(&hdma_usart2_tx);

    __HAL_LINKDMA(&huart2, hdmatx, hdma_usart2_tx);

    DMA1_Channel7->CPAR     = uint64_t(&(USART2->DR));
    DMA1_Channel7->CNDTR    = 0;
    DMA1->IFCR              = DMA_IFCR_CTCIF7 | DMA_IFCR_CHTIF7 | DMA_IFCR_CGIF7;
}

//void UART3_Init() {

//  /* The code below is commented out - otwerwise Serial Receive does not work */
//  // #ifdef CONTROL_SERIAL_USART3
//  //   /* DMA1_Channel3_IRQn interrupt configuration */
//  //   HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 5, 3);
//  //   HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
//  //   /* DMA1_Channel2_IRQn interrupt configuration */
//  //   HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 5, 2);
//  //   HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
//  // #endif

//  // Disable serial interrupt - it is not needed
//  HAL_NVIC_DisableIRQ(DMA1_Channel3_IRQn);  // Rx Channel
//  HAL_NVIC_DisableIRQ(DMA1_Channel2_IRQn);  // Tx Channel

//  __HAL_RCC_DMA1_CLK_ENABLE();
//  __HAL_RCC_GPIOB_CLK_ENABLE();
//  __HAL_RCC_USART3_CLK_ENABLE();

//  huart3.Instance             = USART3;
//  huart3.Init.BaudRate        = USART3_BAUD;
//  huart3.Init.WordLength      = USART3_WORDLENGTH;
//  huart3.Init.StopBits        = UART_STOPBITS_1;
//  huart3.Init.Parity          = UART_PARITY_NONE;
//  huart3.Init.HwFlowCtl       = UART_HWCONTROL_NONE;
//  huart3.Init.OverSampling    = UART_OVERSAMPLING_16;
//  #if defined(CONTROL_SERIAL_USART3)
//    huart3.Init.Mode          = UART_MODE_TX_RX;
//  #elif defined(DEBUG_SERIAL_USART3)
//    huart3.Init.Mode          = UART_MODE_TX;
//  #endif
//  HAL_UART_Init(&huart3);

//  #if defined(FEEDBACK_SERIAL_USART3) || defined(DEBUG_SERIAL_USART3)
//    USART3->CR3 |= USART_CR3_DMAT;  // | USART_CR3_DMAR | USART_CR3_OVRDIS;
//  #endif

//  GPIO_InitTypeDef GPIO_InitStruct;
//  GPIO_InitStruct.Pin         = GPIO_PIN_10;
//  GPIO_InitStruct.Pull        = GPIO_PULLUP;
//  GPIO_InitStruct.Mode        = GPIO_MODE_AF_PP;
//  GPIO_InitStruct.Speed       = GPIO_SPEED_FREQ_HIGH;
//  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//  #ifdef CONTROL_SERIAL_USART3
//    GPIO_InitStruct.Pin       = GPIO_PIN_11;
//    GPIO_InitStruct.Mode      = GPIO_MODE_INPUT;
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//    /* Peripheral DMA init*/
//    hdma_usart3_rx.Instance                   = DMA1_Channel3;
//    hdma_usart3_rx.Init.Direction             = DMA_PERIPH_TO_MEMORY;
//    hdma_usart3_rx.Init.PeriphInc             = DMA_PINC_DISABLE;
//    hdma_usart3_rx.Init.MemInc                = DMA_MINC_ENABLE;
//    hdma_usart3_rx.Init.PeriphDataAlignment   = DMA_PDATAALIGN_BYTE;
//    hdma_usart3_rx.Init.MemDataAlignment      = DMA_MDATAALIGN_BYTE;
//    hdma_usart3_rx.Init.Mode                  = DMA_CIRCULAR; //DMA_NORMAL;
//    hdma_usart3_rx.Init.Priority              = DMA_PRIORITY_LOW;
//    HAL_DMA_Init(&hdma_usart3_rx);
//    __HAL_LINKDMA(&huart3, hdmarx, hdma_usart3_rx);
//  #endif

//  hdma_usart3_tx.Instance                     = DMA1_Channel2;
//  hdma_usart3_tx.Init.Direction               = DMA_MEMORY_TO_PERIPH;
//  hdma_usart3_tx.Init.PeriphInc               = DMA_PINC_DISABLE;
//  hdma_usart3_tx.Init.MemInc                  = DMA_MINC_ENABLE;
//  hdma_usart3_tx.Init.PeriphDataAlignment     = DMA_PDATAALIGN_BYTE;
//  hdma_usart3_tx.Init.MemDataAlignment        = DMA_MDATAALIGN_BYTE;
//  hdma_usart3_tx.Init.Mode                    = DMA_NORMAL;
//  hdma_usart3_tx.Init.Priority                = DMA_PRIORITY_LOW;
//  HAL_DMA_Init(&hdma_usart3_tx);

//  #ifdef CONTROL_SERIAL_USART3
//    __HAL_LINKDMA(&huart3, hdmatx, hdma_usart3_tx);
//  #endif
//  #if defined(FEEDBACK_SERIAL_USART3) || defined(DEBUG_SERIAL_USART3)
//    DMA1_Channel2->CPAR     = (uint32_t) & (USART3->DR);
//    DMA1_Channel2->CNDTR    = 0;
//    DMA1->IFCR              = DMA_IFCR_CTCIF2 | DMA_IFCR_CHTIF2 | DMA_IFCR_CGIF2;
//  #endif
//}

void MX_GPIO_Init() {
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  GPIO_InitStruct.Pin = LEFT_HALL_U_PIN;
  HAL_GPIO_Init(LEFT_HALL_U_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LEFT_HALL_V_PIN;
  HAL_GPIO_Init(LEFT_HALL_V_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LEFT_HALL_W_PIN;
  HAL_GPIO_Init(LEFT_HALL_W_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = RIGHT_HALL_U_PIN;
  HAL_GPIO_Init(RIGHT_HALL_U_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = RIGHT_HALL_V_PIN;
  HAL_GPIO_Init(RIGHT_HALL_V_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = RIGHT_HALL_W_PIN;
  HAL_GPIO_Init(RIGHT_HALL_W_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = CHARGER_PIN;
  HAL_GPIO_Init(CHARGER_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = BUTTON_PIN;
  HAL_GPIO_Init(BUTTON_PORT, &GPIO_InitStruct);


  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;

  GPIO_InitStruct.Pin = LED_PIN;
  HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = BUZZER_PIN;
  HAL_GPIO_Init(BUZZER_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = OFF_PIN;
  HAL_GPIO_Init(OFF_PORT, &GPIO_InitStruct);


  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;

  GPIO_InitStruct.Pin = LEFT_DC_CUR_PIN;
  HAL_GPIO_Init(LEFT_DC_CUR_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LEFT_U_CUR_PIN;
  HAL_GPIO_Init(LEFT_U_CUR_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LEFT_V_CUR_PIN;
  HAL_GPIO_Init(LEFT_V_CUR_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = RIGHT_DC_CUR_PIN;
  HAL_GPIO_Init(RIGHT_DC_CUR_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = RIGHT_U_CUR_PIN;
  HAL_GPIO_Init(RIGHT_U_CUR_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = RIGHT_V_CUR_PIN;
  HAL_GPIO_Init(RIGHT_V_CUR_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = DCLINK_PIN;
  HAL_GPIO_Init(DCLINK_PORT, &GPIO_InitStruct);

  //Analog in
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;

  GPIO_InitStruct.Pin = LEFT_TIM_UH_PIN;
  HAL_GPIO_Init(LEFT_TIM_UH_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LEFT_TIM_VH_PIN;
  HAL_GPIO_Init(LEFT_TIM_VH_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LEFT_TIM_WH_PIN;
  HAL_GPIO_Init(LEFT_TIM_WH_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LEFT_TIM_UL_PIN;
  HAL_GPIO_Init(LEFT_TIM_UL_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LEFT_TIM_VL_PIN;
  HAL_GPIO_Init(LEFT_TIM_VL_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LEFT_TIM_WL_PIN;
  HAL_GPIO_Init(LEFT_TIM_WL_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = RIGHT_TIM_UH_PIN;
  HAL_GPIO_Init(RIGHT_TIM_UH_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = RIGHT_TIM_VH_PIN;
  HAL_GPIO_Init(RIGHT_TIM_VH_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = RIGHT_TIM_WH_PIN;
  HAL_GPIO_Init(RIGHT_TIM_WH_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = RIGHT_TIM_UL_PIN;
  HAL_GPIO_Init(RIGHT_TIM_UL_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = RIGHT_TIM_VL_PIN;
  HAL_GPIO_Init(RIGHT_TIM_VL_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = RIGHT_TIM_WL_PIN;
  HAL_GPIO_Init(RIGHT_TIM_WL_PORT, &GPIO_InitStruct);
}

void MX_TIM_Init() {
  __HAL_RCC_TIM1_CLK_ENABLE();
  __HAL_RCC_TIM8_CLK_ENABLE();

  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;
  TIM_SlaveConfigTypeDef sTimConfig;

  htim_right.Instance               = RIGHT_TIM;
  htim_right.Init.Prescaler         = 0;
  htim_right.Init.CounterMode       = TIM_COUNTERMODE_CENTERALIGNED1;
  htim_right.Init.Period            = 64000000 / 2 / PWM_FREQ;
  htim_right.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
  htim_right.Init.RepetitionCounter = 0;
  htim_right.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  HAL_TIM_PWM_Init(&htim_right);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_ENABLE;
  sMasterConfig.MasterSlaveMode     = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim_right, &sMasterConfig);

  sConfigOC.OCMode       = TIM_OCMODE_PWM1;
  sConfigOC.Pulse        = 0;
  sConfigOC.OCPolarity   = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity  = TIM_OCNPOLARITY_LOW;
  sConfigOC.OCFastMode   = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState  = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_SET;
  HAL_TIM_PWM_ConfigChannel(&htim_right, &sConfigOC, TIM_CHANNEL_1);
  HAL_TIM_PWM_ConfigChannel(&htim_right, &sConfigOC, TIM_CHANNEL_2);
  HAL_TIM_PWM_ConfigChannel(&htim_right, &sConfigOC, TIM_CHANNEL_3);

  sBreakDeadTimeConfig.OffStateRunMode  = TIM_OSSR_ENABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_ENABLE;
  sBreakDeadTimeConfig.LockLevel        = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime         = DEAD_TIME;
  sBreakDeadTimeConfig.BreakState       = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity    = TIM_BREAKPOLARITY_LOW;
  sBreakDeadTimeConfig.AutomaticOutput  = TIM_AUTOMATICOUTPUT_DISABLE;
  HAL_TIMEx_ConfigBreakDeadTime(&htim_right, &sBreakDeadTimeConfig);

  htim_left.Instance               = LEFT_TIM;
  htim_left.Init.Prescaler         = 0;
  htim_left.Init.CounterMode       = TIM_COUNTERMODE_CENTERALIGNED1;
  htim_left.Init.Period            = 64000000 / 2 / PWM_FREQ;
  htim_left.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
  htim_left.Init.RepetitionCounter = 0;
  htim_left.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  HAL_TIM_PWM_Init(&htim_left);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode     = TIM_MASTERSLAVEMODE_ENABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim_left, &sMasterConfig);

  sTimConfig.InputTrigger = TIM_TS_ITR0;
  sTimConfig.SlaveMode    = TIM_SLAVEMODE_GATED;
  HAL_TIM_SlaveConfigSynchronization(&htim_left, &sTimConfig);

  // Start counting >0 to effectively offset timers by the time it takes for one ADC conversion to complete.
  // This method allows that the Phase currents ADC measurements are properly aligned with LOW-FET ON region for both motors
  LEFT_TIM->CNT 		     = ADC_TOTAL_CONV_TIME;

  sConfigOC.OCMode       = TIM_OCMODE_PWM1;
  sConfigOC.Pulse        = 0;
  sConfigOC.OCPolarity   = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity  = TIM_OCNPOLARITY_LOW;
  sConfigOC.OCFastMode   = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState  = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_SET;
  HAL_TIM_PWM_ConfigChannel(&htim_left, &sConfigOC, TIM_CHANNEL_1);
  HAL_TIM_PWM_ConfigChannel(&htim_left, &sConfigOC, TIM_CHANNEL_2);
  HAL_TIM_PWM_ConfigChannel(&htim_left, &sConfigOC, TIM_CHANNEL_3);

  sBreakDeadTimeConfig.OffStateRunMode  = TIM_OSSR_ENABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_ENABLE;
  sBreakDeadTimeConfig.LockLevel        = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime         = DEAD_TIME;
  sBreakDeadTimeConfig.BreakState       = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity    = TIM_BREAKPOLARITY_LOW;
  sBreakDeadTimeConfig.AutomaticOutput  = TIM_AUTOMATICOUTPUT_DISABLE;
  HAL_TIMEx_ConfigBreakDeadTime(&htim_left, &sBreakDeadTimeConfig);

  LEFT_TIM->BDTR &= ~TIM_BDTR_MOE;
  RIGHT_TIM->BDTR &= ~TIM_BDTR_MOE;

  HAL_TIM_PWM_Start(&htim_left, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim_left, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim_left, TIM_CHANNEL_3);
  HAL_TIMEx_PWMN_Start(&htim_left, TIM_CHANNEL_1);
  HAL_TIMEx_PWMN_Start(&htim_left, TIM_CHANNEL_2);
  HAL_TIMEx_PWMN_Start(&htim_left, TIM_CHANNEL_3);

  HAL_TIM_PWM_Start(&htim_right, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim_right, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim_right, TIM_CHANNEL_3);
  HAL_TIMEx_PWMN_Start(&htim_right, TIM_CHANNEL_1);
  HAL_TIMEx_PWMN_Start(&htim_right, TIM_CHANNEL_2);
  HAL_TIMEx_PWMN_Start(&htim_right, TIM_CHANNEL_3);

  htim_left.Instance->RCR = 1;

  __HAL_TIM_ENABLE(&htim_right);
}

void MX_ADC1_Init() {
  ADC_MultiModeTypeDef multimode;
  ADC_ChannelConfTypeDef sConfig;

  __HAL_RCC_ADC1_CLK_ENABLE();

  hadc1.Instance                   = ADC1;
  hadc1.Init.ScanConvMode          = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode    = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T8_TRGO;
  hadc1.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion       = 5;
  HAL_ADC_Init(&hadc1);
  /**Enable or disable the remapping of ADC1_ETRGREG:
    * ADC1 External Event regular conversion is connected to TIM8 TRG0
    */
  __HAL_AFIO_REMAP_ADC1_ETRGREG_ENABLE();

  /**Configure the ADC multi-mode
    */
  multimode.Mode = ADC_DUALMODE_REGSIMULT;
  HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode);

  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.Channel = ADC_CHANNEL_11;  // pc1 left cur  ->  right
  sConfig.Rank    = 1;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

  // sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;
  sConfig.Channel = ADC_CHANNEL_0;  // pa0 right a   ->  left
  sConfig.Rank    = 2;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

  sConfig.Channel = ADC_CHANNEL_14;  // pc4 left b   -> right
  sConfig.Rank    = 3;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

  sConfig.Channel = ADC_CHANNEL_12;  // pc2 vbat
  sConfig.Rank    = 4;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

  //temperature requires at least 17.1uS sampling time
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;  // internal temp
  sConfig.Rank    = 5;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

  hadc1.Instance->CR2 |= ADC_CR2_DMA | ADC_CR2_TSVREFE;

  __HAL_ADC_ENABLE(&hadc1);

  __HAL_RCC_DMA1_CLK_ENABLE();

  DMA1_Channel1->CCR   = 0;
  DMA1_Channel1->CNDTR = 5;
  DMA1_Channel1->CPAR  = uint64_t(&(ADC1->DR));
  DMA1_Channel1->CMAR  = uint64_t(&adc_buffer);
  DMA1_Channel1->CCR   = DMA_CCR_MSIZE_1 | DMA_CCR_PSIZE_1 | DMA_CCR_MINC | DMA_CCR_CIRC | DMA_CCR_TCIE;
  DMA1_Channel1->CCR |= DMA_CCR_EN;

  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

/* ADC2 init function */
void MX_ADC2_Init() {
  ADC_ChannelConfTypeDef sConfig;

  __HAL_RCC_ADC2_CLK_ENABLE();

  // HAL_ADC_DeInit(&hadc2);
  // hadc2.Instance->CR2 = 0;
  /**Common config
    */
  hadc2.Instance                   = ADC2;
  hadc2.Init.ScanConvMode          = ADC_SCAN_ENABLE;
  hadc2.Init.ContinuousConvMode    = DISABLE;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConv      = ADC_SOFTWARE_START;
  hadc2.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
  hadc2.Init.NbrOfConversion       = 5;
  HAL_ADC_Init(&hadc2);


  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.Channel = ADC_CHANNEL_10;  // pc0 right cur   -> left
  sConfig.Rank    = 1;
  HAL_ADC_ConfigChannel(&hadc2, &sConfig);

  // sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;
  sConfig.Channel = ADC_CHANNEL_13;  // pc3 right b   -> left
  sConfig.Rank    = 2;
  HAL_ADC_ConfigChannel(&hadc2, &sConfig);

  sConfig.Channel = ADC_CHANNEL_15;  // pc5 left c   -> right
  sConfig.Rank    = 3;
  HAL_ADC_ConfigChannel(&hadc2, &sConfig);

  sConfig.Channel = ADC_CHANNEL_2;  // pa2 uart-l-tx
  sConfig.Rank    = 4;
  HAL_ADC_ConfigChannel(&hadc2, &sConfig);

  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  sConfig.Channel = ADC_CHANNEL_3;  // pa3 uart-l-rx
  sConfig.Rank    = 5;
  HAL_ADC_ConfigChannel(&hadc2, &sConfig);

  hadc2.Instance->CR2 |= ADC_CR2_DMA;
  __HAL_ADC_ENABLE(&hadc2);
}

void poweroff() {
  //  if (abs(speed) < 20) {  // wait for the speed to drop, then shut down -> this is commented out for SAFETY reasons
        buzzerPattern = 0;
        left.actual.enable = right.actual.enable = 0;
        for (int i = 0; i < 8; i++) {
            buzzerFreq = (uint8_t)i;
            HAL_Delay(100);
        }
        HAL_GPIO_WritePin(OFF_PORT, OFF_PIN, GPIO_PIN_RESET);
        for (int i = 0; i < 5; i++)
            HAL_Delay(1000);
  //  }
}

} // anonymous namespace
