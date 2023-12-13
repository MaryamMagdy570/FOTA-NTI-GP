/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    i2c.h
  * @brief   This file contains all the function prototypes for
  *          the i2c.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */


/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum
{
  I2C_OK       = 0x00U,
  I2C_ERROR    = 0x01U,
  I2C_BUSY     = 0x02U,
  I2C_TIMEOUT  = 0x03
} I2C_StatusTypeDef;


typedef	struct
{
	I2C_HandleTypeDef 	*HI2Cx;
	uint8_t				SESSION_ID;
}I2C_HANDLER;

/* USER CODE BEGIN Private defines */
/* Peripheral Enable: */

#define I2C1_Enable       1
//   #define SPI2_Enable       1
//   #define SPI3_Enable       1

/* USER CODE END Private defines */


#ifdef 	SPI1_Enable
	extern I2C_HandleTypeDef hi2c1 ;
#endif

/* USER CODE BEGIN Prototypes */
I2C_StatusTypeDef _I2Cx_Init(I2C_HANDLER *Hi2cx, uint8_t SessionID);
I2C_StatusTypeDef _I2Cx_DeInit(I2C_HANDLER *Hi2cx);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H__ */

