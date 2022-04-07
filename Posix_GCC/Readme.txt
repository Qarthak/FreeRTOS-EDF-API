Sarthak Chaudhary
I got a lot of advice from seniors. Also code is inspired by https://github.com/ESFree/ESFree

How to compile:
Go to {FreeRTOS}/FreeRTOS/Demo/Posix_GCC and change main.c to run main_assignment.c instead of main_blinky.c (Add extern void main_assignment( void ) and call it)
Run make

I'm getting error
ld: 7 duplicate symbols for architecture arm64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make: *** [build/posix_demo] Error 1
So I'm not sure it will run but I did fix all the errors it gave before showing this

Structure of program:
API.c and API.h are for part 1 and part 2
vScheduleEDF.c is for part 3
Didn't make a vScheduleEDF.h since it's a small file

Issues with program:
I couldn't find how to call EDF at the right times. I went with the example given in main_blinky.c and it might not right. It works by changing the priorities of the earliest deadline job to the highest priority and the inbuild schedulor is a priority based schedulor so EDF works, but the other jobs aren't sorted in order of their priority, since I've used a min-heap instead of a RBT. In case of RBT, I could've traversed in-order and changed all the priorities but that would've been not very efficient to do at each decision point. A RBT would've been asymotically just as good and also have given easy access to slightly lower priority jobs