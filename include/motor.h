/**
* @file motor.h
* @brief This file provides functions to interact with the Botball motors.
*
* @author Nico Kratky
*
* @date 2/2/2017
*/

#ifndef MOTOR_H /* Include guard */
#define MOTOR_H

/**
* @brief Port to which the left driving motor is connected
*/
#define LEFT_MOTOR_DRIVE 0
/**
* @brief Port to which the right driving motor is connected
*/
#define RIGHT_MOTOR_DRIVE 3

/**
* @brief Port to which the left tophat is connected
*/
#define TOPHAT_LEFT 0
/**
* @brief Port to which the left tophat is connected
*/
#define TOPHAT_RIGHT 1

/**
* @brief Threshold for following a line
*/
#define THRESHOLD 0

/**
* @brief This method lets the robot drive with two given velocities
* @author Nico Kratky
*
* @param velocity_left Velocity at which the left motor will be moved
* @param velocity_right Velocity at which the right motor will be moved
*/
void drive_direct(int velocity_left, int velocity_right);

/**
* @brief This method lets the robot drive straight for a given duration
* @author Nico Kratky
*
* @param velocity Velocity at which the motors will be moved
* @param ms How long the robot will drive
*/
void drive_straight(int velocity, unsigned int ms);

/**
* @brief This method lets the robot drive with two given velocities for a given duration
* @author Nico Kratky
*
* @param velocity_left Velocity at which the left motor will be moved
* @param velocity_right Velocity at which the right motor will be moved
* @param ms How long the robot will drive
*/
void drive(int velocity_left, int velocity_right, unsigned int ms);

/**
* @brief This method lets the robot follow a line for a given duration
* @author Nico Kratky
*
* @param ms How lon the robot will follow a line
*/
void follow_line(unsigned int ms);

#endif /* MOTOR_H */
