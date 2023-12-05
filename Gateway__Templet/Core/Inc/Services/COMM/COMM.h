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
#include "usart.h"
#include "spi.h"
#include "i2c.h"
#include "can.h"
/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define FIFO_NUM	5
#define BUFFER_NUM	5
/* USER CODE END PD */


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
  SESSION_BufferMODE    	= 0x01U
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
	uint16_t					SessionFIFO_Size;
	uint16_t					SessionFIFO_counter;
}COM_FIFO;

typedef struct _COM_BUFFER
{
	uint8_t						*pSessionBuffer;
	uint16_t					SessionBuffer_Size;
}COM_BUFFER;
/*------------------------------------------------------------*/
typedef struct _COM_SESSION
{
	uint8_t						SessionID;
	SESSION_MODETypeDef			SessionMODE;
	SESSION_StatusTypeDef		SessionState;
	COM_BUFFER					*pSessionBuffer_Array[BUFFER_NUM];
	COM_FIFO					*pSessionFIFO_Array[FIFO_NUM];
	uint8_t						SessionFIFO_Counter;
	uint8_t						SessionBuffer_Counter;
	SESSION_PROTOCOLE			Session_Protocol;
	void 					    *pSessionHandler;
} COM_SESSION;
/* USER CODE END PTD */


/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */


/* Exported functions prototypes ---------------------------------------------*/
SERVICES_StatusTypeDef COMM_SessionInit(COM_SESSION *SessionHandler);
SERVICES_StatusTypeDef COMM_SessionDeInit(COM_SESSION *SessionHandler);

SERVICES_StatusTypeDef COMM_Transmit(uint8_t *pdata, uint16_t Size, uint8_t Last_element, uint8_t sessID);
SERVICES_StatusTypeDef COMM_Receive(uint8_t *pdata, uint16_t Size,uint8_t Last_element ,uint8_t sessID);

SERVICES_StatusTypeDef COMM_Transmit_IT(uint8_t *pdata, uint16_t Size ,uint8_t Last_element ,uint8_t sessID);
SERVICES_StatusTypeDef COMM_Receive_IT(uint8_t *pdata, uint16_t Size ,uint8_t Last_element ,uint8_t sessID);

SERVICES_StatusTypeDef COMM_Transmit_DMA(uint8_t *pdata, uint16_t Size ,uint8_t sessID);
SERVICES_StatusTypeDef COMM_Receive_DMA(uint8_t *pdata, uint16_t Size ,uint8_t sessID);

SERVICES_StatusTypeDef COMM_Create_FIFO(COM_FIFO *ptfifo,uint8_t *fifoID,uint8_t sessID);
SERVICES_StatusTypeDef COMM_Delete_FIFO(uint8_t fifoID,uint8_t sessID);
SERVICES_StatusTypeDef COMM_Transmit_FIFO(uint8_t *pdata,uint16_t Size, uint8_t fifoID,uint8_t sessID);

SERVICES_StatusTypeDef COMM_DMAPause(uint8_t sessID);
SERVICES_StatusTypeDef COMM_DMAResume(uint8_t sessID);
SERVICES_StatusTypeDef COMM_DMAStop(uint8_t sessID);



#endif /* __COMM_INTERFACE__H */
