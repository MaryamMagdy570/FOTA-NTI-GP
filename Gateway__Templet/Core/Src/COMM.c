/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include <Services/COMM/COMM.h>



/* Private function prototypes ---------------------------------------------*/
/* USER CODE BEGIN PFP */
void Error_Handler(void);
/*----------------------------------------------------------------------------*/

static SERVICES_StatusTypeDef COMM_Transmit_NormalMODE(uint8_t *pdata, uint16_t Size, uint8_t Last_element, uint8_t sessID);
static SERVICES_StatusTypeDef COMM_Receive_NormalMODE(uint8_t *pdata, uint16_t Size,uint8_t Last_element , uint8_t sessID);

static SERVICES_StatusTypeDef COMM_Transmit_IT_NormalMODE(uint8_t *pdata, uint16_t Size ,uint8_t sessID);
static SERVICES_StatusTypeDef COMM_Receive_IT_NormalMODE(uint8_t *pdata, uint16_t Size ,uint8_t sessID);

static SERVICES_StatusTypeDef COMM_Transmit_DMA_NormalMODE(uint8_t *pdata, uint16_t Size ,uint8_t sessID);
static SERVICES_StatusTypeDef COMM_Receive_DMA_NormalMODE(uint8_t *pdata, uint16_t Size ,uint8_t sessID);

/*----------------------------------------------------------------------------*/

//static SERVICES_StatusTypeDef COMM_Transmit_BufferMODE(uint8_t *pdata, uint16_t Size, uint8_t Last_element, uint8_t sessID);
//static SERVICES_StatusTypeDef COMM_Receive_BufferMODE(uint8_t *pdata, uint16_t Size,uint8_t Last_element , uint8_t sessID);
//
//static SERVICES_StatusTypeDef COMM_Transmit_IT_BufferMODE(uint8_t *pdata, uint16_t Size ,uint8_t sessID);
//static SERVICES_StatusTypeDef COMM_Receive_IT_BufferMODE(uint8_t *pdata, uint16_t Size ,uint8_t sessID);
//
//static SERVICES_StatusTypeDef COMM_Transmit_DMA_BufferMODE(uint8_t *pdata, uint16_t Size ,uint8_t sessID);
//static SERVICES_StatusTypeDef COMM_Receive_DMA_BufferMODE(uint8_t *pdata, uint16_t Size ,uint8_t sessID);

/*----------------------------------------------------------------------------*/
/* USER CODE END PFP */


/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE BEGIN PTD */


/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */


/* Exported Variables --------------------------------------------------------*/
/* USER CODE BEGIN  */
COM_SESSION		NULL_SESSION = {0};
static COM_SESSION*	ARR_SESSIONS[8]; 		//Zero index for the NULL_SESSION Session.
/* USER CODE BEGIN  */
/***************************************************************************************************************************************************************************/

/***************************************************************************************************************************************************************************/
SERVICES_StatusTypeDef COMM_SessionInit(COM_SESSION *SessionHandler)
{
	// Initiate an array of sessions and make its first location point to the NULL_SESSION
	ARR_SESSIONS[0]	=	&NULL_SESSION;

	// check the index validity.
	if (SessionHandler->SessionID != 0 && SessionHandler->SessionID < 8)
	{
		// initiate Session state.
		SessionHandler->SessionState = SESSION_FREE;

		// initiate Session Process counter to zero.
		SessionHandler->SessionBuffer_Counter = 0;
		SessionHandler->SessionFIFO_Counter = 0;

		// initiate protocol Handler.
		switch (SessionHandler->Session_Protocol)
		{
			case SESSION_UART:
				_USARTx_Init( (SessionHandler->pSessionHandler), SessionHandler->SessionID);
				break;
			case SESSION_SPI:
				_SPIx_Init((SessionHandler->pSessionHandler), SessionHandler->SessionID);
				break;
			case SESSION_I2C:
				/*		I2C initialization function*/
				break;
			case SESSION_CAN:
				/*		CAN initialization function*/
				break;
			default:
				break;
		}
		// last step, put the Session pointer into the Arr_Sessions.
		ARR_SESSIONS[SessionHandler->SessionID] = SessionHandler;
	}
	else {
		Error_Handler();
	}
	return SERVICES_OK;
}
SERVICES_StatusTypeDef COMM_SessionDeInit(COM_SESSION *SessionHandler)
{
	if (SessionHandler->SessionID != 0 && SessionHandler->SessionID < 8)
	{
		// De_initiate protocol Handler.
		switch (SessionHandler->Session_Protocol)
			{
				case SESSION_UART:
					/*		UART initialization function*/
					break;
					_USARTx_DeInit( SessionHandler->pSessionHandler);
				case SESSION_SPI:
					_SPIx_DeInit(SessionHandler->pSessionHandler);
					break;
				case SESSION_I2C:
					/*		I2C initialization function*/
					break;
				case SESSION_CAN:
					/*		CAN initialization function*/
					break;
				default:
					break;
			}

		//Delete the session handler, by assigning it to the NULL_SESSON
		*SessionHandler = NULL_SESSION;

		// last step, Remove the Session pointer into the Arr_Sessions.
		ARR_SESSIONS[SessionHandler->SessionID] = NULL;
	}
	else {
		Error_Handler();
	}
	return SERVICES_OK;
}

SERVICES_StatusTypeDef COMM_Transmit(uint8_t *pdata, uint16_t Size, uint8_t Last_element, uint8_t sessID)
{
	// check the index validity.
	if (sessID != 0 && sessID < 8)
	{
		// Select the Session mode.
		switch (ARR_SESSIONS[sessID]->SessionMODE)
		{
			case SESSION_NormalMODE:
				COMM_Transmit_NormalMODE(pdata,Size,Last_element,sessID);
				break;
			case SESSION_BufferMODE:
				break;
			default:
				break;
		}
		// Reset Session state.
		ARR_SESSIONS[sessID]->SessionState = SESSION_FREE;
	}
	else {
		Error_Handler();
	}
	return SERVICES_OK;
}
SERVICES_StatusTypeDef COMM_Receive(uint8_t *pdata, uint16_t Size,uint8_t Last_element ,uint8_t sessID)
{
	// check the index validity.
	if (sessID != 0 && sessID < 8)
	{
		// Select the Session mode.
		switch (ARR_SESSIONS[sessID]->SessionMODE)
		{
			case SESSION_NormalMODE:
				COMM_Receive_NormalMODE(pdata,Size,Last_element,sessID);
				break;
			case SESSION_BufferMODE:
				break;
			default:
				break;
		}
		// Reset Session state.
		ARR_SESSIONS[sessID]->SessionState = SESSION_FREE;
	}
	else {
		Error_Handler();
	}
	return SERVICES_OK;
}

SERVICES_StatusTypeDef COMM_Transmit_IT(uint8_t *pdata, uint16_t Size ,uint8_t Last_element ,uint8_t sessID)
{
	// check the index validity.
		if (sessID != 0 && sessID < 8)
		{
			// Select the Session mode.
			switch (ARR_SESSIONS[sessID]->SessionMODE)
			{
				case SESSION_NormalMODE:
					COMM_Transmit_IT_NormalMODE(pdata,Size,sessID);
					break;
				case SESSION_BufferMODE:
					break;
				default:
					break;
			}
			// Reset Session state.
			ARR_SESSIONS[sessID]->SessionState = SESSION_FREE;
		}
		else {
			Error_Handler();
		}
		return SERVICES_OK;
}
SERVICES_StatusTypeDef COMM_Receive_IT(uint8_t *pdata, uint16_t Size ,uint8_t Last_element ,uint8_t sessID)
{
	// check the index validity.
		if (sessID != 0 && sessID < 8)
		{
			// Select the Session mode.
			switch (ARR_SESSIONS[sessID]->SessionMODE)
			{
				case SESSION_NormalMODE:
					COMM_Receive_IT_NormalMODE(pdata,Size,sessID);
					break;
				case SESSION_BufferMODE:
					break;
				default:
					break;
			}
			// Reset Session state.
			ARR_SESSIONS[sessID]->SessionState = SESSION_FREE;
		}
		else {
			Error_Handler();
		}
		return SERVICES_OK;
}

SERVICES_StatusTypeDef COMM_Transmit_DMA(uint8_t *pdata, uint16_t Size ,uint8_t sessID)
{
	// check the index validity.
		if (sessID != 0 && sessID < 8)
		{
			// Select the Session mode.
			switch (ARR_SESSIONS[sessID]->SessionMODE)
			{
				case SESSION_NormalMODE:
					COMM_Transmit_DMA_NormalMODE(pdata,Size,sessID);
					break;
				case SESSION_BufferMODE:
					break;
				default:
					break;
			}
			// Reset Session state.
			ARR_SESSIONS[sessID]->SessionState = SESSION_FREE;
		}
		else {
			Error_Handler();
		}
		return SERVICES_OK;
}
SERVICES_StatusTypeDef COMM_Receive_DMA(uint8_t *pdata, uint16_t Size ,uint8_t sessID)
{
	// check the index validity.
		if (sessID != 0 && sessID < 8)
		{
			// Select the Session mode.
			switch (ARR_SESSIONS[sessID]->SessionMODE)
			{
				case SESSION_NormalMODE:
					COMM_Receive_DMA_NormalMODE(pdata,Size,sessID);
					break;
				case SESSION_BufferMODE:
					break;
				default:
					break;
			}
			// Reset Session state.
			ARR_SESSIONS[sessID]->SessionState = SESSION_FREE;
		}
		else {
			Error_Handler();
		}
		return SERVICES_OK;
}

SERVICES_StatusTypeDef COMM_Create_FIFO(COM_FIFO *ptfifo,uint8_t *fifoID,uint8_t sessID)
{
	if (ARR_SESSIONS[sessID]->SessionFIFO_Counter < FIFO_NUM ) {
		// load the FIFO pointer into the array of FIFOs.
		ARR_SESSIONS[sessID]->pSessionFIFO_Array[ARR_SESSIONS[sessID]->SessionFIFO_Counter] = ptfifo;
		ARR_SESSIONS[sessID]->pSessionFIFO_Array[ARR_SESSIONS[sessID]->SessionFIFO_Counter]->SessionFIFO_counter = ARR_SESSIONS[sessID]->pSessionFIFO_Array[ARR_SESSIONS[sessID]->SessionFIFO_Counter]->SessionFIFO_Size;
		// Get an ID for this FIFO.
		*fifoID = ARR_SESSIONS[sessID]->SessionFIFO_Counter;
		// increase the FIFO_Counter.
		ARR_SESSIONS[sessID]->SessionFIFO_Counter++;
	}
	else
	{
		Error_Handler();
		return	SERVICES_ERROR;
	}
	return	SERVICES_OK;
}
SERVICES_StatusTypeDef COMM_Delete_FIFO(uint8_t fifoID,uint8_t sessID)
{
	if (fifoID < FIFO_NUM ) {
		// load the FIFO pointer into the array of FIFOs.
		ARR_SESSIONS[sessID]->pSessionFIFO_Array[fifoID] = NULL;
		// decrease the FIFO_Counter.
		ARR_SESSIONS[sessID]->SessionFIFO_Counter--;
	}
	else
	{
		Error_Handler();
		return	SERVICES_ERROR;
	}
	return	SERVICES_OK;
}
SERVICES_StatusTypeDef COMM_Transmit_FIFO(uint8_t *pdata,uint16_t Size, uint8_t fifoID,uint8_t sessID)
{
	uint16_t startIndex = ARR_SESSIONS[sessID]->pSessionFIFO_Array[fifoID]->SessionFIFO_Size - ARR_SESSIONS[sessID]->pSessionFIFO_Array[fifoID]->SessionFIFO_counter;
	if (fifoID < FIFO_NUM) {
		if ( Size < ARR_SESSIONS[sessID]->pSessionFIFO_Array[fifoID]->SessionFIFO_counter ) {
			for (uint16_t var = 0; var < Size; ++var,++startIndex) {
				ARR_SESSIONS[sessID]->pSessionFIFO_Array[fifoID]->pSessionFIFO[startIndex] = pdata[var];
			}
			ARR_SESSIONS[sessID]->pSessionFIFO_Array[fifoID]->SessionFIFO_counter -= Size;
			if (ARR_SESSIONS[sessID]->pSessionFIFO_Array[fifoID]->SessionFIFO_counter == 0) {
				COMM_Transmit_DMA(ARR_SESSIONS[sessID]->pSessionFIFO_Array[fifoID]->pSessionFIFO, ARR_SESSIONS[sessID]->pSessionFIFO_Array[fifoID]->SessionFIFO_Size, sessID);
				ARR_SESSIONS[sessID]->pSessionFIFO_Array[fifoID]->SessionFIFO_counter = ARR_SESSIONS[sessID]->pSessionFIFO_Array[fifoID]->SessionFIFO_Size;
			}
		} else {
			return SERVICES_ERROR;
		}
	} else {
		Error_Handler();
	}
	return	SERVICES_OK;
}


SERVICES_StatusTypeDef COMM_DMAPause(uint8_t sessID){return 0;}
SERVICES_StatusTypeDef COMM_DMAResume(uint8_t sessID){return 0;}
SERVICES_StatusTypeDef COMM_DMAStop(uint8_t sessID){return 0;}
/***************************************************************************************************************************************************************************/

//// Set the index value of the Data buffers.
//		static uint8_t	Buffer_Index = 0;  // default in Normal mode.
//
//		// Change Session state.
//		ARR_SESSIONS[sessID]->SessionState = SESSION_BUSY;
//
//		// send the Frame using the protocol Transmit function
//		ARR_SESSIONS[sessID]->pData[Buffer_Index] = pdata;
//		ARR_SESSIONS[sessID]->DataSize[Buffer_Index] = Size;


/***************************************************************************************************************************************************************************/
static SERVICES_StatusTypeDef COMM_Transmit_NormalMODE(uint8_t *pdata, uint16_t Size, uint8_t Last_element, uint8_t sessID)
{
	// check the index validity.
	if (sessID != 0 && sessID < 8)
	{
		// Change Session state.
		ARR_SESSIONS[sessID]->SessionState = SESSION_BUSY;

		// send the Frame using the protocol Transmit function
		switch (ARR_SESSIONS[sessID]->Session_Protocol)
		{
			case SESSION_UART:
				for ( uint8_t var = 0; var < Size; ++var)
				{
					if (pdata[var] == Last_element) {
						HAL_UART_Transmit((ARR_SESSIONS[sessID]->pSessionHandler), pdata, 1, 10);
						break;
					}
					else {
						HAL_UART_Transmit((ARR_SESSIONS[sessID]->pSessionHandler), pdata, 1, 10);
					}
					pdata++;
				}
				break;

			case SESSION_SPI:
				for ( uint8_t var = 0; var < Size; ++var)
				{
					if (pdata[var] == Last_element) {
						HAL_SPI_Transmit((ARR_SESSIONS[sessID]->pSessionHandler), pdata, 1, 10);
						break;
					}
					else {
						HAL_SPI_Transmit((ARR_SESSIONS[sessID]->pSessionHandler), pdata, 1, 10);
					}
					pdata++;
				}
				break;

			case SESSION_I2C:
				/*		I2C Transmit function*/
				break;

			case SESSION_CAN:
				/*		CAN Transmit function*/
				break;

			default:
				break;
		}
		// Reset Session state.
		ARR_SESSIONS[sessID]->SessionState = SESSION_FREE;
	}
	else {
		Error_Handler();
	}
	return SERVICES_OK;
}
static SERVICES_StatusTypeDef COMM_Receive_NormalMODE(uint8_t *pdata, uint16_t Size,uint8_t Last_element , uint8_t sessID)
{
	// check the index validity.
	if (sessID != 0 && sessID < 8)
	{
		// Change Session state.
		ARR_SESSIONS[sessID]->SessionState = SESSION_BUSY;
		uint16_t	timerOut = 10000 ;  // the timer for the first element.
		// send the Frame using the protocol Transmit function
		switch (ARR_SESSIONS[sessID]->Session_Protocol)
		{
		case SESSION_UART:
			for ( uint8_t var = 0; var < Size; ++var)
			{
				HAL_UART_Receive((ARR_SESSIONS[sessID]->pSessionHandler), pdata, 1, timerOut);
				if (pdata[var] == Last_element) {
					break;
				}
				timerOut = 100; // the timer after the first element.
				pdata++;
			}
			break;
		case SESSION_SPI:
			for ( uint8_t var = 0; var < Size; ++var)
			{
				HAL_SPI_Receive((ARR_SESSIONS[sessID]->pSessionHandler), pdata, 1, timerOut);
				if (pdata[var] == Last_element) {
					break;
				}
				timerOut = 100; // the timer after the first element.
				pdata++;
			}
			break;
		case SESSION_I2C:
			/*		I2C Transmit function*/
			break;
		case SESSION_CAN:
			/*		CAN Transmit function*/
			break;
		default:
			break;
		}

		// Reset Session state.
		ARR_SESSIONS[sessID]->SessionState = SESSION_FREE;
	}
	else {
		Error_Handler();
	}
	return SERVICES_OK;
}

static SERVICES_StatusTypeDef COMM_Transmit_IT_NormalMODE(uint8_t *pdata, uint16_t Size ,uint8_t sessID)
{
	// check the index validity.
	if (sessID != 0 && sessID < 8)
	{
		// Change Session state.
		ARR_SESSIONS[sessID]->SessionState = SESSION_BUSY;

		// send the Frame using the protocol Transmit function
		switch (ARR_SESSIONS[sessID]->Session_Protocol)
		{
			case SESSION_UART:
				/*		UART Transmit function*/
				HAL_UART_Transmit_IT((ARR_SESSIONS[sessID]->pSessionHandler), pdata, Size);
				break;
			case SESSION_SPI:
				/*		SPI Transmit function*/
				break;
			case SESSION_I2C:
				/*		I2C Transmit function*/
				break;
			case SESSION_CAN:
				/*		CAN Transmit function*/
				break;
			default:
				break;
		}
		// Reset Session state.
		ARR_SESSIONS[sessID]->SessionState = SESSION_FREE;
	}
	else {
		Error_Handler();
	}
	return SERVICES_OK;
}
static SERVICES_StatusTypeDef COMM_Receive_IT_NormalMODE(uint8_t *pdata, uint16_t Size ,uint8_t sessID)
{
	// check the index validity.
	if (sessID != 0 && sessID < 8)
	{
		// Change Session state.
		ARR_SESSIONS[sessID]->SessionState = SESSION_BUSY;

		// send the Frame using the protocol Transmit function
		switch (ARR_SESSIONS[sessID]->Session_Protocol)
		{
		case SESSION_UART:
				/*		UART Transmit function*/
				// &( Huart1.HUSARTx)
				HAL_UART_Receive_IT((ARR_SESSIONS[sessID]->pSessionHandler),pdata, Size);
				break;
			case SESSION_SPI:
				/*		SPI Transmit function*/
				break;
			case SESSION_I2C:
				/*		I2C Transmit function*/
				break;
			case SESSION_CAN:
				/*		CAN Transmit function*/
				break;
			default:
				break;
		}
		// Reset Session state.
		ARR_SESSIONS[sessID]->SessionState = SESSION_FREE;
	}
	else {
		Error_Handler();
	}
	return SERVICES_OK;
}

static SERVICES_StatusTypeDef COMM_Transmit_DMA_NormalMODE(uint8_t *pdata, uint16_t Size ,uint8_t sessID)
{
	// check the index validity.
	if (sessID != 0 && sessID < 8)
	{
		// Change Session state.
		ARR_SESSIONS[sessID]->SessionState = SESSION_BUSY;

		// send the Frame using the protocol Transmit function
		switch (ARR_SESSIONS[sessID]->Session_Protocol)
		{
			case SESSION_UART:
				/*		UART Transmit function*/
				HAL_UART_Transmit_DMA((ARR_SESSIONS[sessID]->pSessionHandler),pdata, Size);
				break;
			case SESSION_SPI:
				/*		SPI Transmit function*/
				HAL_SPI_Transmit_DMA((ARR_SESSIONS[sessID]->pSessionHandler), pdata, Size);
				break;
			case SESSION_I2C:
				/*		I2C Transmit function*/
				break;
			case SESSION_CAN:
				/*		CAN Transmit function*/
				break;
			default:
				break;
		}
		// Reset Session state.
		ARR_SESSIONS[sessID]->SessionState = SESSION_FREE;
	}
	else {
		Error_Handler();
	}
	return SERVICES_OK;
}
static SERVICES_StatusTypeDef COMM_Receive_DMA_NormalMODE(uint8_t *pdata, uint16_t Size ,uint8_t sessID)
{
	// check the index validity.
	if (sessID != 0 && sessID < 8)
	{
		// Change Session state.
		ARR_SESSIONS[sessID]->SessionState = SESSION_BUSY;

		// send the Frame using the protocol Transmit function
		switch (ARR_SESSIONS[sessID]->Session_Protocol)
		{
		case SESSION_UART:
				HAL_UART_Receive_DMA((ARR_SESSIONS[sessID]->pSessionHandler),pdata, Size);
				break;
			case SESSION_SPI:
				HAL_SPI_Receive_DMA((ARR_SESSIONS[sessID]->pSessionHandler), pdata, Size);
				break;
			case SESSION_I2C:
				/*		I2C Transmit function*/
				break;
			case SESSION_CAN:
				/*		CAN Transmit function*/
				break;
			default:
				break;
		}
		// Reset Session state.
		ARR_SESSIONS[sessID]->SessionState = SESSION_FREE;
	}
	else {
		Error_Handler();
	}
	return SERVICES_OK;
}

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
