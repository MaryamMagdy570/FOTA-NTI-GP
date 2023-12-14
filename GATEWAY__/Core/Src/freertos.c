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
#include <string.h>
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
uint8_t FILE_OPEN[5]	=	{0,1,2,3,4};
uint8_t FILE_CLOSE[5]	=	{5,6,7,8,9};
uint8_t FILE_RECORD[5]	=	{10,11,12,13,14};
/* USER CODE END Variables */
<<<<<<< HEAD
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
=======


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

/* Security Branch Queues -----------------------------------------------------*/
QueueHandle_t	S_Sec_ESP_TO_MSD_Queue = NULL;
/* General Branch Queues -----------------------------------------------------*/
QueueHandle_t	OUT_E_S_MESP_MSD_Queue = NULL ;
QueueHandle_t	OUT_S_E_MSD_MESP_Queue = NULL ;
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
QueueSetHandle_t    MSD_QueueSet = NULL;
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
SemaphoreHandle_t	IN_S_MNSD_Receive_Semph;
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

>>>>>>> parent of 1597b3d (sd_tasks update)

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

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
	// General Branches
	OUT_N_S_MConn_MNSD_Semph = xSemaphoreCreateBinary();
	IN_S_MNSD_Receive_Semph	 = xSemaphoreCreateBinary();
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
	S_Sec_ESP_TO_MSD_Queue	= xQueueCreate(2,sizeof(uint8_t));
	OUT_S_E_MSD_MESP_Queue 	= xQueueCreate(2,sizeof(uint8_t));
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
	IN_S_Receive_MSD_Queue 	= xQueueCreate(50,sizeof(uint8_t));
	IN_S_MSD_Send_Queue 	= xQueueCreate(128,sizeof(uint8_t));
	IN_S_Send_MSD_Queue 	= xQueueCreate(1,sizeof(uint8_t));
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
	MSD_QueueSet 		    = xQueueCreateSet(200);

	// Add to set
	xQueueAddToSet(IN_N_Receive_MConn_Queue_1, MConn_QueueSet);
	xQueueAddToSet(OUT_S_N_MSD_MConn_Queue, MConn_QueueSet);
	xQueueAddToSet(IN_N_MNetwork_MConn_Queue, MConn_QueueSet);

	xQueueAddToSet(IN_N_MConn_Send_Queue_1, N_Send_QueueSet);
	xQueueAddToSet(IN_N_MNetwork_Send_Queue, N_Send_QueueSet);


	xQueueAddToSet( IN_S_Receive_MSD_Queue, MSD_QueueSet);
	xQueueAddToSet( IN_S_Send_MSD_Queue , MSD_QueueSet);
	xQueueAddToSet( OUT_N_S_MConn_MSD_Queue , MSD_QueueSet);
	xQueueAddToSet( OUT_E_S_MESP_MSD_Queue , MSD_QueueSet);
	xQueueAddToSet( S_Sec_ESP_TO_MSD_Queue , MSD_QueueSet);



  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

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
	xTaskCreate( Manage_SD_Task_Func , "Manage SD"  , 700 , NULL , 5U , &Manage_SD_Task_Handler );
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

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

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

	//xSemaphoreTake()
	uint8_t receive_buffer[128];
	uint16_t blocks_num=0;
	uint8_t ack=0;
	while(1)
	{

		if (xSemaphoreTake(Manage_ESP_Semph,100))
		{

			xQueueReceive(queue_sizefromsec/not created/, (uint8_t)&blocks_num, 100);

			if (xSemaphoreTake(Receive_Data_Semph,100/block time/))
			{

				while (blocks_num)
				{
					if (uxQueueMessagesWaiting(queue_from_MSD) > 0)
					{
						xQueueReceive(queue_from_MSD,&ack,100/block time/);
						xQueueSend(queue_send_ack_to_esp,&ack,100/block time/);
						xSemaphoreGive(Send_MESP_Semph);
						xSemaphoreGive(Receive_MESP_Semph);

					}
					if (uxQueueMessagesWaiting(IN_E_Receive_MESP_Queue) > 0)
					{
						xQueueReceive(IN_E_Receive_MESP_Queue, receive_buffer, 100/block time/);
						blocks_num--;
						xQueueSend(OUT_E_S_MESP_MSD_Queue, receive_buffer, 100/block time/);
					}
				}

			}
		}
	}
}void Manage_ESP_Task_Func(void * pvParameters)
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
FIL fil1; 		//File1 handle
FIL fil2; 		//File2 handle
FIL fil3; 		//File3 handle
FIL fil4; 		//File4 handle
FIL fil5; 		//File5 handle
FIL Current_File_Handle_for_Read;
FIL Current_File_Handle_for_Write;
FRESULT fres; // ONLY USED FOR DEBUGGING
// SD TASKS
void Manage_SD_Task_Func(void * pvParameters)
{
	QueueHandle_t local_Queue = NULL;

	uint8_t	MNet_SelectNode_localBuffer[5]	= {0};
	uint8_t	ESP_Record_localBuffer[128] = {0};
	uint8_t	ESP_SelectNode_localBuffer 	= 0;
	uint8_t	MConn_REQUEST_localBuffer[2] = {0};
	uint8_t	SD_Receive_MConn_Record_localBuffer[50] = {0};

	FATFS FatFs; 	//Fatfs handle
	//SD MOUNT
	fres = f_mount(&FatFs, "", 1); //1=mount now


	while(1)
	{
	// check which queue has received new data.
	local_Queue = xQueueSelectFromSet(MSD_QueueSet, portMAX_DELAY);
	if (local_Queue == IN_S_Receive_MSD_Queue) //Receive from SD_Receive task
	{
		// Receive record from SD_Receive task
		xQueueReceive(local_Queue, SD_Receive_MConn_Record_localBuffer, portMAX_DELAY);

		// SEND RECORD TO MCONN
		xQueueSend(OUT_S_N_MSD_MConn_Queue,SD_Receive_MConn_Record_localBuffer,0);

	}
	else if (local_Queue == OUT_N_S_MConn_MSD_Queue)	 // request to open or close file of request record
	{
		xQueueReceive(local_Queue, MConn_REQUEST_localBuffer, portMAX_DELAY);

		switch(MConn_REQUEST_localBuffer[0])
		{
			case 0 :	fres = f_open(&fil1, "NODE1.txt", FA_READ );
								break;
			case 1:	fres = f_open(&fil2, "NODE2.txt", FA_READ );
								break;
			case 2:	fres = f_open(&fil3, "NODE3.txt", FA_READ );
								break;
			case 3:	fres = f_open(&fil4, "NODE4.txt", FA_READ );
								break;
			case 4:	fres = f_open(&fil5, "NODE5.txt", FA_READ );
								break;

			case 10: Current_File_Handle_for_Read = fil1;
										xSemaphoreGive(IN_S_MNSD_Receive_Semph);// give the semaphore that trigger the Manage SD task
												break;
			case 11: Current_File_Handle_for_Read = fil2;
										xSemaphoreGive(IN_S_MNSD_Receive_Semph);// give the semaphore that trigger the Manage SD task
												break;
			case 12: Current_File_Handle_for_Read = fil3;
										xSemaphoreGive(IN_S_MNSD_Receive_Semph);// give the semaphore that trigger the Manage SD task
												break;
			case 13: Current_File_Handle_for_Read = fil4;
										xSemaphoreGive(IN_S_MNSD_Receive_Semph);// give the semaphore that trigger the Manage SD task
												break;
			case 14: Current_File_Handle_for_Read = fil5;
										xSemaphoreGive(IN_S_MNSD_Receive_Semph);// give the semaphore that trigger the Manage SD task
												break;

			case 5: 	f_close(&fil1);
												MNet_SelectNode_localBuffer[0] = 0;
												xQueueSend(OUT_S_N_MSD_MNet_Queue ,MNet_SelectNode_localBuffer,0);
												break;
			case 6: 	f_close(&fil2);
												MNet_SelectNode_localBuffer[1] = 0;
												xQueueSend(OUT_S_N_MSD_MNet_Queue ,MNet_SelectNode_localBuffer,0);
												break;
			case 7: 	f_close(&fil3);
												MNet_SelectNode_localBuffer[2] = 0;
												xQueueSend(OUT_S_N_MSD_MNet_Queue ,MNet_SelectNode_localBuffer,0);
												break;
			case 8: 	f_close(&fil4);
												MNet_SelectNode_localBuffer[3] = 0;
												xQueueSend(OUT_S_N_MSD_MNet_Queue ,MNet_SelectNode_localBuffer,0);
												break;
			case 9: 	f_close(&fil5);
												MNet_SelectNode_localBuffer[4] = 0;
												xQueueSend(OUT_S_N_MSD_MNet_Queue ,MNet_SelectNode_localBuffer,0);
												break;

				default: break;
		}
	}
	else if (local_Queue == S_Sec_ESP_TO_MSD_Queue)   // esp select the node
	{
			//recieve the selected node number
			xQueueReceive(local_Queue, &ESP_SelectNode_localBuffer, portMAX_DELAY);
			switch (ESP_SelectNode_localBuffer)
			{
			  case 1: 	fres = f_open(&fil1, "NODE1.txt", FA_WRITE | FA_CREATE_ALWAYS);
							Current_File_Handle_for_Write = fil1;
							MNet_SelectNode_localBuffer[0] = 1;
							break;
			  case 2: 	fres = f_open(&fil2, "NODE2.txt", FA_WRITE | FA_CREATE_ALWAYS);
							Current_File_Handle_for_Write = fil2;
							MNet_SelectNode_localBuffer[1] = 1;
							break;
			  case 3: 	fres = f_open(&fil3, "NODE3.txt", FA_WRITE | FA_CREATE_ALWAYS);
							Current_File_Handle_for_Write = fil3;
							MNet_SelectNode_localBuffer[2] = 1;
							break;
			  case 4: 	fres = f_open(&fil4, "NODE4.txt", FA_WRITE | FA_CREATE_ALWAYS);
							Current_File_Handle_for_Write = fil4;
							MNet_SelectNode_localBuffer[3] = 1;
							break;
			  case 5: 	fres = f_open(&fil5, "NODE5.txt", FA_WRITE | FA_CREATE_ALWAYS);
							Current_File_Handle_for_Write = fil5;
							MNet_SelectNode_localBuffer[4] = 1;
							break;
					default:  break;
			}
	}
	else if (local_Queue == OUT_E_S_MESP_MSD_Queue )		 // un completed yet
	{
			// receive the block of records from esp_manage
			xQueueReceive(local_Queue, ESP_Record_localBuffer, portMAX_DELAY);

			// send data from buffer to send to sd task
			xQueueSend(IN_S_MSD_Send_Queue,ESP_Record_localBuffer,0);
	}
	else;
	}
}


void Send_to_SD_Task_Func(void * pvParameters)   //write
{
	BYTE Record_localWriteBuffer[512];
  UINT bytesWrote;
	while(1)
	{
		// receive the data from sd_manage into the local buffer.
		xQueueReceive(IN_S_MSD_Send_Queue, Record_localWriteBuffer, portMAX_DELAY);

		// send the data from local buffer to SD card
  	fres = f_write(&Current_File_Handle_for_Write, Record_localWriteBuffer, 512 , &bytesWrote);

	}
}

void Receive_from_SD_Task_Func(void * pvParameters)   //read
{
  UINT bytesRead = 0;

	while(1)
	{
			// take the triggering semaphore
			xSemaphoreTake(IN_S_MNSD_Receive_Semph, portMAX_DELAY);

			// clearing buffers
			uint8_t Record_localReadBuffer[50]={0};
			uint8_t Temp_localReadBuffer[50]={0};

    	// Read data from the file into the buffer
			fres = f_read(&Current_File_Handle_for_Read, Temp_localReadBuffer,49, &bytesRead);

   	 	Temp_localReadBuffer[bytesRead] = '\0'; // Null-terminate the buffer

    	char* sequencePos = strstr((char*)Temp_localReadBuffer, "\r\n"); // Search for "\r\n" sequence

			// Calculate the length until the "\r\n" sequence
			int lengthUntilSequence = sequencePos - (char*)Temp_localReadBuffer;

			// Move the file pointer after the "\r\n" sequence for the next read
			int newPosition = f_tell(&Current_File_Handle_for_Read) - (bytesRead - lengthUntilSequence) + 2;

			if (newPosition >= 0)
			{
				f_lseek(&Current_File_Handle_for_Read, newPosition);
			}
			else
			{}

			memcpy(Record_localReadBuffer, Temp_localReadBuffer, lengthUntilSequence);
			Record_localReadBuffer[lengthUntilSequence] = '#';

			// send the data from local buffer to the manage connection task.
			xQueueSend(IN_S_Receive_MSD_Queue,Record_localReadBuffer,0);
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
			if (record_Counter[Node_Number] <= 0) // for sending first line in communication process.
			{
				// store the record inside a local buffer.
				xQueueReceive(local_Queue, record_localBuffer[Node_Number][!swing], 0);
				if (record_Counter[Node_Number] == 0) {
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
				else
				{
					record_Counter[Node_Number]++; // it will be 0;
					//send second record.
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
					MSD_ack_Buffer[0] =	FILE_RECORD[ack_localBuffer[1]]; // third record.
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

<<<<<<< HEAD
=======
  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
	// General Branches
	OUT_N_S_MConn_MNSD_Semph = xSemaphoreCreateBinary();
	IN_S_MNSD_Receive_Semph	 = xSemaphoreCreateBinary();
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
	S_Sec_ESP_TO_MSD_Queue	= xQueueCreate(2,sizeof(uint8_t));
	OUT_S_E_MSD_MESP_Queue 	= xQueueCreate(2,sizeof(uint8_t));
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
	MSD_QueueSet 		    = xQueueCreateSet(200);

	// Add to set
	xQueueAddToSet(IN_N_Receive_MConn_Queue_1, MConn_QueueSet);
	xQueueAddToSet(OUT_S_N_MSD_MConn_Queue, MConn_QueueSet);
	xQueueAddToSet(IN_N_MNetwork_MConn_Queue, MConn_QueueSet);

	xQueueAddToSet(IN_N_MConn_Send_Queue_1, N_Send_QueueSet);
	xQueueAddToSet(IN_N_MNetwork_Send_Queue, N_Send_QueueSet);


	xQueueAddToSet(  IN_S_Receive_MSD_Queue, MSD_QueueSet);
	xQueueAddToSet( OUT_N_S_MConn_MSD_Queue , MSD_QueueSet);
	//xQueueAddToSet( S_Sec_ESP_TO_MSD_Queue , MSD_QueueSet);


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
	xTaskCreate( Manage_SD_Task_Func , "Manage SD"  , 700 , NULL , 5U , &Manage_SD_Task_Handler );
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
>>>>>>> parent of 1597b3d (sd_tasks update)
