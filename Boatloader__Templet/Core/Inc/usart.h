/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
#ifndef __USART_H__
#define __USART_H__

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
  Uart_OK       = 0x00U,
  Uart_ERROR    = 0x01U,
  Uart_BUSY     = 0x02U,
  Uart_TIMEOUT  = 0x03
} Uart_StatusTypeDef;

typedef	struct
{
	UART_HandleTypeDef 	*HUSARTx;
	uint8_t				SESSION_ID;
}UART_HANDLER;

/* USER CODE END PTD */



/* USER CODE BEGIN Private defines */
/* Peripheral Enable: */

   #define USART1_Enable       1
//   #define USART2_Enable       1
//   #define USART3_Enable       1

/* USER CODE END Private defines */


#ifdef 	USART1_Enable
	extern UART_HANDLER Huart1 ;
#endif

#ifdef	USART2_Enable
	extern UART_HANDLER	Huart2 ;
#endif

#ifdef	USART3_Enable
	extern UART_HANDLER	Huart3 ;
#endif


/* USER CODE BEGIN Prototypes */
Uart_StatusTypeDef _USARTx_Init(UART_HANDLER *Huartx, uint8_t SessionID);
Uart_StatusTypeDef _USARTx_DeInit(UART_HANDLER *Huartx);
/* USER CODE END Prototypes */


#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */
