#include <stdio.h>
#include <conio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/* Priorities at which the tasks are created. */
/*#define sleeping_TASK_PRIORITY		( tskIDLE_PRIORITY + 4 )
#define	breakfirst_TASK_PRIORITY		( tskIDLE_PRIORITY + 3 )
#define	work_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )
#define	dinner_TASK_PRIORITY		( tskIDLE_PRIORITY + 2 )*/

#define sleeping_TASK_PRIORITY		4
#define	breakfirst_TASK_PRIORITY		3
#define	work_TASK_PRIORITY		1
#define	dinner_TASK_PRIORITY		2

#define FREQUENCY_MS			pdMS_TO_TICKS( 2400UL )

static void sleepingTask(void *pvParameters);
static void breakfirstTask(void *pvParameters);
static void workTask(void *pvParameters);
static void dinnerTask(void *pvParameters);

void main_blinky( void )
{
	TickType_t xNextWakeTime;
	xNextWakeTime = xTaskGetTickCount();
	TickType_t lsleeping[2] = {xNextWakeTime, 1000};
	TickType_t lbreakfirst[2] = { xNextWakeTime, 400 };
	TickType_t lwork[2] = { xNextWakeTime, 1600 };
	TickType_t ldinner[2] = { xNextWakeTime, 400 };


	xTaskCreate(sleepingTask,			/* The function that implements the task. */
		"sleeping", 							/* The text name assigned to the task - for debug only as it is not used by the kernel. */
		configMINIMAL_STACK_SIZE, 		/* The size of the stack to allocate to the task. */
		(void *)&lsleeping, 							/* The parameter passed to the task - not used in this simple case. */
		sleeping_TASK_PRIORITY,/* The priority assigned to the task. */
		NULL);
	xTaskCreate(breakfirstTask,			
		"breakfirst", 							
		configMINIMAL_STACK_SIZE, 		
		(void *)&lbreakfirst,
		breakfirst_TASK_PRIORITY,
		NULL);
	xTaskCreate(workTask,			
		"work", 							
		configMINIMAL_STACK_SIZE, 		
		(void *)&lwork,
		work_TASK_PRIORITY,
		NULL);
	xTaskCreate(dinnerTask,			
		"dinner", 							
		configMINIMAL_STACK_SIZE, 		
		(void *)&ldinner,
		dinner_TASK_PRIORITY,
		NULL);


	vTaskStartScheduler();

	/* If all is well, the scheduler will now be running, and the following
	line will never be reached.  If the following line does execute, then
	there was insufficient FreeRTOS heap memory available for the idle and/or
	timer tasks	to be created.  See the memory management section on the
	FreeRTOS web site for more details. */
	for( ;; );
}

static void sleepingTask(void *pvParameters)
{
	TickType_t start;
	start = *((TickType_t *)pvParameters) - 2400UL;
	const TickType_t xBlockTime = FREQUENCY_MS;
	for (;; ) {
		vTaskDelayUntil(&start, xBlockTime);
		printf("sleeping_s: %d\r\n", xTaskGetTickCount());
		TickType_t s = xTaskGetTickCount();
		while (xTaskGetTickCount() < (s + 1000)) {
		}
		printf("sleeping: %d\r\n", xTaskGetTickCount());
	}
}

static void breakfirstTask(void *pvParameters)
{
	TickType_t start;
	start = *((TickType_t *)pvParameters) - 1600UL;
	const TickType_t xBlockTime = FREQUENCY_MS;
	for (;; ) {
		vTaskDelayUntil(&start, xBlockTime);
		printf("breakfirst_s: %d\r\n", xTaskGetTickCount());
		TickType_t s = xTaskGetTickCount();
		while (xTaskGetTickCount() < (s + 200)) {
		}
		printf("breakfirst: %d\r\n", xTaskGetTickCount());
	}
}


static void workTask(void *pvParameters)
{
	TickType_t start;
	start = *((TickType_t *)pvParameters) - 1800UL;
	const TickType_t xBlockTime = FREQUENCY_MS;
	for (;; ) {
		vTaskDelayUntil(&start, xBlockTime);
		printf("work_s: %d\r\n", xTaskGetTickCount());
		TickType_t s = xTaskGetTickCount();
		while (xTaskGetTickCount() < (s + 1000)) {
		}
		printf("work: %d\r\n", xTaskGetTickCount());
	}
}


static void dinnerTask(void *pvParameters)
{
	TickType_t start;
	start = *((TickType_t *)pvParameters) - 400UL;
	const TickType_t xBlockTime = FREQUENCY_MS;
	for (;; ) {
		vTaskDelayUntil(&start, xBlockTime);
		printf("dinner_s: %d\r\n", xTaskGetTickCount());
		TickType_t s = xTaskGetTickCount();
		while (xTaskGetTickCount() < (s + 200)) {
		}
		printf("dinner: %d\r\n", xTaskGetTickCount());
	}
}



