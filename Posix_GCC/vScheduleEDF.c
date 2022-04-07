#include <stdio.h>
#include <stdlib.h>
#include "freeRTOS.h"
#include "task.h"
#include "timers.h"
#include "vectorTask.h"
#include "heap.h"

void vScheduleEDF(TimerHandle_t xTimer, MinHeap deadlineHeap){
	// The maximum possible task priority is configMAX_PRIORITIES - 1
	vTaskPrioritySet(getMin(&deadlineHeap)->task_id, configMAX_PRIORITIES-1);

	printf("~~~~~~~~~~\n");

	printf("At tick count : %d \n",xTaskGetTickCount());

	printf("The task with the minimum deadline is and maximum priority is: %d\n",getMin(&deadlineHeap));
}