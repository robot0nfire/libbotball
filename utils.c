/**
* @file utils.c
* @brief This file provides utility functions
*
* @author Nico Kratky
*
* @date 17/2/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include "include/utils.h"
#include "include/ports.h"

unsigned long start_time;

int float_close(float a, float b, float abs_tol) {
    float rel_tol = 0.00001;

    if(abs(a - b) <= MAX(rel_tol * MAX(abs(a), abs(b)), abs_tol))
        return 1;
    return 0;
}


void start() {
    int light = 0;

    start_time = systime();

    printf("Press Button once to start with light, otherwise will start on button press\n");
    while(((unsigned long) (start_time + 500.0)) > systime()) {
        if(digital(RIGHT_BUTTON) == 1) {
            light = 1;
            break;
        }
        msleep(1);
    }

    if(light == 1) {
        printf("Starting with light\n");
        msleep(500);
        wait_for_light(LIGHT_SENSOR);
        start_time = systime();
        printf("Let's Go!\n");
    }
    else {
        printf("Starting on button press\nWaiting for input...\n");
        while(!digital(RIGHT_BUTTON)) msleep(1);
        start_time = systime();
        printf("Let's Go!\n");
    }
}

unsigned long get_time() {
    return (unsigned long)(systime() - start_time);
}
