/**
* @file ports.h
* @brief This file defines the ports to which sensors, motors, and servos are connected
*
* @author Nico Kratky
*
* @date 17/2/2017
*/

#ifndef PORTS_H /* Include guard */
#define PORTS_H

/**
* @brief Port to which the left tophat sensor is connected
*/
#define TOPHAT_LEFT 0
/**
* @brief Port to which the right tophat sensor is connected
*/
#define TOPHAT_RIGHT 1
/**
* @brief Port to which the light sensor is connected
*/
#define LIGHT_SENSOR 5

/**
* @brief Port to which the right button is connected
*/
#define RIGHT_BUTTON 13

/**
* @brief Port to which the left driving motor is connected
*/
#define LEFT_MOTOR_DRIVE 1
/**
* @brief Port to which the right driving motor is connected
*/
#define RIGHT_MOTOR_DRIVE 0

#endif /* PORTS_H */
