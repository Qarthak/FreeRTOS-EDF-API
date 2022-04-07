#include <stdio.h>
#include "freeRTOS.h"
#include "task.h"
#include "API.h"
#include "timers.h"
#include "heap.h"
#include "vScheduleEDF.c"

#define TASK_COUNT 3
TickType_t temperatureLastWakeTime = 0;
TickType_t heightLastWakeTime = 0;
TickType_t pressureLastWakeTime = 0;

Task *taskArray;
MinHeap deadlineHeap;

void generateTemperatureTask(void * p){
	while(1){
		TickType_t nextJobReleaseTime = temperatureLastWakeTime + pdMS_TO_TICKS(PERIOD_TEMPERATURE);
		printf("Next Job of Temperature will be released at : %d\n",nextJobReleaseTime);

		int temperature = getTemperature();
		printf("Temperature is : %d°C , at tick count : %d \n",temperature, xTaskGetTickCount());
		fflush(stdout);
		for(int i = 0 ; i < TASK_COUNT; i++){
				if(taskArray[i].task_id == 1){
					taskArray[i].deadline = nextJobReleaseTime+pdMS_TO_TICKS(PERIOD_TEMPERATURE);
					printf("Next Temperature Job will have Deadline will be : %d\n",taskArray[i].deadline);
					break;
				}
			}
		vTaskDelayUntil(&temperatureLastWakeTime,pdMS_TO_TICKS(PERIOD_TEMPERATURE));
	}
}

void generatePressureTask(void * p){
	while(1){
		TickType_t nextJobReleaseTime = pressureLastWakeTime + pdMS_TO_TICKS(PERIOD_PRESSURE);
		printf("Next Job of Pressure will be released at : %d\n",nextJobReleaseTime);

		int pressure = getPressure();
		printf("Pressure is : %d Hg , at tick count : %d \n",pressure, xTaskGetTickCount());
		fflush(stdout);
		for(int i = 0 ; i < TASK_COUNT; i++){
			if(taskArray[i].task_id == 2){
				taskArray[i].deadline = nextJobReleaseTime+pdMS_TO_TICKS(PERIOD_PRESSURE);
				printf("Next Pressure Job's Deadline will be : %d\n",taskArray[i].deadline);
				break;
			}
		}
		vTaskDelayUntil(&pressureLastWakeTime,pdMS_TO_TICKS(PERIOD_PRESSURE));
	}
}

void generateHeightTask(void * p){
	while(1){
		TickType_t nextJobReleaseTime = heightLastWakeTime + pdMS_TO_TICKS(PERIOD_HEIGHT);
		printf("Next Job of Height will be released at : %d\n",nextJobReleaseTime);

		int height = getHeight();
		printf("Height is : %d , at tick count : %d \n",height, xTaskGetTickCount());
		fflush(stdout);
		for(int i = 0 ; i < TASK_COUNT; i++){
			if(taskArray[i].task_id == 3){
				taskArray[i].deadline = nextJobReleaseTime+ pdMS_TO_TICKS(PERIOD_HEIGHT);
				printf("Next Height Job's Deadline will be : %d\n",taskArray[i].deadline);
				break;
			}
		}
		vTaskDelayUntil(&heightLastWakeTime,pdMS_TO_TICKS(PERIOD_HEIGHT));
	}
}


void EDFSchedulor(TimerHandle_t xTimer){
	vScheduleEDF(xTimer, deadlineHeap);
}

void main_assignment( void ){
	TaskHandle_t taskTemperatureHandle = NULL;
	TaskHandle_t taskPressureHandle = NULL;
	TaskHandle_t taskHeightHandle = NULL;
	TimerHandle_t softwareTimer = NULL;
	
	taskArray = (Task *)calloc(TASK_COUNT,sizeof(Task));

	softwareTimer = xTimerCreate("EDF_TIMER", 1, pdTRUE, 0, EDFSchedulor);

	xTimerStart(softwareTimer,0);

	xTaskCreate(generateTemperatureTask, "temperature", 200, (void *)0, tskIDLE_PRIORITY+1, &taskTemperatureHandle);
	xTaskCreate(generatePressureTask, "pressure", 200, (void *)0, tskIDLE_PRIORITY+1, &taskPressureHandle);
	xTaskCreate(generateHeightTask, "height", 200, (void *)0, tskIDLE_PRIORITY+1, &taskHeightHandle);

	printf("At tick count : %d\n",xTaskGetTickCount());
	taskArray[0].task_id = 1;
	taskArray[0].period = PERIOD_TEMPERATURE;
	taskArray[0].priority = PRIORITY_TEMPERATURE;
	taskArray[0].deadline = pdMS_TO_TICKS(PERIOD_TEMPERATURE);
	taskArray[0].task_handle = taskTemperatureHandle;
	taskArray[0].releaseTime = temperatureLastWakeTime;

	taskArray[1].task_id = 2;
	taskArray[1].period = PERIOD_PRESSURE;
	taskArray[1].priority = PRIORITY_PRESSURE;
	taskArray[1].deadline = pdMS_TO_TICKS(PERIOD_PRESSURE);
	taskArray[1].task_handle = taskPressureHandle;
	taskArray[1].releaseTime = heightLastWakeTime;

	taskArray[2].task_id = 3;
	taskArray[2].period = PERIOD_HEIGHT;
	taskArray[2].priority = PRIORITY_HEIGHT;
	taskArray[2].deadline = pdMS_TO_TICKS(PERIOD_HEIGHT);
	taskArray[2].task_handle = taskHeightHandle;
	taskArray[2].releaseTime = pressureLastWakeTime;

	for(int i=0; i<TASK_COUNT; i++){
		taskArray[i].timeExecuted = 0;
	}

	initMinHeap(&deadlineHeap);
	for(int i=0; i<3; i++){
		insertKey(&deadlineHeap,taskArray[i]);
	}


	for(int i = 0; i<3;i++){
		printf("Task_id : %d\n",taskArray[i].task_id);
		fflush(stdout);
	}

	printf("\nUsing EDF to schedule\n");

	vTaskStartScheduler();
}
