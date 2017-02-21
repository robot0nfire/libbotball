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
* @section sensors Ports to which sensors are connected
*/

/**
* @subsection sensors_analog Ports to which analog sensors are connected
*/

#define TOPHAT_LEFT 0
#define TOPHAT_RIGHT 1
#define LIGHT_SENSOR 5


/**
* @subsection sensors_digital Ports to which digital sensors are connected
*/

#define RIGHT_BUTTON 13

/**
* @section motors Ports to which motors are connected
*/

#define LEFT_MOTOR_DRIVE 0
#define RIGHT_MOTOR_DRIVE 3

#endif /* PORTS_H */
