#include "vectorTask.h"

void vectorTaskInit(vectorTask *v)
{
	//Initialize the vectorTask
	v->capacity = VECTOR_INIT_CAPACITY;
	
	v->totalSize = 0;
	v->elements = malloc(sizeof(Task) * v->capacity);
}

int vectorTaskSet(vectorTask *v, int index, Task element)
{
	int status = INIT_CODE;
	if(v)
	{
		if ((index >= 0) && (index < v->totalSize))
		{
			v->elements[index] = element;
			status = SUCCESS_CODE;
		}
	}
	return status;
}

Task* vectorTaskGet(vectorTask *v, int index)
{
	if(v)
	{
		if ((index >= 0) && (index < v->totalSize))
		{
			return &(v->elements[index]);
		}
	}
	return NULL;
}

int vectorTaskPushback(vectorTask *v, Task element)
{
	int status = INIT_CODE;
	if(v)
	{
		if (v->capacity == v->totalSize)
		{
			status = vectorTaskResize(v, v->capacity * VECTOR_GROWTH_FACTOR);
			if(status != INIT_CODE)
			{
				v->elements[v->totalSize++] = element;
			}
		}
		else
		{
			v->elements[v->totalSize++] = element;
			status = SUCCESS_CODE;
		}
	}
	return status;
}

/*
	* Function to pop the element from the end of a vectorTask.
	* Returns 0 on success, -1 on failure.
*/
int (vectorTaskPopback)(vectorTask *v){
	int status = INIT_CODE;
	if(v)
	{
		if (v->totalSize > 0)
		{
			v->totalSize--;
			status = SUCCESS_CODE;
		}
	}
	return status;
}

int vectorTaskSize(vectorTask *v)
{
	int totalCount = INIT_CODE;
	if(v)
	{
		totalCount = v->totalSize;
	}
	return totalCount;
}

int vectorTaskResize(vectorTask *v, int capacity)
{
	int status = INIT_CODE;
	if(v)
	{
		Task* elements = realloc(v->elements, sizeof(Task) * capacity);
		if (elements)
		{
			v->elements = elements;
			v->capacity = capacity;
			status = SUCCESS_CODE;
		}
	}
	return status;
}

int vectorTaskDelete(vectorTask *v, int index)
{
	int status = INIT_CODE;
	int i = 0;
	if(v)
	{
		if ((index < 0) || (index >= v->totalSize))
			return status;
		for (i = index; (i < v->totalSize - 1); ++i)
		{
			v->elements[i] = v->elements[i + 1];
		}
		v->totalSize--;
		if ((v->totalSize > 0) && ((v->totalSize) == (v->capacity / VECTOR_SHRINK_THRESHOLD)))
		{
			vectorTaskResize(v, v->capacity / VECTOR_SHRINK_FACTOR);
		}
		status = SUCCESS_CODE;
	}
	return status;
}

int vectorTaskFree(vectorTask *v)
{
	int status = INIT_CODE;
	if(v)
	{
		free(v->elements);
		v->elements = NULL;
		status = SUCCESS_CODE;
	}
	return status;
}

int vectorTaskDeadline(vectorTask *v, int index){
	return v->elements[index].deadline;
}
