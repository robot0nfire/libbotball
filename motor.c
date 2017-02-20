/**
* @file motor.c
* @brief This file provides functions to interact with the Botball motors.
*
* @author Nico Kratky
*
* @date 2/2/2017
*/

#include <kipr/botball.h>
#include "include/motor.h"

void drive_direct(const short velocity_l, const short velocity_r) {
    mav(LEFT_MOTOR_DRIVE, velocity_l);
    mav(RIGHT_MOTOR_DRIVE, -velocity_r);
}

void drive_straight(const short velocity, const short ms) {
    mav(LEFT_MOTOR_DRIVE, velocity);
    mav(RIGHT_MOTOR_DRIVE, -velocity);

    msleep(ms);

    freeze(LEFT_MOTOR_DRIVE);
    freeze(RIGHT_MOTOR_DRIVE);
}

void drive(const short velocity_l, int velocity_r, const int ms) {
    drive_direct(velocity_l, velocity_r);
    msleep(ms);
    freeze(LEFT_MOTOR_DRIVE);
    freeze(RIGHT_MOTOR_DRIVE);
}

void follow_line(const int ms) {
    float end_time = seconds() + (ms / 1000);

    while (seconds() < end_time) {
        if ((analog(TOPHAT_RIGHT) < THRESHOLD) && (analog(TOPHAT_LEFT) > THRESHOLD))
            drive(500, 1500, 10);
        else if ((analog(TOPHAT_LEFT) < THRESHOLD) && (analog(TOPHAT_RIGHT) > THRESHOLD))
            drive(1500, 500, 10);
        else
            drive(1500, 1500, 10);
    }
}

void smp(int port, const short velocity, const short position) {
    if(position < get_motor_position_counter(port))
        mtp(port, -velocity, position);
    else
        mtp(port, velocity, position);
    msleep(300);
    while(!get_motor_done(port))
        msleep(1);
    freeze(port);
}
