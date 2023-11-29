/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
 **/
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COM_UART_H
#define __COM_UART_H

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../../../STM32F3xx_HAL_Driver/Inc/stm32f3xx_hal_uart.h"
#include "../../../STM32F3xx_HAL_Driver/Inc/stm32f3xx_hal_rcc.h"
#include "../../../STM32F3xx_HAL_Driver/Inc/stm32f3xx_hal_gpio.h"
/* USER CODE END Includes */



/* Exported types ------------------------------------------------------------*/
typedef enum
{
  Uart_OK       = 0x00U,
  Uart_ERROR    = 0x01U,
  Uart_BUSY     = 0x02U,
  Uart_TIMEOUT  = 0x03
} Uart_StatusTypeDef;
/*------------------------------------------------------------*/
typedef	struct
{
	UART_HandleTypeDef 	*HUSARTx;
	uint8_t	SESSION_ID;
}UART_HANDLER;


/* Peripheral Enable:  -------------------------------------------------------*/
/*								Enable / Disable			        		  */
   #define USART1_Enable       1        */
/*    #define USART2_Enable       1        */
/*    #define USART3_Enable       1        */



#ifdef 	USART1_Enable
	extern UART_HANDLER Huart1 ;
#endif
#ifdef	USART2_Enable
	extern UART_HANDLER	Huart2 ;
#endif
#ifdef	USART3_Enable
	extern UART_HANDLER	Huart3 ;
#endif


/*	Function Prototypes -----------------------------------------------------*/
Uart_StatusTypeDef _USARTx_Init(UART_HANDLER *Huartx, uint8_t SessionID);
Uart_StatusTypeDef _USARTx_DeInit(UART_HANDLER *Huartx);

#endif /* __COM_UART_H */
