/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
*/
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMM_INTERFACE__H
#define __COMM_INTERFACE__H

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Uart/COM_Uart.h"
#include "Spi/COM_Spi.h"
#include "I2C/COM_I2C.h"
#include "CAN/COM_CAN.h"
/* USER CODE END Includes */


/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum
{
  SESSION_FREE      	= 0x00U,
  SESSION_BUSY    		= 0x01U
} SESSION_StatusTypeDef;
typedef enum
{
  SESSION_NormalMODE      	= 0x00U,
  SESSION_BufferMODE    		= 0x01U,
  SESSION_FIFOMODE        		= 0x02U
} SESSION_MODETypeDef;
typedef enum
{
  SESSION_UART      = 0x00U,
  SESSION_SPI    	= 0x01U,
  SESSION_I2C    	= 0x02U,
  SESSION_CAN    	= 0x03U
} SESSION_PROTOCOLE;
typedef enum
{
  SERVICES_OK       = 0x00U,
  SERVICES_ERROR    = 0x01U,
  SERVICES_BUSY     = 0x02U,
  SERVICES_TIMEOUT  = 0x03
} SERVICES_StatusTypeDef;

typedef struct _COM_FIFO
{
	uint8_t						*pSessionFIFO;
	uint8_t						SessionFIFO_Size;
}COM_FIFO;
/*------------------------------------------------------------*/
typedef struct _COM_SESSION
{
	uint8_t						SessionID;
	SESSION_MODETypeDef			SessionMODE;
	SESSION_StatusTypeDef		SessionState;
	uint8_t						*pData[5]; 			// pointer of array of data
	uint16_t					DataSize[5];		// pointer of array of data
	uint8_t						SessionProcessCounter;
	SESSION_PROTOCOLE			Session_Protocol;
	void 					    *pSessionHandler;
	COM_FIFO					*pSessionFIFO;
} COM_SESSION;
/* USER CODE END PTD */


/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */


/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
//#define 		CAST_TO_UART_HANDLER(psessionh) ((struct UART_HANDLER*)(psessionh))
//#define		_SPI_HANDLER_CAST(psessionh)	(struct COM_SPI_HANDLER*)psessionh
//#define		_I2C_HANDLER_CAST(psessionh)	(struct COM_I2C_HANDLER*)psessionh
//#define		_CAN_HANDLER_CAST(psessionh)	(struct COM_CAN_HANDLER*)psessionh
/* USER CODE END PM */


/* Exported functions prototypes ---------------------------------------------*/
SERVICES_StatusTypeDef COMM_SessionInit(COM_SESSION *SessionHandler);
SERVICES_StatusTypeDef COMM_SessionDeInit(COM_SESSION *SessionHandler);

SERVICES_StatusTypeDef COMM_Transmit(uint8_t *pdata, uint16_t Size, uint32_t Timeout, uint8_t Last_element, uint8_t sessID);
SERVICES_StatusTypeDef COMM_Receive(uint8_t *pdata, uint16_t Size, uint32_t Timeout,uint8_t Last_element ,uint8_t sessID);

SERVICES_StatusTypeDef COMM_Transmit_IT(uint8_t *pdata, uint16_t Size ,uint8_t Last_element ,uint8_t sessID);
SERVICES_StatusTypeDef COMM_Receive_IT(uint8_t *pdata, uint16_t Size ,uint8_t Last_element ,uint8_t sessID);

SERVICES_StatusTypeDef COMM_Transmit_DMA(uint8_t *pdata, uint16_t Size ,uint8_t sessID);
SERVICES_StatusTypeDef COMM_Receive_DMA(uint8_t *pdata, uint16_t Size ,uint8_t sessID);

SERVICES_StatusTypeDef COMM_Transmit_FIFO(uint8_t *pdata, uint16_t Size,uint8_t sessID);
SERVICES_StatusTypeDef COMM_Receive_FIFO(uint8_t *pdata, uint16_t Size,uint8_t sessID);

SERVICES_StatusTypeDef COMM_DMAPause(uint8_t sessID);
SERVICES_StatusTypeDef COMM_DMAResume(uint8_t sessID);
SERVICES_StatusTypeDef COMM_DMAStop(uint8_t sessID);



#endif /* __COMM_INTERFACE__H */
