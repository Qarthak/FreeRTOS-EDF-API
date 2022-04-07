#include <API.h>
#include <stdio.h>
#include <stdlib.h>
#include "freeRTOS.h"
#include "task.h"
#include "timers.h"

int getTemperature()
{
	srand(xTaskGetTickCount());
	return temperature = (rand() % 81) + 10;
}

int getPressure()
{
	srand(xTaskGetTickCount());
	return pressure = (rand() % 7) + 2;
}

int getHeight()
{
	srand(xTaskGetTickCount());
	return height = (rand() % 901) + 100;
}