#include "heap.h"

void initMinHeap(MinHeap* heap)
{
	// heap->heapSize = 0;
	vectorTaskInit(&(heap->arr));
}

int insertKey(MinHeap* heap, Task newTask)
{
	vectorTaskPushback(&(heap->arr), newTask);
	int index = vectorTaskSize(&(heap->arr)) - 1;

	while (index != 0 && vectorTaskGet(&(heap->arr), parent(index))->deadline > vectorTaskGet(&(heap->arr), index )->deadline)
	{
		swapElements(heap, index, parent(index));
		index = parent(index);
	}
	return 0;
}

void changeKeyValue(MinHeap* heap, int index, Task newTask)
{
	vectorTaskSet(&(heap->arr), index, newTask);
	while (index != 0 && vectorTaskGet(&(heap->arr), parent(index))->deadline > vectorTaskGet(&(heap->arr), index)->deadline)
	{
		swapElements(heap, index, parent(index));
		index = parent(index);
	}
}

Task* getMin(MinHeap* heap){
	return vectorTaskGet(&(heap->arr), 0);
}

void deleteKey(MinHeap* heap, int index)
{
	vectorTaskSet(&(heap->arr), index, *vectorTaskGet(&(heap->arr), vectorTaskSize(&(heap->arr)) - 1));
	vectorTaskPopback(&(heap->arr));
	MinHeapify(heap, index);
}

void MinHeapify(MinHeap* heap, int index)
{
	int smallest = index;
	int l = left(index);
	int r = right(index);
	if(l < vectorTaskSize(&(heap->arr)) && vectorTaskGet(&(heap->arr), l)->deadline < vectorTaskGet(&(heap->arr), smallest)->deadline)
	{
		smallest = l;
	}
	if(r < vectorTaskSize(&(heap->arr)) && vectorTaskGet(&(heap->arr), r)->deadline < vectorTaskGet(&(heap->arr), smallest)->deadline){
		smallest = r;
	}
	if (smallest != index)
	{
		swapElements(heap, index, smallest);
		MinHeapify(heap, smallest);
	}
}

void swapElements(MinHeap* heap, int x, int y)
{
	Task* temp = vectorTaskGet(&(heap->arr), x);
	vectorTaskSet(&(heap->arr), x, *vectorTaskGet(&(heap->arr), y));
	vectorTaskSet(&(heap->arr), y, *temp);
}