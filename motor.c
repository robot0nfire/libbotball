/**
* @file motor.c
* @brief This file provides functions to interact with the Botball motors.
*
* @author Nico Kratky
*
* @date 2/2/2017
*/

#include <kipr/botball.h>
#include "include/ports.h"
#include "include/motor.h"

void drive_direct(const short velocity_l, const short velocity_r) {
    mav(LEFT_MOTOR_DRIVE, velocity_l);
    mav(RIGHT_MOTOR_DRIVE, -velocity_r);
}

void drive_straight(const short velocity, const short ms) {
    mav(LEFT_MOTOR_DRIVE, (short)(velocity * 1.0));
    mav(RIGHT_MOTOR_DRIVE, (short)(velocity * -1.0));

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

void turn(const short velocity, const short deg) {

    msleep(100); // important!
    clear_motor_position_counter(RIGHT_MOTOR_DRIVE);
    clear_motor_position_counter(LEFT_MOTOR_DRIVE);

    printf("Turning %d degrees\n", deg);
    printf("Motor %d starting ticks: %d\n", RIGHT_MOTOR_DRIVE, get_motor_position_counter(RIGHT_MOTOR_DRIVE));
    printf("Motor %d starting ticks: %d\n", LEFT_MOTOR_DRIVE, get_motor_position_counter(LEFT_MOTOR_DRIVE));

    int ticks = ((900.0 + (0.1667 * abs(deg))) / 90.0) * deg;
    printf("Ticks to be turned: %d\n", ticks);

    move_to_position(RIGHT_MOTOR_DRIVE, velocity, ticks);
    move_to_position(LEFT_MOTOR_DRIVE, velocity, ticks);

    if (deg > 0)
        while (get_motor_position_counter(RIGHT_MOTOR_DRIVE) < ticks && get_motor_position_counter(LEFT_MOTOR_DRIVE) < ticks) msleep(5);
    else
        while (get_motor_position_counter(RIGHT_MOTOR_DRIVE) > ticks && get_motor_position_counter(LEFT_MOTOR_DRIVE) > ticks) msleep(5);

    /* need this hack because the wallaby is a stupid fuck */
    if (abs(get_motor_position_counter(LEFT_MOTOR_DRIVE)) < 50) {
        freeze(RIGHT_MOTOR_DRIVE);
        move_to_position(LEFT_MOTOR_DRIVE, velocity, ticks);

        if (deg > 0)
            while (get_motor_position_counter(LEFT_MOTOR_DRIVE) < ticks) msleep(5);
        else
            while (get_motor_position_counter(LEFT_MOTOR_DRIVE) > ticks) msleep(5);
    }

    if (abs(get_motor_position_counter(RIGHT_MOTOR_DRIVE)) < 50) {
        freeze(LEFT_MOTOR_DRIVE);
        move_to_position(RIGHT_MOTOR_DRIVE, velocity, ticks);

        if (deg > 0)
            while (get_motor_position_counter(RIGHT_MOTOR_DRIVE) < ticks) msleep(5);
        else
            while (get_motor_position_counter(RIGHT_MOTOR_DRIVE) > ticks) msleep(5);
    }

    freeze(RIGHT_MOTOR_DRIVE);
    freeze(LEFT_MOTOR_DRIVE);

    printf("Motor %d end ticks: %d\n", RIGHT_MOTOR_DRIVE, get_motor_position_counter(RIGHT_MOTOR_DRIVE));
    printf("Motor %d end ticks: %d\n", LEFT_MOTOR_DRIVE, get_motor_position_counter(LEFT_MOTOR_DRIVE));
}
