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
* @brief Parameters for seek time calculation
* see http://www.servodatabase.com/servo/towerpro/sg-5010 for further information
*/
#define degreesPerTick 8789
/**
* @brief Parameters for seek time calculation
* see http://www.servodatabase.com/servo/towerpro/sg-5010 for further information
*/
#define timePerDegree 283333
/**
* @brief Parameters for seek time calculation
* see http://www.servodatabase.com/servo/towerpro/sg-5010 for further information
*/
#define calcDivisor  100000

/**
* @brief Properties Array for moving servos asynchronously.
* Dimensions represent the different servos
* 0: servo blocked status. 0 = not blocked; 1 = blocked
* 1: position to which the servo will be moved
* 2: stepsize which should be used to move the servo stepwise. If set to -1 the servo will be moved normally
* 3: sleep which should be used to move the servo stepwise. If set to -1 the servo will be moved normally
*/
int servoProperties[4][4] = {
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
int is_blocked(int servo){
    return servoProperties[servo][0];
}

/**
* @brief Wait till servo has finished moving
*
* @param servo Port to which the servo is connected
*/
void wait_for_servo(int servo){
    while(servoProperties[servo][0]){
        msleep(1);
    }
}

/**
* @brief Calculates the time in ms to wait before the whole movement of the servo is done at lowest energy level
* http://www.servodatabase.com/servo/towerpro/sg-5010 - servo data sheet
* @author Nico Kratky
*
* @param currentPosition Position in ticks at which the servo currenty is
* @param finalPosition Position in ticks to which the servo will be moved
*/
void servo_get_seek_time(unsigned int currentPosition, unsigned int finalPosition);

/**
* @brief This method moves the given servo to the desired position
* @author Nico Kratky
*
* @param port The port at which the servo is connected to the wallaby
* @param position The position to which the servo should be moved
*/
void ssp(unsigned int port, unsigned int position);

/**
* @brief Moves a servo with a given speed and given step size "slow" to it's destination
* @author Nico Kratky
*
* @param port The port at which the servo is connected to the wallaby
* @param position The position to which the servo should be moved
* @param stepsize How 'slow' the servo should be moved
* @param sleep How long the servo sleeps in between steps
*/
void ssp_stepwise(unsigned int port, unsigned int position, unsigned int stepsize, unsigned int sleep);

/**
* @brief This method moves two given servos asymmetrically to the given position
* @author Nico Kratky
*
* @param port1 The port at which the first servo is connected to the wallaby
* @param port2 The port at which the second servo is connected to the wallaby
* @param position The position to which the servo should be moved
*/
void ssp_asym(unsigned int port1, unsigned int port2, unsigned int position);

/**
* @brief This method moves servo 1 to the position defined in the positions array
* @author Nico Kratky
*
* @param stepsize How 'slow' the servo should be moved. If set to -1 the servo will not be moved stepwise
* @param sleep How long the servo sleeps in between steps. If set to -1 the servo will not be moved stepwise
*/
void setServo0(unsigned int stepsize, unsigned int sleep);

/**
* @brief This method moves servo 2 to the position defined in the positions array
* @author Nico Kratky
*
* @param stepsize How 'slow' the servo should be moved. If set to -1 the servo will not be moved stepwise
* @param sleep How long the servo sleeps in between steps. If set to -1 the servo will not be moved stepwise
*/
void setServo1(unsigned int stepsize, unsigned int sleep);

/**
* @brief This method moves servo 3 to the position defined in the positions array
* @author Nico Kratky
*
* @param stepsize How 'slow' the servo should be moved. If set to -1 the servo will not be moved stepwise
* @param sleep How long the servo sleeps in between steps. If set to -1 the servo will not be moved stepwise
*/
void setServo2(unsigned int stepsize, unsigned int sleep);

/**
* @brief This method moves servo 4 to the position defined in the positions array
* @author Nico Kratky
*
* @param stepsize How 'slow' the servo should be moved. If set to -1 the servo will not be moved stepwise
* @param sleep How long the servo sleeps in between steps. If set to -1 the servo will not be moved stepwise
*/
void setServo3(unsigned int stepsize, unsigned int sleep);

/**
* @brief This method moves the given servo asynchronously to the desired position
* @author Nico Kratky
*
* @param port The port at which the servo is connected to the wallaby
* @param position The position to which the servo should be moved
*/
void ssp_async(unsigned int port, unsigned int position);

/**
* @brief This method moves the given servo stepwise and asynchronously to the desired position
* @author Nico Kratky
*
* @param port The port at which the servo is connected to the wallaby
* @param position The position to which the servo should be moved
*/
void ssp_stepwise_async(unsigned int port, unsigned int position, unsigned int stepsize, unsigned int sleep);

#endif /* SERVO_H */
