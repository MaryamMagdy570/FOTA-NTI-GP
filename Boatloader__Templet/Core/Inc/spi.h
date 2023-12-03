/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    spi.h
  * @brief   This file contains all the function prototypes for
  *          the spi.c file
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
#ifndef __SPI_H__
#define __SPI_H__

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
  SPI_OK       = 0x00U,
  SPI_ERROR    = 0x01U,
  SPI_BUSY     = 0x02U,
  SPI_TIMEOUT  = 0x03
} SPI_StatusTypeDef;

typedef	struct
{
	SPI_HandleTypeDef 	*HSPIx;
	uint8_t				SESSION_ID;
}SPI_HANDLER;

/* USER CODE END PTD */


/* USER CODE BEGIN Private defines */
/* Peripheral Enable: */

#define SPI1_Enable       1
//   #define SPI2_Enable       1
//   #define SPI3_Enable       1

/* USER CODE END Private defines */


#ifdef 	SPI1_Enable
	extern SPI_HANDLER Hspi1 ;
#endif

#ifdef	SPI2_Enable
	extern SPI_HANDLER	Hspi2 ;
#endif

#ifdef	SPI3_Enable
	extern SPI_HANDLER	Hspi3 ;
#endif


/* USER CODE BEGIN Prototypes */
SPI_StatusTypeDef _SPIx_Init(SPI_HANDLER *Hspix, uint8_t SessionID);
SPI_StatusTypeDef _SPIx_DeInit(SPI_HANDLER *Hspix);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */

