#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "freeRTOS.h"
#include "task.h"
#include "timers.h"
#include "vectorTask.h"


// A class for Min Heap
struct MinHeap
{
	// int *arr;
	vectorTask *arr; // vector of elements in heap
	// int heapSize; // Current number of elements in min heap
};

typedef struct MinHeap MinHeap;

//Swaps the elements at the two indices of the heap
void swapElements(MinHeap* heap, int x, int y);

//Initialize the heap
void initMinHeap(MinHeap* heap);

// to heapify a subtree with the root at given index
void MinHeapify(MinHeap* heap, int );

// to get the parent of a certain node
int parent(int i) { return (i-1)/2; }

// to get index of left child of node at index i
int left(int i) { return (2*i + 1); }

// to get index of right child of node at index i
int right(int i) { return (2*i + 2); }

// Decreases value of key at index i
void changeKeyValue(MinHeap* heap, int i, Task newTask);

// Returns the minimum key (key at root) from min heap
Task* getMin(MinHeap* heap);

// Deletes a key stored at given index
void deleteKey(MinHeap* heap, int index);

// Inserts a new key 'k'
int insertKey(MinHeap* heap, Task k);