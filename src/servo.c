/**
* @file servo.c
* @brief This file provides functions to interact with the Botball servos.
*
* @author Nico Kratky
*
* @date 27/1/2017
*/

#include <kipr/botball.h>
#include "servo.h"

void ssp(short port, short position) {
    int oldPos = get_servo_position(port);

    if(position > servoMaxTicks) {
        position = servoMaxTicks;
    } else if(position < servoMinTicks) {
        position = servoMinTicks;
    }

    set_servo_position(port, position);
    msleep(300);

    printf("Moved servo to position: %d\n", get_servo_position(port));
}


void ssp_stepwise(short port, short position, int stepsize, int sleep) {
    if(position > servoMaxTicks) {
        position = servoMaxTicks;
    } else if(position < servoMinTicks) {
        position = servoMinTicks;
    }

    int currentPosition = get_servo_position(port);

    if(position == currentPosition) { return; }

    if(position > currentPosition) {
        while(position > currentPosition) {
            currentPosition = ((int) (currentPosition + stepsize) > position) ?
                              position : (currentPosition + stepsize);
            set_servo_position(port, currentPosition);
            msleep(sleep);
        }
    } else {
        while(position < currentPosition) {
            currentPosition = ((int) (currentPosition - stepsize) < position) ?
                              position : (currentPosition - stepsize);
            set_servo_position(port, currentPosition);
            msleep(sleep);
        }
    }

    printf("Moved servo to position: %d\n", get_servo_position(port));
}


void ssp_asym(short port1, short port2, short position) {
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


void ssp_stepwise_asym(short port1,
                       short port2,
                       short position,
                       int stepsize,
                       int sleep) {
    if(position > servoMaxTicks) {
        position = servoMaxTicks;
    } else if(position < servoMinTicks) {
        position = servoMinTicks;
    }

    int pos1 = position;
    int pos2 = servoMaxTicks - position;

    wait_for_servo(port1);
    wait_for_servo(port2);

    int currentPosition = get_servo_position(port1);

    if(position == currentPosition) { return; }

    if(position > currentPosition) {
        while(position > currentPosition) {
            currentPosition = ((int) (currentPosition + stepsize) > position) ?
                              position : (currentPosition + stepsize);
            set_servo_position(port1, currentPosition);
            set_servo_position(port2, servoMaxTicks - currentPosition);
            msleep(sleep);
           }
    } else {
           while(position < currentPosition) {
            currentPosition = ((int) (currentPosition - stepsize) < position) ?
                              position : (currentPosition - stepsize);
            set_servo_position(port1, currentPosition);
            set_servo_position(port2, servoMaxTicks - currentPosition);
            msleep(sleep);
        }
    }

    printf("Moved servoA to position: %d\n", get_servo_position(port1));
    printf("Moved servoB to position: %d\n", get_servo_position(port2));
}


void setServo0() {
    printf("Move Servo 0 to %d\n", servoProperties[0][1]);

    if(servoProperties[0][2] == -1 || servoProperties[0][3] == -1)
        ssp(0, servoProperties[0][1]);
    else
        ssp_stepwise(0, servoProperties[0][1], servoProperties[0][2],
                     servoProperties[0][3]);

    servoProperties[0][0] = 0;
}


void setServo1() {
    printf("Move Servo 1 to %d\n", servoProperties[1][1]);

    if(servoProperties[1][2] == -1 || servoProperties[1][3] == -1)
        ssp(1, servoProperties[1][1]);
    else
        ssp_stepwise(1, servoProperties[1][1], servoProperties[1][2],
                     servoProperties[1][3]);

    servoProperties[1][0] = 0;
}


void setServo2() {
    printf("Move Servo 2 to %d\n", servoProperties[2][1]);

    if(servoProperties[2][2] == -1 || servoProperties[2][3] == -1)
        ssp(2, servoProperties[2][1]);
    else
        ssp_stepwise(2, servoProperties[2][1], servoProperties[2][2],
                     servoProperties[2][3]);

    servoProperties[2][0] = 0;
}


void setServo3() {
    printf("Move Servo 3 to %d\n", servoProperties[3][1]);

    if(servoProperties[3][2] == -1 || servoProperties[3][3] == -1)
        ssp(3, servoProperties[3][1]);
    else
        ssp_stepwise(3, servoProperties[3][1], servoProperties[3][2],
                     servoProperties[3][3]);

    servoProperties[3][0] = 0;
}


void ssp_async(short port, short position) {
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


void ssp_stepwise_async(short port, short position, int stepsize, int sleep) {
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


void ssp_asym_async(short port1, short port2, short position) {
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


void ssp_stepwise_asym_async(short port1,
                             short port2,
                             short position,
                             int stepsize,
                             int sleep) {
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
