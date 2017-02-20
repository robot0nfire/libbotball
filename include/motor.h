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
* @brief Threshold for following a line
*/
#define THRESHOLD 0

/**
* @brief This method lets the robot drive with two given velocities
* @author Nico Kratky
*
* @param velocity_l Velocity at which the left motor will be moved
* @param velocity_r Velocity at which the right motor will be moved
*/
void drive_direct(const short velocity_l, const short velocity_r);

/**
* @brief This method lets the robot drive straight for a given duration
* @author Nico Kratky
*
* @param velocity Velocity at which the motors will be moved
* @param ms How long the robot will drive
*/
void drive_straight(const short velocity, const short ms);

/**
* @brief This method lets the robot drive with two given velocities for a given duration
* @author Nico Kratky
*
* @param velocity_l Velocity at which the left motor will be moved
* @param velocity_r Velocity at which the right motor will be moved
* @param ms How long the robot will drive
*/
void drive(const short velocity_l, int velocity_r, const int ms);

/**
* @brief This method lets the robot follow a line for a given duration
* @author Nico Kratky
*
* @param ms How long the robot will follow a line
*/
void follow_line(const int ms);

/**
* @brief This method moves a motor to a given position
* smp stands for 'set motor position'
* @author Nico Kratky
*
* @param port Port to which the motor is connected
* @oaram velocity Speed at which the motor will move
* @param position Position to which to motor should be moved
*/
void smp(int port, const short velocity, const short position);

#endif /* MOTOR_H */
