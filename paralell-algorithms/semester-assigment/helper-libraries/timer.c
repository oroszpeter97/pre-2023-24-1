#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include "timer.h"

static double start_time = 0.0; /**< Start time of the timer. */
static double end_time = 0.0; /**< End time of the timer. */
static double elapsed_time = 0.0; /**< Elapsed time between start and stop of the timer. */
 
static bool clock_is_running = false; /**< Indicates whether the timer is currently running or not. */

void start_clock(){
    if(clock_is_running){
        printf("Cannot start clock, it is already running!");
        return;
    }
    clock_is_running = true;
    start_time = clock();
}

void stop_clock(){
    if(!clock_is_running){
        printf("Cannot stop clock, it is not running!");
        return;
    }
    clock_is_running = false;
    end_time = clock();
}

double get_elapsed_time(){
    if(end_time == 0){
        printf("There is not a valid timeframe to calcualte elapsed time!\n");
        return 0.0;
    }
    elapsed_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    start_time = 0.0;
    end_time = 0.0;
    return elapsed_time;
}