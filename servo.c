/**
* @file servo.c
* @brief This file provides functions to interact with the Botball servos.
*
* @author Nico Kratky
*
* @date 27/1/2017
*/

#include <kipr/botball.h>
#include "include/servo.h"

/**
* @brief Stepsize for moving the servo asyncronously
* Season specific parameter for moving servos asynchronously
*/
#define servoTickSize 10
/**
* @brief Sleep for moving the servo asyncronously
* Season specific parameter for moving servos asynchronously
*/
#define servoSleep 17
/**
* @brief Shorter sleep for moving the servo asyncronously
* Season specific parameter for moving servos asynchronously
*/
#define servoSleepShort 10

void servo_get_seek_time(unsigned int currentPosition, unsigned int finalPosition) {
    int ticks_to_move = (currentPosition > finalPosition)? currentPosition - finalPosition : finalPosition - currentPosition;

    return (int)(((ticks_to_move * degreesPerTick * timePerDegree) / calcDivisor) / calcDivisor);
}

void ssp(unsigned int port, unsigned int position) {
    int oldPos = get_servo_position(port);

    if(position > servoMaxTicks) {
        position = servoMaxTicks;
    } else if(position < servoMinTicks) {
        position = servoMinTicks;
    }

    set_servo_position(servo, position);
    msleep(servo_get_seek_time(oldPos, position));

    printf("Moved servo to position: %d\n", get_servo_position(port));
}

void ssp_stepwise(unsigned int port, unsigned int position, unsigned int stepsize, unsigned int sleep) {
    if(position > servoMaxTicks) {
        position = servoMaxTicks;
    } else if(position < servoMinTicks) {
        position = servoMinTicks;
    }

    int currentPosition = get_servo_position(port);

    if(position == currentPosition) { return; }

    if(position > currentPosition) {
        while(position != currentPosition) {
            currentPosition = ((currentPosition + stepsize) > position) ? position : (currentPosition + stepsize);
            set_servo_position(port, currentPosition);
            msleep(sleep);
        }
    } else {
        while(position != currentPosition){
            currentPosition = ((currentPosition - stepsize) < position) ? position : (currentPosition - stepsize);
            set_servo_position(port, currentPosition);
            msleep(sleep);
        }
    }
}

void ssp_asym(unsigned int port1, unsigned int port2, unsigned int position) {
    if(position > servoMaxTicks) {
        position = servoMaxTicks;
    } else if(position < servoMinTicks) {
        position = servoMinTicks;
    }

    int pos1 = position;
    int pos2 = servoMaxTicks - position;

    wait_for_servo(port1);
    wait_for_servo(port2);

    set_servo_position(port1, pos1);
    set_servo_position(port2, pos2);
    msleep(300);

    printf("Moved servoA to position: %d\n", get_servo_position(port1));
    printf("Moved servoB to position: %d\n", get_servo_position(port2));
}

void setServo0(){
    printf("Move Servo 0 to %d", servoPositions[0]);
    ssp_stepwise(0, servoPositions[0], servoTickSize, servoSleep);
    servoBlocked[0] = 0;
}

void setServo1(){
    printf("Move Servo 1 to %d", servoPositions[1]);
    ssp_stepwise(1, servoPositions[1], servoTickSize, servoSleep);
    servoBlocked[1] = 0;
}

void setServo2(){
    printf("Move Servo 2 to %d", servoPositions[2]);
    ssp_stepwise(2, servoPositions[2], servoTickSize, servoSleepShort);
    servoBlocked[2] = 0;
}

void setServo3(){
    printf("Move Servo 3 to %d", servoPositions[3]);
    ssp_stepwise(3, servoPositions[3], servoTickSize, servoSleep);
    servoBlocked[3] = 0;
}

void ssp_async(unsigned int port, unsigned int position) {
    wait_for_servo(port);

    servoBlocked[port] = 1;
    servoPositions[port] = position;

    thread run;
    if(servo == 0){
        run = thread_create(setServo0);
    } else if(servo == 1){
        run = thread_create(setServo1);
    } else if(servo == 2){
        run = thread_create(setServo2);
    } else if(servo == 3){
        run = thread_create(setServo3);
    }

    thread_start(run);
    printf("Started Servo thread\n");
}
