/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
 **/
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define  	_1S_					pdMS_TO_TICKS(1000)
#define 	MConn_QueueSet_Size		50
#define		N_Send_QueueSet_Size	50
#define 	MAX_SLAVE_COUNT			5
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
// ACKS OF  OUT_N_S_MConn_MSD_Queue
uint8_t FILE_OPEN[5]	=	{0,3,6,9,12};
uint8_t FILE_CLOSE[5]	=	{1,4,7,10,13};
uint8_t FILE_RECORD[5]	=	{2,5,8,11,14};
/* USER CODE END Variables */


/* Task Handlers -------------------------------------------------------------*/
/* USER CODE BEGIN Tasks */

/* General Branch tasks ------------------------------------------------------*/
TaskHandle_t Check_Validity_Task_Handler;
/*----------------------------------------------------------------------------*/
/* General Control Branch tasks ----------------------------------------------*/
TaskHandle_t Init_Deinit_Reset_Task_Handler;
TaskHandle_t Control_Branch_Task_Handler;
TaskHandle_t Control_DMA_Task_Handler;
/*----------------------------------------------------------------------------*/
/* ESP Branch tasks ----------------------------------------------------------*/
TaskHandle_t Manage_ESP_Task_Handler;
TaskHandle_t Send_to_ESP_Task_Handler;
TaskHandle_t Receive_from_EST_Task_Handler;
/*----------------------------------------------------------------------------*/
/* SD Branch tasks -----------------------------------------------------------*/
TaskHandle_t Manage_SD_Task_Handler;
TaskHandle_t Send_to_SD_Task_Handler;
TaskHandle_t Receive_from_SD_Task_Handler;
/*----------------------------------------------------------------------------*/
/* Main Nodes Branch tasks ---------------------------------------------------*/
TaskHandle_t Check_Network_Task_Handler;
TaskHandle_t Manage_Network_Task_Handler;
TaskHandle_t Manage_Connection_Task_Handler;
TaskHandle_t Receive_from_Node_Task_Handler;
TaskHandle_t Send_to_Node_Task_Handler;
/*----------------------------------------------------------------------------*/

/* USER CODE END Tasks */


/* Queue Handlers ------------------------------------------------------------*/
/* USER CODE BEGIN Queues */

/* General Branch Queues -----------------------------------------------------*/
QueueHandle_t	OUT_E_S_MESP_MSD_Queue = NULL ;
QueueHandle_t	OUT_S_N_MSD_MNet_Queue = NULL ;
QueueHandle_t	OUT_S_N_MSD_MConn_Queue = NULL ;
QueueHandle_t	OUT_N_S_MConn_MSD_Queue = NULL ;
/*----------------------------------------------------------------------------*/
/* General Control Branch Queues ---------------------------------------------*/
QueueHandle_t	IN_G_CBranch_CDMA_Queue = NULL ;
/*----------------------------------------------------------------------------*/
/* ESP Branch Queues ---------------------------------------------------------*/
QueueHandle_t	IN_E_Receive_MESP_Queue = NULL ;
QueueHandle_t	IN_E_MESP_Send_Queue = NULL ;
/*----------------------------------------------------------------------------*/
/* SD Branch Queues ----------------------------------------------------------*/
QueueHandle_t	IN_S_Receive_MSD_Queue = NULL ;
QueueHandle_t	IN_S_MSD_Send_Queue = NULL ;
/*----------------------------------------------------------------------------*/
/* Main Nodes Branch Queues --------------------------------------------------*/
QueueHandle_t	IN_N_MNetwork_MConn_Queue = NULL ;
QueueHandle_t	IN_N_Receive_MConn_Queue_1 = NULL ;
QueueHandle_t	IN_N_Receive_MConn_Queue_2 = NULL ;
QueueHandle_t	IN_N_MConn_Send_Queue_1 = NULL ;
QueueHandle_t	IN_N_MConn_Send_Queue_2 = NULL ;
QueueHandle_t	IN_N_Receive_CheckNet_Queue = NULL ;
QueueHandle_t	IN_N_CheckNet_Send_Queue = NULL ;
QueueHandle_t	IN_N_MNetwork_Send_Queue = NULL ;
QueueHandle_t	IN_N_CheckNet_MNetwork_Queue = NULL;
// Queue set:
QueueSetHandle_t	MConn_QueueSet  = NULL;
QueueSetHandle_t	N_Send_QueueSet  = NULL;
/*----------------------------------------------------------------------------*/

/* USER CODE END Queues */


/* Semaphore Handlers --------------------------------------------------------*/
/* USER CODE BEGIN Semaphores */

/* General Branch Semaphores -------------------------------------------------*/
SemaphoreHandle_t	OUT_N_S_MConn_MNSD_Semph ;
/*----------------------------------------------------------------------------*/
/* General Control Branch Semaphores -----------------------------------------*/
/*----------------------------------------------------------------------------*/
/* ESP Branch Semaphores -----------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/* SD Branch Semaphores ------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/* Main Nodes Branch Semaphores ----------------------------------------------*/
SemaphoreHandle_t	IN_N_CheckNet_Semph ;
SemaphoreHandle_t	IN_N_MConn_MNet_Semph ;
/*----------------------------------------------------------------------------*/

/* USER CODE END Semaphores */


/* Timer Handlers ------------------------------------------------------------*/
/* USER CODE BEGIN Timers */

/* General Branch Timers -----------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/* General Control Branch Timers ---------------------------------------------*/
/*----------------------------------------------------------------------------*/
/* ESP Branch Timers ---------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/* SD Branch Timers -----------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/* Main Nodes Branch Timers --------------------------------------------------*/
TimerHandle_t		Record_Timer = NULL ;
/*----------------------------------------------------------------------------*/

/* USER CODE END Timers */


/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */
void vRecord_TimerCallBack(TimerHandle_t Record_Timer);

/*USER TASKs BEGIN FunctionPrototypes*/

/* General Branch Fun */
void Check_Validity_Task_Func(void * pvParameters);
/* General Control Branch Fun */
void Init_Deinit_Reset_Task_Func(void * pvParameters);
void Control_Branch_Task_Func(void * pvParameters);
void Control_DMA_Task_Func(void * pvParameters);
/* ESP Branch Fun */
void Manage_ESP_Task_Func(void * pvParameters);
void Send_to_ESP_Task_Func(void * pvParameters);
void Receive_from_EST_Task_Func(void * pvParameters);
/* SD Branch Fun */
void Manage_SD_Task_Func(void * pvParameters);
void Send_to_SD_Task_Func(void * pvParameters);
void Receive_from_SD_Task_Func(void * pvParameters);
/* Main Nodes Branch Fun */
void Check_Network_Task_Func(void * pvParameters);
void Manage_Network_Task_Func(void * pvParameters);
void Manage_Connection_Task_Func(void * pvParameters);
void Receive_from_Node_Task_Func(void * pvParameters);
void Send_to_Node_Task_Func(void * pvParameters);
void ResetBranch(void);

/*USER TASKs END FunctionPrototypes*/

/* USER CODE END FunctionPrototypes */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/* ISRs code -----------------------------------------------------------------*/
void vRecord_TimerCallBack(TimerHandle_t Bump_Dist_Timer)
{}
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/* General Branch code -------------------------------------------------------*/
void Check_Validity_Task_Func(void * pvParameters)
{
	while(1)
	{

	}
}
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/* General Control Branch code -----------------------------------------------*/
void Init_Deinit_Reset_Task_Func(void * pvParameters)
{
	while(1)
	{

	}
}
void Control_Branch_Task_Func(void * pvParameters)
{
	while(1)
	{

	}
}
void Control_DMA_Task_Func(void * pvParameters)
{
	while(1)
	{

	}
}
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/* ESP Branch code -----------------------------------------------------------*/
void Manage_ESP_Task_Func(void * pvParameters)
{
	while(1)
	{

	}
}
void Send_to_ESP_Task_Func(void * pvParameters)
{
	while(1)
	{

	}
}
void Receive_from_EST_Task_Func(void * pvParameters)
{
	while(1)
	{

	}
}
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/* SD Branch code -------------------------------------------------------*/
void Manage_SD_Task_Func(void * pvParameters)
{
	while(1)
	{

	}
}
void Send_to_SD_Task_Func(void * pvParameters)
{
	while(1)
	{

	}
}
void Receive_from_SD_Task_Func(void * pvParameters)
{
	while(1)
	{

	}
}
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/* Main Nodes Branch code ----------------------------------------------------*/
uint8_t flag_address_buffer_update = 0;
uint8_t slave_address_buffer[MAX_SLAVE_COUNT]={0x50,0x51,0x52,0x53,0x54};
void Check_Network_Task_Func(void * pvParameters)
{
	uint8_t slave_address_buffer[MAX_SLAVE_COUNT];
    uint8_t data_to_slave = 0xAA;
    uint8_t data_from_slave;
    uint8_t slave_index = 0;
    while(1)
    {
    	//i2c transmit with slave address = 0x00
    	xQueueSend(IN_N_CheckNet_Send_Queue, &data_to_slave,0);
    	// receive from i2c slave their addresses
    	xQueueReceive(IN_N_Receive_CheckNet_Queue,&data_from_slave ,0);
    	/*** store slave address in slave_address_buffer ***/
    	uint8_t isNewSlave = 1;
    	for (uint8_t i = 0; i < MAX_SLAVE_COUNT; ++i)
    	{
    		if (slave_address_buffer[i] == data_from_slave)
    		{
    			isNewSlave = 0;
    			break;
    		}
    	}
    	// If it's a new slave, add it to the array
    	if (isNewSlave && (slave_index < MAX_SLAVE_COUNT))
    	{
    		slave_address_buffer[slave_index++] = data_from_slave;
    	}
    	//send the buffer to manage network using queue
    	xQueueSend(IN_N_CheckNet_MNetwork_Queue ,slave_address_buffer,0);
    }
}

void Manage_Network_Task_Func(void * pvParameters)
{
	uint8_t update_node_buffer[MAX_SLAVE_COUNT];
	uint8_t node_id;
	uint8_t StateSUM;
	while(1)
	{
	   //get the slave address buffer from check network
	   if (flag_address_buffer_update == 0)
	   {
		   xQueueReceive(IN_N_CheckNet_MNetwork_Queue ,slave_address_buffer,portMAX_DELAY);
		   flag_address_buffer_update = 1; //trigger it only once
	   }
	   else
	   {
		   if (uxQueueMessagesWaiting(OUT_S_N_MSD_MNet_Queue) > 0) //check if there is update in queue
		   {
			 //get the nodeS i want to update from sd card
			 xQueueReceive(OUT_S_N_MSD_MNet_Queue ,update_node_buffer,0);
			 StateSUM = 0;
			 for(uint8_t var=0; var < 5;var++)
			 {
			   StateSUM += update_node_buffer[var];
			 }
		   }
		   while(StateSUM > 0)
		   {
			 if (uxQueueMessagesWaiting(OUT_S_N_MSD_MNet_Queue) > 0)
			 {
			    //get the nodeS i want to update from sd card
			    xQueueReceive(OUT_S_N_MSD_MNet_Queue ,update_node_buffer,0);
			    StateSUM = 0;
			    for(node_id=0; node_id < MAX_SLAVE_COUNT;node_id++)
			    {
			  	   StateSUM += update_node_buffer[node_id];
			    }
			 }
			 for(node_id=0 ; node_id<MAX_SLAVE_COUNT;node_id++)
			 {
				if(update_node_buffer[node_id]==1)
				{
					//SEND THE NODE TO MCONN TASK
					xQueueSend(IN_N_MNetwork_MConn_Queue ,&node_id,0);
					//SEND THE SLAVE ADDRESS OF THE NODE TO SEND TASK
					xQueueSend(IN_N_MNetwork_Send_Queue ,&slave_address_buffer[node_id],0);
					xSemaphoreTake(IN_N_MConn_MNet_Semph,portMAX_DELAY);
				}
			  }
		   }
	   }
	}
}

void Manage_Connection_Task_Func(void * pvParameters)
{
	QueueSetMemberHandle_t 	local_Queue = NULL;
	uint8_t			Node_Number;
	uint8_t			record_localBuffer[5][2][50];
	uint8_t			MSD_ack_Buffer[2];
	uint8_t			ack_localBuffer[2];
	bool	 		swing = 0;
	uint8_t 		recordSize = 0;
	uint8_t 		oldSize[5] = {3,3,3,3,3};  // the size of the Info starting message.
	uint8_t 		var = 0;
	static int16_t	record_Counter[5] = {-1,-1,-1,-1,-1};

	while(1)
	{
		// take the starting semaphore.
		// check which queue has received new data.
		local_Queue = xQueueSelectFromSet(MConn_QueueSet, 0);
		if (local_Queue == OUT_S_N_MSD_MConn_Queue) // Receive new record from Manage SD task
		{
			if (record_Counter <= 0) // for sending first line in communication process.
			{
				// store the record inside a local buffer.
				xQueueReceive(local_Queue, record_localBuffer[Node_Number][!swing], 0);
				if (record_Counter == 0) {
					// store the record inside a local buffer.
					xQueueReceive(local_Queue, record_localBuffer[Node_Number][swing], 0);
					while(record_localBuffer[Node_Number][swing][var] != '#')
					{
						recordSize++;
					}
					var = 0; // return the var value to zero.
					recordSize++; // as we add the size of the next record.  (Need to be checked)
					record_localBuffer[Node_Number][!swing][oldSize[Node_Number]] = recordSize;
					// send the old record and the size of this record and the new one to the send task.
					xQueueSend(IN_N_MConn_Send_Queue_1,record_localBuffer[Node_Number][!swing],0);
					oldSize[Node_Number]++;
					xQueueSend(IN_N_MConn_Send_Queue_2,&oldSize[Node_Number],0);
					// clear the buffer and change the values.
					for (uint8_t var_l = 0; var_l < oldSize[Node_Number]; ++var_l) {
						record_localBuffer[Node_Number][!swing][var_l] = 0;
					}
					swing = !swing; // Flip the swing value.
					oldSize[Node_Number] = recordSize; // store the recordsize as the oldsize.
				}
			}
			else
			{
				// store the record inside a local buffer.
				xQueueReceive(local_Queue, record_localBuffer[swing], 0);
				// count the record size.
				while(record_localBuffer[Node_Number][swing][var] != '#') {
					recordSize++;
				}
				var = 0;	// return the var value to zero.
				recordSize++; // as we add the size of the next record.  (Need to be checked)
				record_localBuffer[Node_Number][!swing][oldSize[Node_Number]] = recordSize;
				// send the old record and the size of the new one to the send task.
				xQueueSend(IN_N_MConn_Send_Queue_1,record_localBuffer[!swing],0);
				oldSize[Node_Number]++;
				xQueueSend(IN_N_MConn_Send_Queue_2,&oldSize[Node_Number],0);
				// clear the buffer and change the values.
				for (uint8_t var_l = 0; var_l < oldSize[Node_Number]; ++var_l) {
					record_localBuffer[Node_Number][!swing][var_l] = 0;
				}
				swing = !swing; // Flip the swing value.
				oldSize[Node_Number] = recordSize; // store the recordsize as the oldsize.
			}
			record_Counter[Node_Number]++;
			// give the ACK that trigger the Manage SD task
			MSD_ack_Buffer[0] =	FILE_RECORD[Node_Number];
			MSD_ack_Buffer[1] = 0;
			xQueueSend(OUT_N_S_MConn_MSD_Queue,MSD_ack_Buffer,0);
			// Give the semaphore to the manage Network to change the node number.
			xSemaphoreGive(IN_N_MConn_MNet_Semph);
		}
		else if (local_Queue == IN_N_MNetwork_MConn_Queue) // Receive Data from Manage network task
		{
			// store the Node Number inside a local buffer.
			xQueueReceive(local_Queue, &Node_Number, 0);
		}
		else if (local_Queue == IN_N_Receive_MConn_Queue_1) // Receive acknowledge from the Connected Node.
		{
			// store the acknowledge inside a local buffer.
			xQueueReceive(local_Queue, &ack_localBuffer[0], 0);
			// store the Node Number.
			xQueueReceive(local_Queue, &ack_localBuffer[1], 0);
			// switch on acks value.
			switch (ack_localBuffer[0])
			{
				case 	0x01:  // Start connection.
					// ask the SD for starting information {Number of Records(2-Bytes),First record size(1-Byte)}.
					// give the ACK that Open File in the SD task
					MSD_ack_Buffer[0] =	FILE_OPEN[ack_localBuffer[1]];
					MSD_ack_Buffer[1] = 0;
					xQueueSend(OUT_N_S_MConn_MSD_Queue,MSD_ack_Buffer,0);
					break;

				case 	0x02:  // Accepted ACK for new Image .
					// ask the SD for the First Record.
					MSD_ack_Buffer[0] =	FILE_RECORD[ack_localBuffer[1]];
					MSD_ack_Buffer[1] = 0;
					xQueueSend(OUT_N_S_MConn_MSD_Queue,MSD_ack_Buffer,0);
					break;

				case 	0x03:  // Not Accepted n_ack for new Image .
					// Delete the Image and inform the Server.
					MSD_ack_Buffer[0] =	FILE_CLOSE[ack_localBuffer[1]];
					MSD_ack_Buffer[1] = 0;
					xQueueSend(OUT_N_S_MConn_MSD_Queue,MSD_ack_Buffer,0);
					break;

				case 	0x04:	// Start synchronization at the start of record (1).
					// store the start time.
					break;

				case 	0x05:	// End synchronization at the end of record (1).
					// store the start time.
					break;

				case 	0x06:	// process Failed.
					// stop and end the process.
					MSD_ack_Buffer[0] =	FILE_CLOSE[ack_localBuffer[1]];
					MSD_ack_Buffer[1] = 0;
					xQueueSend(OUT_N_S_MConn_MSD_Queue,MSD_ack_Buffer,0);
					break;

				case 	0x07:	// End Process successfully.
					ResetBranch();
					record_Counter[ack_localBuffer[1]] = 0;
					oldSize[ack_localBuffer[1]] = 3;
					// send the end ACK to the MSD task.
					MSD_ack_Buffer[0] =	FILE_CLOSE[ack_localBuffer[1]];
					MSD_ack_Buffer[1] = 0;
					xQueueSend(OUT_N_S_MConn_MSD_Queue,MSD_ack_Buffer,0);
					break;

				default:
					break;
			}
		}
	}
}

void Receive_from_Node_Task_Func(void * pvParameters)
{
	uint8_t		ack_localBuffer[50];
	uint8_t		NodeNum;
	while(1)
	{
		// store the received data into the local buffer
		//HAL_I2C_Slave_Receive_DMA(hi2c, pData, Size)
		// send the data to the manage connection task.
		xQueueSend(IN_N_Receive_MConn_Queue_1,ack_localBuffer,0);
		// get the Node ID from the Address value, and send it to the Manage Connection.
		// GETID_FUN(ADDRESS,NodeNum);
		xQueueSend(IN_N_Receive_MConn_Queue_2,&NodeNum,0);
	}
}

void Send_to_Node_Task_Func(void * pvParameters)
{
	QueueSetMemberHandle_t 	local_Queue = NULL;
	uint8_t			DevAddress = 0;
	uint8_t			record_localBuffer[50];
	uint8_t			record_Size;
	while(1)
	{
		// receive the data from the Queue.
		local_Queue = xQueueSelectFromSet(N_Send_QueueSet, 0);
		if (local_Queue == IN_N_MConn_Send_Queue_1) // Receive new record from Manage SD task
		{
			xQueueReceive(IN_N_MConn_Send_Queue_1, record_localBuffer, 0);
			xQueueReceive(IN_N_MConn_Send_Queue_1, &record_Size, 0);
			// send the data.
			//HAL_I2C_Master_Transmit_DMA(hi2c, 0x00, record_localBuffer, record_Size);
		}
		else if (local_Queue == IN_N_CheckNet_Send_Queue)
		{
			xQueueReceive(IN_N_CheckNet_Send_Queue, record_localBuffer, 0);
			// send the data.
			//HAL_I2C_Master_Transmit_DMA(hi2c, 0x00, record_localBuffer[0], 1);
		}
		else if (local_Queue == IN_N_MNetwork_Send_Queue)
		{
			xQueueReceive(IN_N_MNetwork_Send_Queue, &DevAddress, 0);
			// send the data.
			//HAL_I2C_Master_Transmit_DMA(hi2c, 0x00, record_localBuffer[0], 1);
		}
	}
}
/*----------------------------------------------------------------------------*/
void ResetBranch(void)
{
	flag_address_buffer_update=0;
}
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/* USER CODE END Application */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
	// General Branches
	OUT_N_S_MConn_MNSD_Semph = xSemaphoreCreateBinary();
	// General control
	// ESP
	// SD
	// Nodes
	IN_N_CheckNet_Semph = xSemaphoreCreateBinary();
	IN_N_MConn_MNet_Semph = xSemaphoreCreateBinary();
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
	Record_Timer = xTimerCreate("Record Timer", _1S_, pdTRUE, NULL, &vRecord_TimerCallBack ); // the periodic will change according to the flashing speed.
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
	// General Branches
	OUT_E_S_MESP_MSD_Queue 	= xQueueCreate(2,sizeof(uint8_t));
	OUT_S_N_MSD_MNet_Queue 	= xQueueCreate(2,sizeof(uint8_t));
	OUT_S_N_MSD_MConn_Queue = xQueueCreate(2,sizeof(uint8_t));
	OUT_N_S_MConn_MSD_Queue	= xQueueCreate(2,sizeof(uint8_t));
	// General control
	IN_G_CBranch_CDMA_Queue = xQueueCreate(2,sizeof(uint8_t));
	// ESP
	IN_E_Receive_MESP_Queue = xQueueCreate(2,sizeof(uint8_t));
	IN_E_MESP_Send_Queue    = xQueueCreate(2,sizeof(uint8_t));
	// SD
	IN_S_Receive_MSD_Queue 	= xQueueCreate(2,sizeof(uint8_t));
	IN_S_MSD_Send_Queue 	= xQueueCreate(2,sizeof(uint8_t));
	// Nodes
	IN_N_MNetwork_MConn_Queue   = xQueueCreate(1,sizeof(uint8_t));
	IN_N_Receive_MConn_Queue_1  = xQueueCreate(2,sizeof(uint8_t));
	IN_N_Receive_MConn_Queue_2	= xQueueCreate(1,sizeof(uint8_t));
	IN_N_MConn_Send_Queue_1 	= xQueueCreate(2,sizeof(uint8_t));
	IN_N_MConn_Send_Queue_2	    = xQueueCreate(1,sizeof(uint8_t));
	IN_N_Receive_CheckNet_Queue = xQueueCreate(2,sizeof(uint8_t));
	IN_N_CheckNet_Send_Queue 	= xQueueCreate(2,sizeof(uint8_t));
	IN_N_MNetwork_Send_Queue	= xQueueCreate(2,sizeof(uint8_t));
	IN_N_CheckNet_MNetwork_Queue= xQueueCreate(2,sizeof(uint8_t));
	// QueueSet.
	MConn_QueueSet			= xQueueCreateSet(MConn_QueueSet_Size);
	N_Send_QueueSet 		= xQueueCreateSet(N_Send_QueueSet_Size);
	// Add to set
	xQueueAddToSet(IN_N_Receive_MConn_Queue_1, MConn_QueueSet);
	xQueueAddToSet(OUT_S_N_MSD_MConn_Queue, MConn_QueueSet);
	xQueueAddToSet(IN_N_MNetwork_MConn_Queue, MConn_QueueSet);

	xQueueAddToSet(IN_N_MConn_Send_Queue_1, N_Send_QueueSet);
	xQueueAddToSet(IN_N_MNetwork_Send_Queue, N_Send_QueueSet);
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
	/* General Branch Fun */
	xTaskCreate( Check_Validity_Task_Func , "Check Validity"  , 100 , NULL , 26U , &Check_Validity_Task_Handler );
	/* General Control Branch Fun */
	xTaskCreate( Init_Deinit_Reset_Task_Func , "Initi,Deinit,and Reset"  , 100 , NULL , 30U , &Init_Deinit_Reset_Task_Handler );
	xTaskCreate( Control_Branch_Task_Func , "Control Branch"  , 100 , NULL , 29U , &Control_Branch_Task_Handler );
	xTaskCreate( Control_DMA_Task_Func , "Control DMA"  , 100 , NULL , 28U , &Control_DMA_Task_Handler );
	/* ESP Branch Fun */
	xTaskCreate( Receive_from_EST_Task_Func , "Receive from EST"  , 100 , NULL , 5U , &Receive_from_EST_Task_Handler );
	xTaskCreate( Manage_ESP_Task_Func , "Manage ESP"  , 100 , NULL , 4U , &Manage_ESP_Task_Handler );
	xTaskCreate( Send_to_ESP_Task_Func , "Send to ESP"  , 100 , NULL , 3U , &Send_to_ESP_Task_Handler );
	/* SD Branch Fun */
	xTaskCreate( Manage_SD_Task_Func , "Manage SD"  , 100 , NULL , 5U , &Manage_SD_Task_Handler );
	xTaskCreate( Send_to_SD_Task_Func , "Send to SD"  , 100 , NULL , 4U , &Send_to_SD_Task_Handler );
	xTaskCreate( Receive_from_SD_Task_Func , "Receive from SD"  , 100 , NULL , 3U , &Receive_from_SD_Task_Handler );
	/* Main Nodes Branch Fun */
	xTaskCreate( Check_Network_Task_Func , "Check Network"  , 100 , NULL , 5U , &Check_Network_Task_Handler );
	xTaskCreate( Manage_Network_Task_Func , "Manage Network"  , 100 , NULL , 4U , &Manage_Network_Task_Handler );
	xTaskCreate( Receive_from_Node_Task_Func , "Receive from Node"  , 100 , NULL , 3U , &Receive_from_Node_Task_Handler );
	xTaskCreate( Manage_Connection_Task_Func , "Manage Connection"  , 100 , NULL , 2U , &Manage_Connection_Task_Handler );
	xTaskCreate( Send_to_Node_Task_Func , "Send to Node"  , 100 , NULL , 1U , &Send_to_Node_Task_Handler );
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}
