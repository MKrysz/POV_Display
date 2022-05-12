/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "led.h"
#include "clk.h"
#include "array.h"
#include <stdbool.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// #define MODE_IMAGE
#define MODE_ANALOG_CLOCK
// #define MODE_DIGITAL_CLOCK
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/**
 * @brief time of full rotation in ms
 * 
 */
volatile uint16_t period = 0;

/**
 * @brief time of full rotation in us
 * 
 */
volatile uint16_t periodUS = 0;


volatile size_t imgIdx = 0;

#include "img.h"

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void sleepRoutine();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC_Init();
  MX_SPI2_Init();
  MX_RTC_Init();
  MX_DMA_Init();
  MX_TIM6_Init();
  MX_TIM21_Init();
  MX_TIM22_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  TIM_Init();
  GPIO_Init();
  LED_Init();
  LED_AllBlack();
  HAL_Delay(1500);
  LED_AllWhite();
  HAL_Delay(1500);
  LED_AllBlack();
  HAL_Delay(2000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  /**
   * @brief time in ms since last full rotation after which display goes dormant
   * 
   */
  const uint16_t shutdownTime = 500;

  while (1)
  {

    while(1)
    {


      #ifdef MODE_IMAGE

      const size_t imgIdxMax = IMG_SIZE;
      LED_Send(image[imgIdxMax-imgIdx-1]);

      #endif


      #ifdef MODE_ANALOG_CLOCK

      const size_t imgIdxMax = 120;
      uint8_t sendData[8];
      size_t tempIdx = imgIdx;         
      // size_t tempIdx = (imgIdx + imgIdxMax/2) % imgIdxMax;

      //add background
      ARRAY_Copy(CLK_BKGD[tempIdx], sendData, 8);

      // //add hands
      // RTC_TimeTypeDef currentTime; 
      // // HAL_RTC_GetTime(&hrtc, &currentTime, RTC_FORMAT_BIN);
      // currentTime.Hours = 3;
      // currentTime.Minutes = 30;
      // currentTime.Seconds = 45;

      // if(currentTime.Hours * 10 == tempIdx)
      //   ARRAY_BitwiseOR(sendData, hours, sendData, 8);
      // if(currentTime.Minutes * 2 == tempIdx)
      //   ARRAY_BitwiseOR(sendData, minutes, sendData, 8);
      // if(currentTime.Seconds * 2 == tempIdx)
      //   ARRAY_BitwiseOR(sendData, seconds, sendData, 8);

      LED_Send(sendData);

      #endif

      //progress in showing img
      imgIdx++;
      if(imgIdx == imgIdxMax){
        imgIdx = 0;
      }

      while(__HAL_TIM_GET_COUNTER(&HTIM_US_DELAY) < (uint16_t)(periodUS/imgIdxMax));
    __HAL_TIM_SET_COUNTER(&HTIM_US_DELAY, 0);

      // //calculate and execute delay
      // uint32_t delayDurationUS = (period * 1000) / imgIdxMax;
      // if(delayDurationUS > 60000){
      // //   while(__HAL_TIM_GET_COUNTER(&HTIM_MS_DELAY) < (uint16_t)(period/imgIdxMax));
      // // __HAL_TIM_SET_COUNTER(&HTIM_MS_DELAY, 0);
      // }
      // else{
      //   if(period > 60){
      //   //   while(__HAL_TIM_GET_COUNTER(&HTIM_US_DELAY) < (uint16_t)(delayDurationUS));
      //   // __HAL_TIM_SET_COUNTER(&HTIM_US_DELAY, 0);
      //   }
      //   else{
      //     while(__HAL_TIM_GET_COUNTER(&HTIM_US_DELAY) < (uint16_t)(periodUS/imgIdxMax));
      //   __HAL_TIM_SET_COUNTER(&HTIM_US_DELAY, 0);
      //   }
      // }


      //shutdown if no rotation detected for specified time
      if(__HAL_TIM_GET_COUNTER(&HTIM_MS_GET) >= shutdownTime){
        sleepRoutine();
      }

    }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void sleepRoutine()
{
  LED_AllBlack();
  
  HAL_SuspendTick();
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
