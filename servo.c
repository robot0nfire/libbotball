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

int servo_get_seek_time(unsigned int currentPosition, unsigned int finalPosition) {
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

    set_servo_position(port, position);
    msleep(500);
    printf("%d\n", servo_get_seek_time(oldPos, position));

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
            ssp(port, currentPosition);
            msleep(sleep);
        }
    } else {
        while(position != currentPosition){
            currentPosition = ((currentPosition - stepsize) < position) ? position : (currentPosition - stepsize);
            ssp(port, currentPosition);
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

    ssp(port1, pos1);
    ssp(port2, pos2);
    msleep(300);

    printf("Moved servoA to position: %d\n", get_servo_position(port1));
    printf("Moved servoB to position: %d\n", get_servo_position(port2));
}

void ssp_stepwise_asym(unsigned int port1, unsigned int port2, unsigned int position, unsigned int stepsize, unsigned int sleep) {
    if(position > servoMaxTicks) {
        position = servoMaxTicks;
    } else if(position < servoMinTicks) {
        position = servoMinTicks;
    }

    int pos1 = position;
    int pos2 = servoMaxTicks - position;

    wait_for_servo(port1);
    wait_for_servo(port2);

    ssp_stepwise(port1, pos1, stepsize, sleep);
    ssp_stepwise(port2, pos2, stepsize, sleep);
    msleep(300);

    printf("Moved servoA to position: %d\n", get_servo_position(port1));
    printf("Moved servoB to position: %d\n", get_servo_position(port2));
}

void setServo0(unsigned int stepsize, unsigned int sleep) {
    printf("Move Servo 0 to %d", servoProperties[0][1]);

    if(servoProperties[0][2] == -1 || servoProperties[0][3] == -1)
        ssp(0, *servoProperties[1]);
    else
        ssp_stepwise(0, *servoProperties[1], *servoProperties[2], *servoProperties[3]);

    servoProperties[0][0] = 0;
}

void setServo1(unsigned int stepsize, unsigned int sleep) {
    printf("Move Servo 1 to %d", servoProperties[1][1]);

    if(servoProperties[1][2] == -1 || servoProperties[1][3] == -1)
        ssp(1, *servoProperties[1]);
    else
        ssp_stepwise(1, *servoProperties[1], *servoProperties[2], *servoProperties[3]);

    servoProperties[1][0] = 0;
}

void setServo2(unsigned int stepsize, unsigned int sleep) {
    printf("Move Servo 2 to %d", servoProperties[2][1]);

    if(servoProperties[2][2] == -1 || servoProperties[2][3] == -1)
        ssp(2, *servoProperties[1]);
    else
        ssp_stepwise(2, *servoProperties[1], *servoProperties[2], *servoProperties[3]);

    servoProperties[2][0] = 0;
}

void setServo3(unsigned int stepsize, unsigned int sleep) {
    printf("Move Servo 3 to %d", servoProperties[3][1]);

    if(servoProperties[3][2] == -1 || servoProperties[3][3] == -1)
        ssp(3, *servoProperties[1]);
    else
        ssp_stepwise(3, *servoProperties[1], *servoProperties[2], *servoProperties[3]);

    servoProperties[3][0] = 0;
}

void ssp_async(unsigned int port, unsigned int position) {
    if(position > servoMaxTicks) {
        position = servoMaxTicks;
    } else if(position < servoMinTicks) {
        position = servoMinTicks;
    }

    wait_for_servo(port);

    servoProperties[port][0] = 1;
    servoProperties[port][1] = position;
    servoProperties[port][2] = -1;
    servoProperties[port][3] = -1;

    thread run;

    if(port == 0){
        run = thread_create(setServo0);
    } else if(port == 1) {
        run = thread_create(setServo1);
    } else if(port == 2) {
        run = thread_create(setServo2);
    } else if(port == 3) {
        run = thread_create(setServo3);
    }

    thread_start(run);
    printf("Started Servo thread\n");
}

void ssp_stepwise_async(unsigned int port, unsigned int position, unsigned int stepsize, unsigned int sleep) {
    if(position > servoMaxTicks) {
        position = servoMaxTicks;
    } else if(position < servoMinTicks) {
        position = servoMinTicks;
    }

    wait_for_servo(port);

    servoProperties[port][0] = 1;
    servoProperties[port][1] = position;
    servoProperties[port][2] = stepsize;
    servoProperties[port][3] = sleep;

    thread run;

    if(port == 0){
        run = thread_create(setServo0);
    } else if(port == 1) {
        run = thread_create(setServo1);
    } else if(port == 2) {
        run = thread_create(setServo2);
    } else if(port == 3) {
        run = thread_create(setServo3);
    }

    thread_start(run);
    printf("Started Servo thread\n");
}

void ssp_asym_async(unsigned int port1, unsigned int port2, unsigned int position) {
    wait_for_servo(port1);
    wait_for_servo(port2);

    if(position > servoMaxTicks) {
        position = servoMaxTicks;
    } else if(position < servoMinTicks) {
        position = servoMinTicks;
    }

    int pos1 = position;
    int pos2 = servoMaxTicks - position;

    servoProperties[port1][0] = 1;
    servoProperties[port1][1] = pos1;
    servoProperties[port1][2] = -1;
    servoProperties[port1][3] = -1;

    servoProperties[port2][0] = 1;
    servoProperties[port2][1] = pos2;
    servoProperties[port2][2] = -1;
    servoProperties[port2][3] = -1;

    thread run1;
    thread run2;

    if(port1 == 0){
        run1 = thread_create(setServo0);
    } else if(port1 == 1) {
        run1 = thread_create(setServo1);
    } else if(port1 == 2) {
        run1 = thread_create(setServo2);
    } else if(port1 == 3) {
        run1 = thread_create(setServo3);
    }

    if(port2 == 0){
        run2 = thread_create(setServo0);
    } else if(port2 == 1) {
        run2 = thread_create(setServo1);
    } else if(port2 == 2) {
        run2 = thread_create(setServo2);
    } else if(port2 == 3) {
        run2 = thread_create(setServo3);
    }

    thread_start(run1);
    thread_start(run2);

    printf("Started Servo threads\n");
}

void ssp_stepwise_asym_async(unsigned int port1, unsigned int port2, unsigned int position, unsigned int stepsize, unsigned int sleep) {
    wait_for_servo(port1);
    wait_for_servo(port2);

    if(position > servoMaxTicks) {
        position = servoMaxTicks;
    } else if(position < servoMinTicks) {
        position = servoMinTicks;
    }

    int pos1 = position;
    int pos2 = servoMaxTicks - position;

    servoProperties[port1][0] = 1;
    servoProperties[port1][1] = pos1;
    servoProperties[port1][2] = stepsize;
    servoProperties[port1][3] = sleep;

    servoProperties[port2][0] = 1;
    servoProperties[port2][1] = pos2;
    servoProperties[port2][2] = stepsize;
    servoProperties[port2][3] = sleep;

    thread run1;
    thread run2;

    if(port1 == 0){
        run1 = thread_create(setServo0);
    } else if(port1 == 1) {
        run1 = thread_create(setServo1);
    } else if(port1 == 2) {
        run1 = thread_create(setServo2);
    } else if(port1 == 3) {
        run1 = thread_create(setServo3);
    }

    if(port2 == 0){
        run2 = thread_create(setServo0);
    } else if(port2 == 1) {
        run2 = thread_create(setServo1);
    } else if(port2 == 2) {
        run2 = thread_create(setServo2);
    } else if(port2 == 3) {
        run2 = thread_create(setServo3);
    }

    thread_start(run1);
    thread_start(run2);

    printf("Started Servo threads\n");
}
