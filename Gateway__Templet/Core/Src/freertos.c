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
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define  	_1S_					pdMS_TO_TICKS(1000)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

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
	// General control
	IN_G_CBranch_CDMA_Queue = xQueueCreate(2,sizeof(uint8_t));
	// ESP
	IN_E_Receive_MESP_Queue = xQueueCreate(2,sizeof(uint8_t));
	IN_E_MESP_Send_Queue    = xQueueCreate(2,sizeof(uint8_t));
	// SD
	IN_S_Receive_MSD_Queue 	= xQueueCreate(2,sizeof(uint8_t));
	IN_S_MSD_Send_Queue 	= xQueueCreate(2,sizeof(uint8_t));
	// Nodes
	IN_N_MNetwork_MConn_Queue   = xQueueCreate(2,sizeof(uint8_t));
	IN_N_Receive_MConn_Queue    = xQueueCreate(2,sizeof(uint8_t));
	IN_N_MConn_Send_Queue 	    = xQueueCreate(2,sizeof(uint8_t));
	IN_N_Receive_CheckNet_Queue = xQueueCreate(2,sizeof(uint8_t));
	IN_N_CheckNet_Send_Queue 	= xQueueCreate(2,sizeof(uint8_t));
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

void Check_Network_Task_Func(void * pvParameters)
{
	while(1)
	{

	}
}

void Manage_Network_Task_Func(void * pvParameters)
{
	while(1)
	{

	}
}

void Manage_Connection_Task_Func(void * pvParameters)
{
	while(1)
	{

	}
}

void Receive_from_Node_Task_Func(void * pvParameters)
{
	while(1)
	{

	}
}

void Send_to_Node_Task_Func(void * pvParameters)
{
	while(1)
	{

	}
}
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



/* USER CODE END Application */

