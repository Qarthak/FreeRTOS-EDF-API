#ifndef VECTOR_H
#define VECTOR_H


#define VECTOR_INIT_CAPACITY 4
#define VECTOR_GROWTH_FACTOR 2
#define VECTOR_SHRINK_FACTOR 2
#define VECTOR_SHRINK_THRESHOLD 4
#define INIT_CODE -1
#define SUCCESS_CODE 0

#endif

#ifndef VECTOR_PJ_H
#define VECTOR_PJ_H

//Both of these are needed to define NULL. Newer versions can make do with either one
#include <stdio.h>
#include <stdlib.h>
#include "freeRTOS.h"
#include "task.h"
#include "timers.h"

// struct Task{
// 	int period;
// 	float executionTime;
// 	int relativeDeadline;
// 	int timesExecuted;
// 	float remainingExecutionTime;
// 	int absoluteDeadline;
// };
typedef struct _Task
{
	int task_id ;
	TickType_t releaseTime;
	TickType_t period;
	TickType_t deadline;
	TickType_t timeExecuted;
	TickType_t executionTime;
	UBaseType_t priority;
	TaskHandle_t task_handle;
};

typedef struct _Task Task;

struct vectorTask
{
	/*
	 * Pointer to the array of elements
	*/
	Task* elements;
	
	/*
	 * The total number of elements already stored in the array
	*/
	int totalSize;
	
	/*
	 * The number of elements that can be stored in the allocated space
	*/
	int capacity;
};

typedef struct vectorTask vectorTask;

/*
 * Function to initialize the vectorTask
*/
void vectorTaskInit(vectorTask *v);

/*
 * Function to get the deadline
*/
int vectorTaskDeadline(vectorTask *v, int index);

/*
	* Function to set the element at a particular index in the vectorTask.
	* Returns 0 on success, -1 on failure.
*/
int (vectorTaskSet)(vectorTask *v, int index, Task element);

/*
	* Function to get an element from the vectorTask.
	* Returns a pointer to the element on success, NULL on failure.
*/
Task* (vectorTaskGet)(vectorTask *v, int index);

/*
	* Function to push an element to the end of a vectorTask.
	* Returns 0 on success, -1 on failure.
*/
int (vectorTaskPushback)(vectorTask *v, Task element);

/*
	* Function to pop an element from the end of a vectorTask.
	* Returns 0 on success, -1 on failure.
*/
int (vectorTaskPopback)(vectorTask *v);

/*
	* Function to find size of a vectorTask.
	* Returns size of vectorTask if it's been initialized, -1 if it still points at NULL
*/
int (vectorTaskSize)(vectorTask *v);

/*
	* Function to resize the vectorTask.
	* Returns 0 on success, -1 on failure.
*/
int (vectorTaskResize)(vectorTask *v, int size);

/*
	* Function to delete an element from the vectorTask.
	* Returns 0 on success, -1 on failure.
*/
int (vectorTaskDelete)(vectorTask *v, int index);

/*
	* Function to free the vectorTask.
	* Returns 0 on success, -1 on failure.
*/
int (vectorTaskFree)(vectorTask *v);


#endif