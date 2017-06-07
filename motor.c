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
#include "math.h"

void drive_direct(const short velocity_l, const short velocity_r) {
    mav(LEFT_MOTOR_DRIVE, -velocity_l);
    mav(RIGHT_MOTOR_DRIVE, velocity_r);
}

void drive_straight(const short velocity, const short ms) {
    mav(LEFT_MOTOR_DRIVE, -velocity);
    mav(RIGHT_MOTOR_DRIVE, velocity);

    msleep(ms);

    freeze(LEFT_MOTOR_DRIVE);
    freeze(RIGHT_MOTOR_DRIVE);
}

void drive_distance(short velocity, const short distance) {
    msleep(100);
    cmpc(LEFT_MOTOR_DRIVE);
    cmpc(RIGHT_MOTOR_DRIVE);

    velocity *= -1;

    int abs_distance = abs(distance);

    int leftTicks = (float) ((float) abs_distance / (float) WHEELPERIMETER) * (float) LEFTTICKS;
    int rightTicks = (float) ((float) abs_distance / (float) WHEELPERIMETER) * (float) RIGHTTICKS;

    int mean;
    float error;

    int left_speed = velocity, right_speed = velocity;

    int diff = abs(LEFTTICKS - RIGHTTICKS);

    if (LEFTTICKS > RIGHTTICKS) {
        mean = LEFTTICKS - (diff / 2);
        error = (diff / 1.0f) / mean;
        left_speed = velocity - (velocity * error);
    }
    else {
        mean = RIGHTTICKS - (diff / 2);
        error = (diff / 1.0f) / mean;
        right_speed = velocity - (velocity * error);
    }

    if (distance < 0) {
        left_speed *= -1;
    }
    else {
        right_speed *= -1;
    }

    mav(LEFT_MOTOR_DRIVE, left_speed);
    mav(RIGHT_MOTOR_DRIVE, right_speed);

    printf("Driving at velocity %d for %d mm\n", velocity, distance);
    printf("---- Left Ticks: %d, Right Ticks: %d, Left Speed: %d, Right Speed: %d\n", leftTicks, rightTicks, left_speed, right_speed);

    int mpl = abs(gmpc(LEFT_MOTOR_DRIVE)), mpr = abs(gmpc(RIGHT_MOTOR_DRIVE));
    while(mpr < rightTicks && mpl < leftTicks) {
        if(abs(mpl - mpr) > 50) {
            if(mpl > mpr) {
                mav(LEFT_MOTOR_DRIVE, left_speed*0.95);
            }
            else {
                mav(RIGHT_MOTOR_DRIVE, right_speed*0.95);
            }
        }
        else {
            mav(LEFT_MOTOR_DRIVE, left_speed);
            mav(RIGHT_MOTOR_DRIVE, right_speed);
            msleep(1);
        }
        mpl = abs(gmpc(LEFT_MOTOR_DRIVE));
        mpr = abs(gmpc(RIGHT_MOTOR_DRIVE));
    }

    freeze(LEFT_MOTOR_DRIVE);
    freeze(RIGHT_MOTOR_DRIVE);

    printf("---- Stopped! Left Ticks %d, Right Ticks: %d\n", abs(gmpc(LEFT_MOTOR_DRIVE)), abs(gmpc(RIGHT_MOTOR_DRIVE)));
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

void turn(short velocity, const short deg) {

    msleep(200); // important!
    clear_motor_position_counter(RIGHT_MOTOR_DRIVE);
    clear_motor_position_counter(LEFT_MOTOR_DRIVE);

    printf("Turning %d degrees\n", deg);
    printf("Motor %d starting ticks: %d\n", RIGHT_MOTOR_DRIVE, get_motor_position_counter(RIGHT_MOTOR_DRIVE));
    printf("Motor %d starting ticks: %d\n", LEFT_MOTOR_DRIVE, get_motor_position_counter(LEFT_MOTOR_DRIVE));

    int ticks = ((1010.0 + (0.1667 * abs(deg))) / 90.0) * deg;
    printf("Ticks to be turned: %d\n", ticks);

    if(ticks < 0) velocity *= -1;

    mav(RIGHT_MOTOR_DRIVE, velocity);
    mav(LEFT_MOTOR_DRIVE, velocity);

    if (deg > 0)
        while (get_motor_position_counter(RIGHT_MOTOR_DRIVE) < ticks && get_motor_position_counter(LEFT_MOTOR_DRIVE) < ticks) msleep(5);
    else
        while (get_motor_position_counter(RIGHT_MOTOR_DRIVE) > ticks && get_motor_position_counter(LEFT_MOTOR_DRIVE) > ticks) msleep(5);

    /* need this hack because the wallaby is a stupid fuck */
    if (abs(get_motor_position_counter(LEFT_MOTOR_DRIVE)) < 50) {
        freeze(RIGHT_MOTOR_DRIVE);
        mav(LEFT_MOTOR_DRIVE, velocity);

        if (deg > 0)
            while (get_motor_position_counter(LEFT_MOTOR_DRIVE) < ticks) msleep(5);
        else
            while (get_motor_position_counter(LEFT_MOTOR_DRIVE) > ticks) msleep(5);
    }

    if (abs(get_motor_position_counter(RIGHT_MOTOR_DRIVE)) < 50) {
        freeze(LEFT_MOTOR_DRIVE);
        mav(RIGHT_MOTOR_DRIVE, velocity);

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

void moveMotor0() {
    printf("Move Motor 0 at %d\n", motorProperties[0][1]);

    mav(0, motorProperties[0][1]);

    if(motorProperties[0][2] != -1) {
        msleep(motorProperties[0][2]);
        freeze(0);
    }

    motorProperties[0][0] = 0;
    motorProperties[0][2] = -1;

    printf("Finished Motor 0\n");
}

void moveMotor1() {
    printf("Move Motor 1 at %d\n", motorProperties[1][1]);

    mav(1, motorProperties[1][1]);

    if(motorProperties[1][2] != -1) {
        msleep(motorProperties[1][2]);
        freeze(1);
    }

    motorProperties[1][0] = 0;
    motorProperties[1][2] = -1;

    printf("Finished Motor 1\n");
}

void moveMotor2() {
    printf("Move Motor 2 at %d\n", motorProperties[2][1]);

    mav(2, motorProperties[2][1]);

    if(motorProperties[2][2] != -1) {
        msleep(motorProperties[2][2]);
        freeze(2);
    }

    motorProperties[2][0] = 0;
    motorProperties[2][2] = -1;

    printf("Finished Motor 2\n");
}

void moveMotor3() {
    printf("Move Motor 3 at %d\n", motorProperties[3][1]);

    mav(3, motorProperties[3][1]);

    if(motorProperties[3][2] != -1) {
        msleep(motorProperties[3][2]);
        freeze(3);
    }

    motorProperties[3][0] = 0;
    motorProperties[3][2] = -1;

    printf("Finished Motor 3\n");
}

void mav_async(const short port, const short velocity) {
    wait_for_motor(port);

    motorProperties[port][0] = 1;
    motorProperties[port][1] = velocity;

    thread run;

    if(port == 0){
        run = thread_create(moveMotor0);
    } else if(port == 1) {
        run = thread_create(moveMotor1);
    } else if(port == 2) {
        run = thread_create(moveMotor2);
    } else if(port == 3) {
        run = thread_create(moveMotor3);
    }

    thread_start(run);
    printf("Started motor thread\n");
}


void mav_async_time(const short port, const short velocity, const short ms) {
    wait_for_motor(port);

    motorProperties[port][0] = 1;
    motorProperties[port][1] = velocity;
    motorProperties[port][2] = ms;

    thread run;

    if(port == 0){
        run = thread_create(moveMotor0);
    } else if(port == 1) {
        run = thread_create(moveMotor1);
    } else if(port == 2) {
        run = thread_create(moveMotor2);
    } else if(port == 3) {
        run = thread_create(moveMotor3);
    }

    thread_start(run);
    printf("Started motor thread\n");
}

void mav_time(const short port, const short velocity, const short ms) {
    mav(port, velocity);
    msleep(ms);
    freeze(port);
}
