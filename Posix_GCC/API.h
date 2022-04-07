#pragma once
#include <stdio.h>
#include <stdlib.h>

/* 
 * This function returns a random integer between 10 and 90
 */
int getTemperature();

/* 
 * This function returns a random integer between 2 and 10
 */
int getPressure();

/* 
 * This function returns a random integer between 100 and 1000
 */
int getHeight();

// Units is millisecond, not ticks. Later converted to ticks using pdMS_TO_TICKS
#define PERIOD_TEMPERATURE		6
#define PRIORITY_TEMPERATURE	1

#define PERIOD_PRESSURE			5
#define PRIORITY_PRESSURE		2

#define PERIOD_HEIGHT			12
#define PRIORITY_HEIGHT			3