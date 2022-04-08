# FreeRTOS-EDF-API
Implements EDF Algorithm for FreeRTOS Scheduler by setting the priority of the nearest deadline task to max priority. Internally uses a heap and self adjusting vector of jobs for dynamic handling of new jobs. The initial size and resizing paramaters for the vector can be changed in vectorTask.h

## Requirements
FreeRTOS 202112.00
Version as tested: FreeRTOS 202112.00

gprof
Version as tested: GNU gprof (GNU Binutils) 2.36

make
Version as tested: GNU Make 3.82

gcc
Version as tested: gcc (GCC) 11.0.0


## How to compile:
1) Go to {FreeRTOS}/FreeRTOS/Demo/Posix_GCC and change main.c to run main_assignment.c instead of main_blinky.c (Add extern void main_assignment)
2) Run makefile

## Structure of the program:
1) API.c and API.h are API for three tasks which we'll use to test the algorithm
2) heap.c and heap.h implement the heap
3) vectorTask.c and vectorTask.h are implementations of vector which are used by the heap
4) vScheduleEDF.c is the actual implementation of EDF. Since we've implemented a dynamic heap already, the algorithm is very easy and efficient
5) The other files are FreeRTOS's standard files

At each decision point, vScheduleEDF is called and it sets the nearest deadline first to the highest priority 
We then call FreeRTOS's priority based schedulor, hence implementing EDF schedulor using the inbuilt schedulor by playing with the priorities
