/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
 **/
/* USER CODE END Header */

/* Private includes ----------------------------------------------------------*/
#include "COM_Uart.h"

/* Exported types ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
static void Error_Handler(void);
static void UART_MspInit(UART_HandleTypeDef* uartHandle);
static void UART_MspDeInit(UART_HandleTypeDef* uartHandle);



/* Private Variables ---------------------------------------------------------*/
#ifdef 	USART1_Enable
	UART_HandleTypeDef husart_1 =
	{
		 .Instance = USART1,
		 .Init.BaudRate = 9600,
		 .Init.WordLength = UART_WORDLENGTH_8B,
		 .Init.StopBits = UART_STOPBITS_1,
		 .Init.Parity = UART_PARITY_NONE,
		 .Init.Mode = UART_MODE_TX_RX,
		 .Init.HwFlowCtl = UART_HWCONTROL_NONE,
		 .Init.OverSampling = UART_OVERSAMPLING_16,
		 .Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE,
		 .AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT
	};
	UART_HANDLER 	Huart1 =
	{
			.HUSARTx = &husart_1,
			.SESSION_ID = 0
	};
#endif
#ifdef	USART2_Enable
	UART_HandleTypeDef husart_2 = {
		 .Instance = USART2,
		 .Init.BaudRate = 9600,
		 .Init.WordLength = UART_WORDLENGTH_8B,
		 .Init.StopBits = UART_STOPBITS_1,
		 .Init.Parity = UART_PARITY_NONE,
		 .Init.Mode = UART_MODE_TX_RX,
		 .Init.HwFlowCtl = UART_HWCONTROL_NONE,
		 .Init.OverSampling = UART_OVERSAMPLING_16,
		 .Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE,
		 .AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT
	};
	UART_HANDLER	Huart2 =
	{
			.HUSARTx = &husart_2 ,
			.SESSION_ID = 0
	};
#endif
#ifdef	USART3_Enable
	UART_HandleTypeDef husart_3 = {
		 .Instance = USART3,
		 .Init.BaudRate = 9600,
		 .Init.WordLength = UART_WORDLENGTH_8B,
		 .Init.StopBits = UART_STOPBITS_1,
		 .Init.Parity = UART_PARITY_NONE,
		 .Init.Mode = UART_MODE_TX_RX,
		 .Init.HwFlowCtl = UART_HWCONTROL_NONE,
		 .Init.OverSampling = UART_OVERSAMPLING_16,
		 .Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE,
		 .AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT
	};
	UART_HANDLER	Huart3 =
	{
			.HUSARTx = &husart_3,
			.SESSION_ID = 0
	};
#endif



Uart_StatusTypeDef _USARTx_Init(UART_HANDLER *Huartx, uint8_t SessionID)
{
	/*  Enable RCC, Configure GPIOS */
	UART_MspInit(Huartx->HUSARTx);

	/*	Configure peripheral	*/
	if (Huartx->SESSION_ID == 0)
	{
	  if (HAL_UART_Init(Huartx->HUSARTx) != HAL_OK)
	  {
	     Error_Handler();
	     Huartx->SESSION_ID = 0;
	     return	Uart_ERROR;
	   }
	   else
	   {
		   Huartx->SESSION_ID = SessionID;
		   return	Uart_OK;
	   }
	}
	else
	{
		return	Uart_BUSY;
	}
	return	Uart_OK;
}


Uart_StatusTypeDef _USARTx_DeInit(UART_HANDLER *Huartx)
{
	/* Disable RCC, Reset GPIOS, Reset Peripheral  */
	UART_MspDeInit(Huartx->HUSARTx);
	Huartx->SESSION_ID = 0;
	return	Uart_OK;
}














static void UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PC4     ------> USART1_TX
    PC5     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
}

static void UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PC4     ------> USART1_TX
    PC5     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_4|GPIO_PIN_5);

  /* USER CODE BEGIN USART1_MspDeInit 1 */
    __HAL_RCC_USART1_FORCE_RESET();
    __HAL_RCC_USART1_RELEASE_RESET();
  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

  /* USER CODE BEGIN USART2_MspDeInit 1 */
    __HAL_RCC_USART2_FORCE_RESET();
    __HAL_RCC_USART2_RELEASE_RESET();
  /* USER CODE END USART2_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

  /* USER CODE BEGIN USART3_MspDeInit 1 */
    __HAL_RCC_USART3_FORCE_RESET();
    __HAL_RCC_USART3_RELEASE_RESET();
  /* USER CODE END USART3_MspDeInit 1 */
  }
}

static void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
