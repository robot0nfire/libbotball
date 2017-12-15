/**
* @file servo.h
* @brief This file provides functions to interact with the Botball servos.
*
* @author Nico Kratky
*
* @date 30/1/2017
*/

#ifndef SERVO_H /* Include guard */
#define SERVO_H

/**
* @brief Minimum ticks to which servos should be moved
*/
#define servoMinTicks 0
/**
* @brief Maximum ticks to which servos should be moved
*/
#define servoMaxTicks 2047

/**
* @brief Properties Array for moving servos asynchronously.
* Dimensions represent the different servos
* 0: servo blocked status. 0 = not blocked; 1 = blocked
* 1: position to which the servo will be moved
* 2: stepsize which should be used to move the servo stepwise. If set to -1 the servo will be moved normally
* 3: sleep which should be used to move the servo stepwise. If set to -1 the servo will be moved normally
*/
static int servoProperties[4][4] = {
    {0, 0, -1, -1},
    {0, 0, -1, -1},
    {0, 0, -1, -1},
    {0, 0, -1, -1}
};

/**
* @brief Get status of servo
*
* @param servo Port to which the servo is connected
*/
static int is_blocked(short servo){
    return servoProperties[servo][0];
}


/**
* @brief Wait till servo has finished moving
*
* @param servo Port to which the servo is connected
*/
static void wait_for_servo(short servo){
    while(servoProperties[servo][0]){
        msleep(1);
    }
}


/**
* @brief Move the given servo to the given position
*
* @param port       The port at which the servo is connected to the wallaby
* @param position   The position to which the servo should be moved
*/
void ssp(short port, short position);


/**
* @brief Moves a servo with a given speed and given step size to it's destination
*
* @param port       The port at which the servo is connected to the wallaby
* @param position   The position to which the servo should be moved
* @param stepsize   How 'slow' the servo should be moved
* @param sleep      How long the servo sleeps in between steps
*/
void ssp_stepwise(short port, short position, int stepsize, int sleep);


/**
* @brief Move two given servos asymmetrically to the given position
*
* @param port1      The port at which the first servo is connected to the wallaby
* @param port2      The port at which the second servo is connected to the wallaby
* @param position   The position to which the servo should be moved
*/
void ssp_asym(short port1, short port2, short position);


/**
* @brief Move two given servos asymmetrically and stepwise to the given position
*
* @param port1      The port at which the first servo is connected to the wallaby
* @param port2      The port at which the second servo is connected to the wallaby
* @param position   The position to which the servo should be moved
* @param stepsize   How 'slow' the servos should be moved
* @param sleep      How long the servos sleep in between steps
*/
void ssp_stepwise_asym(short port1,
                       short port2,
                       short position,
                       int stepsize,
                       int sleep);


/**
* @brief Move servo 1 to the position define in the position array
*/
void setServo0();


/**
* @brief Move servo 2 to the position defined in the position array
*/
void setServo1();


/**
* @brief Move servo 3 to the position defined in the position array
*/
void setServo2();


/**
* @brief Move servo 4 to the position defined in the position array
*/
void setServo3();


/**
* @brief Move the given servo asynchonously to the desired position
*
* @param port       The port at which the servo is connected to the wallaby
* @param position   The position to which the servo should be moved
*/
void ssp_async(short port, short position);


/**
* @brief Move the given servo stepwise and async to the desired position
*
* @param port       The port at which the servo is connected to the wallaby
* @param position   The position to which the servo should be moved
* @param stepsize   How 'slow' the servos should be moved
* @param sleep      How long the servos sleep in between steps
*/
void ssp_stepwise_async(short port, short position, int stepsize, int sleep);


/**
* @brief Move the given servos asymmetrically and async to the desiren position
*
* @param port1      The port at which the first servo is connected to the wallaby
* @param port2      The port at which the second servo is connected to the wallaby
* @param position   The position to which the servos should be moved
*/
void ssp_asym_async(short port1, short port2, short position);


/**
* @brief Move the given servos stepwise, asym and async to the desired position
*
* @param port1      The port at which the first servo is connected to the wallaby
* @param port2      The port at which the second servo is connected to the wallaby
* @param position   The position to which the servos should be moved
* @param stepsize   How 'slow' the servos should be moved
* @param sleep      How long the servos sleep in between steps
*/
void ssp_stepwise_asym_async(short port1,
                             short port2,
                             short position,
                             int stepsize,
                             int sleep);

#endif /* SERVO_H */
