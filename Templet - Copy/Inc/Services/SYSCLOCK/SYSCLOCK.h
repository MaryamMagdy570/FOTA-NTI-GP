/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
*/
/* USER CODE END Header */


/* Define to prevent recursive inclusion ----------------------------*/
#ifndef __SYSCLOCK__H
#define __SYSCLOCK__H


/* Private includes -------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../../STM32F3xx_HAL_Driver/Inc/stm32f3xx_hal_rcc.h"
#include "../../STM32F3xx_HAL_Driver/Inc/stm32f3xx_hal.h"
/* USER CODE END Includes */

/* Private types ----------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ---------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro ----------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */


/* functions prototypes ---------------------------------------------*/
void SystemClock_Config(void);

#endif /* __SYSCLOCK__H */