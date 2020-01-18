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

#include <stdlib.h> // for abs()
#include "BLDC_controller.h"
#include "stm32f1xx_hal.h"
#include "defines.h"
#include "setup.h"
#include "config.h"
#include "comms.h"
#include "eeprom.h"

void MX_GPIO_Init(void);
void UART2_Init(void);
void MX_TIM_Init(void);
void MX_ADC1_Init(void);
void MX_ADC2_Init(void);

TIM_HandleTypeDef htim_right;
TIM_HandleTypeDef htim_left;
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
static UART_HandleTypeDef huart;

DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;
DMA_HandleTypeDef hdma_usart3_rx;
DMA_HandleTypeDef hdma_usart3_tx;
volatile adc_buf_t adc_buffer;

// ###############################################################################

static int16_t pwm_margin = 100;        /* This margin allows to always have a window in the PWM signal for proper Phase currents measurement */

volatile uint32_t timeout;

uint8_t buzzerFreq          = 0;
uint8_t buzzerFreqReq       = 0;
uint8_t buzzerPattern       = 0;
uint8_t buzzerPatternReq    = 0;

static uint32_t buzzerTimer = 0;

static const uint16_t pwm_res  = 64000000 / 2 / PWM_FREQ; // = 2000

static uint16_t offsetcount = 0;
static int16_t offsetrl1    = 2000;
static int16_t offsetrl2    = 2000;
static int16_t offsetrr1    = 2000;
static int16_t offsetrr2    = 2000;
static int16_t offsetdcl    = 2000;
static int16_t offsetdcr    = 2000;

int16_t        batVoltage       = (400 * BAT_CELLS * BAT_CALIB_ADC) / BAT_CALIB_REAL_VOLTAGE;
static int32_t batVoltageFixdt  = (400 * BAT_CELLS * BAT_CALIB_ADC) / BAT_CALIB_REAL_VOLTAGE << 20;  // Fixed-point filter output initialized at 400 V*100/cell = 4 V/cell converted to fixed-point

// Matlab includes and defines - from auto-code generation
// ###############################################################################
#include "BLDC_controller.h"      /* Model's header file */
#include "rtwtypes.h"

RT_MODEL rtM_Left_;               /* Real-time model */
RT_MODEL rtM_Right_;              /* Real-time model */
RT_MODEL *const rtM_Left    = &rtM_Left_;
RT_MODEL *const rtM_Right   = &rtM_Right_;

extern P rtP_Left;                /* Block parameters (auto storage) */
DW    rtDW_Left;                  /* Observable states */
ExtU  rtU_Left;                   /* External inputs */
ExtY  rtY_Left;                   /* External outputs */

P     rtP_Right;                  /* Block parameters (auto storage) */
DW    rtDW_Right;                 /* Observable states */
ExtU  rtU_Right;                  /* External inputs */
ExtY  rtY_Right;                  /* External outputs */

// ###############################################################################

void SystemClock_Config(void);
void poweroff(void);

#if defined(CONTROL_SERIAL_USART2) || defined(CONTROL_SERIAL_USART3)
typedef struct{
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
} Serialcommand;
static volatile Serialcommand command;
static int16_t timeoutCntSerial   = 0;  // Timeout counter for Rx Serial command
#endif
static uint8_t timeoutFlagSerial  = 0;  // Timeout Flag for Rx Serial command: 0 = OK, 1 = Problem detected (line disconnected or wrong Rx data)

uint8_t        enableL       = 0;        // initially motors are disabled for SAFETY
uint8_t        enableLReq    = 0;
uint8_t        enableR       = 0;        // initially motors are disabled for SAFETY
uint8_t        enableRReq    = 0;

int pwmLReq = 0;
volatile int pwmL = 0;
int pwmRReq = 0;
volatile int pwmR = 0;

uint8_t ctrlTypLReq = CTRL_TYP_SEL;
volatile uint8_t ctrlTypL    = CTRL_TYP_SEL;   // Final control mode request
uint8_t ctrlTypRReq = CTRL_TYP_SEL;
volatile uint8_t ctrlTypR    = CTRL_TYP_SEL;   // Final control mode request

uint8_t ctrlModLReq = CTRL_MOD_REQ;
volatile uint8_t ctrlModL    = CTRL_MOD_REQ;   // Final control mode request
uint8_t ctrlModRReq = CTRL_MOD_REQ;
volatile uint8_t ctrlModR    = CTRL_MOD_REQ;   // Final control mode request

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

static uint32_t inactivity_timeout_counter;
static uint32_t main_loop_counter;

void poweroff(void) {
  //  if (abs(speed) < 20) {  // wait for the speed to drop, then shut down -> this is commented out for SAFETY reasons
        buzzerPattern = 0;
        enableL = enableR = 0;
        for (int i = 0; i < 8; i++) {
            buzzerFreq = (uint8_t)i;
            HAL_Delay(100);
        }
        HAL_GPIO_WritePin(OFF_PORT, OFF_PIN, GPIO_PIN_RESET);
        while(1) {}
  //  }
}


int main(void) {

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
  rtP_Left.b_selPhaABCurrMeas   = 1;            // Left motor measured current phases = {iA, iB} -> do NOT change
  rtP_Left.z_ctrlTypSel         = ctrlTypL;
  rtP_Left.b_diagEna            = DIAG_ENA; 
  rtP_Left.i_max                = (iMotMaxL * A2BIT_CONV) << 4;        // fixdt(1,16,4)
  rtP_Left.n_max                = nMotMaxL << 4;                       // fixdt(1,16,4)
  rtP_Left.b_fieldWeakEna       = FIELD_WEAK_ENA; 
  rtP_Left.id_fieldWeakMax      = (fieldWeakMaxL * A2BIT_CONV) << 4;   // fixdt(1,16,4)
  rtP_Left.a_phaAdvMax          = phaseAdvMaxL << 4;                   // fixdt(1,16,4)
  rtP_Left.r_fieldWeakHi        = FIELD_WEAK_HI << 4;                   // fixdt(1,16,4)
  rtP_Left.r_fieldWeakLo        = FIELD_WEAK_LO << 4;                   // fixdt(1,16,4)

  rtP_Right                     = rtP_Left;     // Copy the Left motor parameters to the Right motor parameters
  rtP_Right.b_selPhaABCurrMeas  = 0;            // Left motor measured current phases = {iB, iC} -> do NOT change
  rtP_Left.z_ctrlTypSel         = ctrlTypR;
  rtP_Left.b_diagEna            = DIAG_ENA;
  rtP_Left.i_max                = (iMotMaxR * A2BIT_CONV) << 4;        // fixdt(1,16,4)
  rtP_Left.n_max                = nMotMaxR << 4;                       // fixdt(1,16,4)
  rtP_Left.b_fieldWeakEna       = FIELD_WEAK_ENA;
  rtP_Left.id_fieldWeakMax      = (fieldWeakMaxR * A2BIT_CONV) << 4;   // fixdt(1,16,4)
  rtP_Left.a_phaAdvMax          = phaseAdvMaxR << 4;                   // fixdt(1,16,4)
  rtP_Left.r_fieldWeakHi        = FIELD_WEAK_HI << 4;                   // fixdt(1,16,4)
  rtP_Left.r_fieldWeakLo        = FIELD_WEAK_LO << 4;                   // fixdt(1,16,4)

  /* Pack LEFT motor data into RTM */
  rtM_Left->defaultParam        = &rtP_Left;
  rtM_Left->dwork               = &rtDW_Left;
  rtM_Left->inputs              = &rtU_Left;
  rtM_Left->outputs             = &rtY_Left;

  /* Pack RIGHT motor data into RTM */
  rtM_Right->defaultParam       = &rtP_Right;
  rtM_Right->dwork              = &rtDW_Right;
  rtM_Right->inputs             = &rtU_Right;
  rtM_Right->outputs            = &rtY_Right;

  /* Initialize BLDC controllers */
  BLDC_controller_initialize(rtM_Left);
  BLDC_controller_initialize(rtM_Right);

// ###############################################################################

  for (int i = 8; i >= 0; i--) {
    buzzerFreq = (uint8_t)i;
    HAL_Delay(100);
  }
  buzzerFreq = 0;

  HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);

  #if defined(CONTROL_SERIAL_USART2) || defined(FEEDBACK_SERIAL_USART2) || defined(DEBUG_SERIAL_USART2)
    UART2_Init();
    huart = huart2;
  #endif
  #if defined(CONTROL_SERIAL_USART3) || defined(FEEDBACK_SERIAL_USART3) || defined(DEBUG_SERIAL_USART3)
    UART3_Init();
    huart = huart3;
  #endif
  #if defined(CONTROL_SERIAL_USART2) || defined(CONTROL_SERIAL_USART3)
    HAL_UART_Receive_DMA(&huart, (uint8_t *)&command, sizeof(command));
  #endif

  int32_t board_temp_adcFixdt = adc_buffer.temp << 20;  // Fixed-point filter output initialized with current ADC converted to fixed-point
  int16_t board_temp_adcFilt  = adc_buffer.temp;
  int16_t board_temp_deg_c;

  while(1) {
    HAL_Delay(DELAY_IN_MAIN_LOOP); //delay in ms

    #if defined CONTROL_SERIAL_USART2 || defined CONTROL_SERIAL_USART3

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
            enableLReq = command.enableL;
            enableRReq = command.enableR;

            pwmLReq = command.pwmL;
            pwmRReq = command.pwmR;

            ctrlTypLReq = command.ctrlTypL;
            ctrlTypRReq = command.ctrlTypR;

            ctrlModLReq = command.ctrlModL;
            ctrlModRReq = command.ctrlModR;

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
            HAL_UART_DMAStop(&huart);
            HAL_UART_Receive_DMA(&huart, (uint8_t *)&command, sizeof(command));
        }
    }

    if (timeoutFlagSerial)
    {
        enableL = 1;
        enableR = 1;

        pwmL = 0;
        pwmR = 0;

        ctrlTypL = 2;
        ctrlTypR = 2;

        ctrlModL  = 0;                                // OPEN_MODE request. This will bring the motor power to 0 in a controlled way
        ctrlModR  = 0;                                // OPEN_MODE request. This will bring the motor power to 0 in a controlled way

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
        enableL = enableLReq;
        enableR = enableRReq;

        pwmL = pwmLReq;
        pwmR = pwmRReq;

        ctrlTypL = ctrlTypLReq;
        ctrlTypR = ctrlTypRReq;

        ctrlModL  = ctrlModLReq;
        ctrlModR  = ctrlModRReq;

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

    #endif

    // ####### CALC BOARD TEMPERATURE #######
    filtLowPass32(adc_buffer.temp, TEMP_FILT_COEF, &board_temp_adcFixdt);
    board_temp_adcFilt  = (int16_t)(board_temp_adcFixdt >> 20);  // convert fixed-point to integer
    board_temp_deg_c    = (TEMP_CAL_HIGH_DEG_C - TEMP_CAL_LOW_DEG_C) * (board_temp_adcFilt - TEMP_CAL_LOW_ADC) / (TEMP_CAL_HIGH_ADC - TEMP_CAL_LOW_ADC) + TEMP_CAL_LOW_DEG_C;

    if (main_loop_counter % 25 == 0) {    // Send data periodically

      #if defined(FEEDBACK_SERIAL_USART2) || defined(FEEDBACK_SERIAL_USART3)
        if(UART_DMA_CHANNEL->CNDTR == 0) {
          // TODO send feedback
        }
      #endif      
    }    

    HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
    // ####### POWEROFF BY POWER-BUTTON #######
    if (HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN)) {
      enableL = enableR = 0;                                             // disable motors
      while (HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN)) {}    // wait until button is released
      if(__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST)) {               // do not power off after software reset (from a programmer/debugger)
        __HAL_RCC_CLEAR_RESET_FLAGS();                        // clear reset flags
      } else {
        poweroff();                                           // release power-latch
      }
    }


    // ####### INACTIVITY TIMEOUT #######
    if (abs(pwmL) > 25 || abs(pwmR) > 50) {
      inactivity_timeout_counter = 0;
    } else {
      inactivity_timeout_counter ++;
    }
    if (inactivity_timeout_counter > (INACTIVITY_TIMEOUT * 60 * 1000) / (DELAY_IN_MAIN_LOOP + 1)) {  // rest of main loop needs maybe 1ms
      poweroff();
    }

    main_loop_counter++;
    timeout++;
  }
}

#ifdef VARIANT_TRANSPOTTER
  void saveConfig() {
    HAL_FLASH_Unlock();
    EE_WriteVariable(VirtAddVarTab[0], saveValue);
    HAL_FLASH_Lock();
  }
#endif

void longBeep(uint8_t freq){
    buzzerFreq = freq;
    HAL_Delay(500);
    buzzerFreq = 0;
}

void shortBeep(uint8_t freq){
    buzzerFreq = freq;
    HAL_Delay(100);
    buzzerFreq = 0;
}

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
  int32_t tmp;
  
  tmp = (int16_t)(u << 4) - (*y >> 16);  
  tmp = CLAMP(tmp, -32768, 32767);  // Overflow protection  
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
void SystemClock_Config(void) {
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


// =================================
// DMA interrupt frequency =~ 16 kHz
// =================================
void DMA1_Channel1_IRQHandler(void) {

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

  // Disable PWM when current limit is reached (current chopping)
  // This is the Level 2 of current protection. The Level 1 should kick in first given by I_MOT_MAX
  if(ABS(curL_DC) > (iDcMaxL * A2BIT_CONV) || timeout > TIMEOUT || enableL == 0) {
    LEFT_TIM->BDTR &= ~TIM_BDTR_MOE;
  } else {
    LEFT_TIM->BDTR |= TIM_BDTR_MOE;
  }

  if(ABS(curR_DC)  > (iDcMaxR * A2BIT_CONV) || timeout > TIMEOUT || enableR == 0) {
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
      HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, 0);
  }

  // ############################### MOTOR CONTROL ###############################

  static boolean_T OverrunFlag = false;

  /* Check for overrun */
  if (OverrunFlag) {
    return;
  }
  OverrunFlag = true;

  /* Make sure to stop BOTH motors in case of an error */
  int8_t enableLFin = enableL && !rtY_Left.z_errCode && !rtY_Right.z_errCode;
  int8_t enableRFin = enableR && !rtY_Left.z_errCode && !rtY_Right.z_errCode;

  // ========================= LEFT MOTOR ============================
    // Get hall sensors values
    uint8_t hall_ul = !(LEFT_HALL_U_PORT->IDR & LEFT_HALL_U_PIN);
    uint8_t hall_vl = !(LEFT_HALL_V_PORT->IDR & LEFT_HALL_V_PIN);
    uint8_t hall_wl = !(LEFT_HALL_W_PORT->IDR & LEFT_HALL_W_PIN);

    /* Set motor inputs here */
    rtP_Left.z_ctrlTypSel         = ctrlTypL;
    rtP_Left.i_max                = (iMotMaxL * A2BIT_CONV) << 4;        // fixdt(1,16,4)
    rtP_Left.n_max                = nMotMaxL << 4;                       // fixdt(1,16,4)
    rtP_Left.id_fieldWeakMax      = (fieldWeakMaxL * A2BIT_CONV) << 4;   // fixdt(1,16,4)
    rtP_Left.a_phaAdvMax          = phaseAdvMaxL << 4;                   // fixdt(1,16,4)

    rtU_Left.b_motEna     = enableLFin;
    rtU_Left.z_ctrlModReq = ctrlModL;
    rtU_Left.r_inpTgt     = pwmL;
    rtU_Left.b_hallA      = hall_ul;
    rtU_Left.b_hallB      = hall_vl;
    rtU_Left.b_hallC      = hall_wl;
    rtU_Left.i_phaAB      = curL_phaA;
    rtU_Left.i_phaBC      = curL_phaB;
    rtU_Left.i_DCLink     = curL_DC;

    /* Step the controller */
    BLDC_controller_step(rtM_Left);

    /* Get motor outputs here */
    int ul            = rtY_Left.DC_phaA;
    int vl            = rtY_Left.DC_phaB;
    int wl            = rtY_Left.DC_phaC;

    /* Apply commands */
    LEFT_TIM->LEFT_TIM_U    = (uint16_t)CLAMP(ul + pwm_res / 2, pwm_margin, pwm_res-pwm_margin);
    LEFT_TIM->LEFT_TIM_V    = (uint16_t)CLAMP(vl + pwm_res / 2, pwm_margin, pwm_res-pwm_margin);
    LEFT_TIM->LEFT_TIM_W    = (uint16_t)CLAMP(wl + pwm_res / 2, pwm_margin, pwm_res-pwm_margin);
  // =================================================================


  // ========================= RIGHT MOTOR ===========================
    // Get hall sensors values
    uint8_t hall_ur = !(RIGHT_HALL_U_PORT->IDR & RIGHT_HALL_U_PIN);
    uint8_t hall_vr = !(RIGHT_HALL_V_PORT->IDR & RIGHT_HALL_V_PIN);
    uint8_t hall_wr = !(RIGHT_HALL_W_PORT->IDR & RIGHT_HALL_W_PIN);

    /* Set motor inputs here */
    rtP_Left.z_ctrlTypSel         = ctrlTypR;
    rtP_Left.i_max                = (iMotMaxR * A2BIT_CONV) << 4;        // fixdt(1,16,4)
    rtP_Left.n_max                = nMotMaxR << 4;                       // fixdt(1,16,4)
    rtP_Left.id_fieldWeakMax      = (fieldWeakMaxR * A2BIT_CONV) << 4;   // fixdt(1,16,4)
    rtP_Left.a_phaAdvMax          = phaseAdvMaxR << 4;                   // fixdt(1,16,4)

    rtU_Right.b_motEna      = enableRFin;
    rtU_Right.z_ctrlModReq  = ctrlModR;
    rtU_Right.r_inpTgt      = pwmR;
    rtU_Right.b_hallA       = hall_ur;
    rtU_Right.b_hallB       = hall_vr;
    rtU_Right.b_hallC       = hall_wr;
    rtU_Right.i_phaAB       = curR_phaB;
    rtU_Right.i_phaBC       = curR_phaC;
    rtU_Right.i_DCLink      = curR_DC;

    /* Step the controller */
    BLDC_controller_step(rtM_Right);

    /* Get motor outputs here */
    int ur            = rtY_Right.DC_phaA;
    int vr            = rtY_Right.DC_phaB;
    int wr            = rtY_Right.DC_phaC;

    /* Apply commands */
    RIGHT_TIM->RIGHT_TIM_U  = (uint16_t)CLAMP(ur + pwm_res / 2, pwm_margin, pwm_res-pwm_margin);
    RIGHT_TIM->RIGHT_TIM_V  = (uint16_t)CLAMP(vr + pwm_res / 2, pwm_margin, pwm_res-pwm_margin);
    RIGHT_TIM->RIGHT_TIM_W  = (uint16_t)CLAMP(wr + pwm_res / 2, pwm_margin, pwm_res-pwm_margin);
  // =================================================================

  /* Indicate task complete */
  OverrunFlag = false;

 // ###############################################################################

}


#if defined(CONTROL_SERIAL_USART2) || defined(FEEDBACK_SERIAL_USART2) || defined(DEBUG_SERIAL_USART2)
void UART2_Init(void) {

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
  #if defined(CONTROL_SERIAL_USART2)
    huart2.Init.Mode        = UART_MODE_TX_RX;
  #elif defined(DEBUG_SERIAL_USART2)
    huart2.Init.Mode        = UART_MODE_TX;
  #endif
  HAL_UART_Init(&huart2);

  #if defined(FEEDBACK_SERIAL_USART2) || defined(DEBUG_SERIAL_USART2)
    USART2->CR3 |= USART_CR3_DMAT;  // | USART_CR3_DMAR | USART_CR3_OVRDIS;
  #endif

  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin       = GPIO_PIN_2;
  GPIO_InitStruct.Pull      = GPIO_PULLUP; //GPIO_NOPULL;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  #ifdef CONTROL_SERIAL_USART2
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
  #endif

  hdma_usart2_tx.Instance                   = DMA1_Channel7;
  hdma_usart2_tx.Init.Direction             = DMA_MEMORY_TO_PERIPH;
  hdma_usart2_tx.Init.PeriphInc             = DMA_PINC_DISABLE;
  hdma_usart2_tx.Init.MemInc                = DMA_MINC_ENABLE;
  hdma_usart2_tx.Init.PeriphDataAlignment   = DMA_PDATAALIGN_BYTE;
  hdma_usart2_tx.Init.MemDataAlignment      = DMA_MDATAALIGN_BYTE;
  hdma_usart2_tx.Init.Mode                  = DMA_NORMAL;
  hdma_usart2_tx.Init.Priority              = DMA_PRIORITY_LOW;
  HAL_DMA_Init(&hdma_usart2_tx);

  #ifdef CONTROL_SERIAL_USART2
    __HAL_LINKDMA(&huart2, hdmatx, hdma_usart2_tx);
  #endif
  #if defined(FEEDBACK_SERIAL_USART2) || defined(DEBUG_SERIAL_USART2)
    DMA1_Channel7->CPAR     = (uint32_t) & (USART2->DR);
    DMA1_Channel7->CNDTR    = 0;
    DMA1->IFCR              = DMA_IFCR_CTCIF7 | DMA_IFCR_CHTIF7 | DMA_IFCR_CGIF7;
  #endif

}
#endif

#if defined(CONTROL_SERIAL_USART3) || defined(FEEDBACK_SERIAL_USART3) || defined(DEBUG_SERIAL_USART3)
void UART3_Init(void) {

  /* The code below is commented out - otwerwise Serial Receive does not work */
  // #ifdef CONTROL_SERIAL_USART3
  //   /* DMA1_Channel3_IRQn interrupt configuration */
  //   HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 5, 3);
  //   HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
  //   /* DMA1_Channel2_IRQn interrupt configuration */
  //   HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 5, 2);
  //   HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
  // #endif

  // Disable serial interrupt - it is not needed
  HAL_NVIC_DisableIRQ(DMA1_Channel3_IRQn);  // Rx Channel
  HAL_NVIC_DisableIRQ(DMA1_Channel2_IRQn);  // Tx Channel

  __HAL_RCC_DMA1_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_USART3_CLK_ENABLE();

  huart3.Instance             = USART3;
  huart3.Init.BaudRate        = USART3_BAUD;
  huart3.Init.WordLength      = USART3_WORDLENGTH;
  huart3.Init.StopBits        = UART_STOPBITS_1;
  huart3.Init.Parity          = UART_PARITY_NONE;
  huart3.Init.HwFlowCtl       = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling    = UART_OVERSAMPLING_16;
  #if defined(CONTROL_SERIAL_USART3)
    huart3.Init.Mode          = UART_MODE_TX_RX;
  #elif defined(DEBUG_SERIAL_USART3)
    huart3.Init.Mode          = UART_MODE_TX;
  #endif
  HAL_UART_Init(&huart3);

  #if defined(FEEDBACK_SERIAL_USART3) || defined(DEBUG_SERIAL_USART3)
    USART3->CR3 |= USART_CR3_DMAT;  // | USART_CR3_DMAR | USART_CR3_OVRDIS;
  #endif

  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin         = GPIO_PIN_10;
  GPIO_InitStruct.Pull        = GPIO_PULLUP;
  GPIO_InitStruct.Mode        = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed       = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  #ifdef CONTROL_SERIAL_USART3
    GPIO_InitStruct.Pin       = GPIO_PIN_11;
    GPIO_InitStruct.Mode      = GPIO_MODE_INPUT;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Peripheral DMA init*/
    hdma_usart3_rx.Instance                   = DMA1_Channel3;
    hdma_usart3_rx.Init.Direction             = DMA_PERIPH_TO_MEMORY;
    hdma_usart3_rx.Init.PeriphInc             = DMA_PINC_DISABLE;
    hdma_usart3_rx.Init.MemInc                = DMA_MINC_ENABLE;
    hdma_usart3_rx.Init.PeriphDataAlignment   = DMA_PDATAALIGN_BYTE;
    hdma_usart3_rx.Init.MemDataAlignment      = DMA_MDATAALIGN_BYTE;
    hdma_usart3_rx.Init.Mode                  = DMA_CIRCULAR; //DMA_NORMAL;
    hdma_usart3_rx.Init.Priority              = DMA_PRIORITY_LOW;
    HAL_DMA_Init(&hdma_usart3_rx);
    __HAL_LINKDMA(&huart3, hdmarx, hdma_usart3_rx);
  #endif

  hdma_usart3_tx.Instance                     = DMA1_Channel2;
  hdma_usart3_tx.Init.Direction               = DMA_MEMORY_TO_PERIPH;
  hdma_usart3_tx.Init.PeriphInc               = DMA_PINC_DISABLE;
  hdma_usart3_tx.Init.MemInc                  = DMA_MINC_ENABLE;
  hdma_usart3_tx.Init.PeriphDataAlignment     = DMA_PDATAALIGN_BYTE;
  hdma_usart3_tx.Init.MemDataAlignment        = DMA_MDATAALIGN_BYTE;
  hdma_usart3_tx.Init.Mode                    = DMA_NORMAL;
  hdma_usart3_tx.Init.Priority                = DMA_PRIORITY_LOW;
  HAL_DMA_Init(&hdma_usart3_tx);

  #ifdef CONTROL_SERIAL_USART3
    __HAL_LINKDMA(&huart3, hdmatx, hdma_usart3_tx);
  #endif
  #if defined(FEEDBACK_SERIAL_USART3) || defined(DEBUG_SERIAL_USART3)
    DMA1_Channel2->CPAR     = (uint32_t) & (USART3->DR);
    DMA1_Channel2->CNDTR    = 0;
    DMA1->IFCR              = DMA_IFCR_CTCIF2 | DMA_IFCR_CHTIF2 | DMA_IFCR_CGIF2;
  #endif
}
#endif

void MX_GPIO_Init(void) {
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

void MX_TIM_Init(void) {
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

void MX_ADC1_Init(void) {
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
  DMA1_Channel1->CPAR  = (uint32_t) & (ADC1->DR);
  DMA1_Channel1->CMAR  = (uint32_t)&adc_buffer;
  DMA1_Channel1->CCR   = DMA_CCR_MSIZE_1 | DMA_CCR_PSIZE_1 | DMA_CCR_MINC | DMA_CCR_CIRC | DMA_CCR_TCIE;
  DMA1_Channel1->CCR |= DMA_CCR_EN;

  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

/* ADC2 init function */
void MX_ADC2_Init(void) {
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
