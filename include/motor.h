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
#define THRESHOLD 3800

/**
* @brief Amount of ticks the left motor needs for a full rotation
*/
#define LEFTTICKS 1267

/**
* @brief Amount of ticks the right motor needs for a full rotation
*/
#define RIGHTTICKS 1365

/**
* @brief Perimeter of the wheels in mm
*/
#define WHEELPERIMETER 151

/**
* @brief Properties Array for moving motors asynchronously.
* Dimensions represent the different motors
* 0: motor blocked status. 0 = not blocked; 1 = blocked
* 1: velocity at which the motor will move
* 2: how long the motor will move
*/
static int motorProperties[4][3] = {
    {0, 0, -1},
    {0, 0, -1},
    {0, 0, -1},
    {0, 0, -1}
};

/**
* @brief Wait till motor has finished moving
*
* @param motor Port to which the motor is connected
*/
static void wait_for_motor(short motor){
    while(motorProperties[motor][0]){
        msleep(1);
    }
}


/**
* @brief Turn each wheel at given velocities
*
* @param velocity_l Velocity at which the left motor will be moved
* @param velocity_r Velocity at which the right motor will be moved
*/
void drive_direct(const short velocity_l, const short velocity_r);


/**
* @brief Drive straight for a given duration
*
* @param velocity   Velocity at which the motors will be moved
* @param ms         How long the robot will drive
*/
void drive_straight(const short velocity, const short ms);


/**
* @brief Drive straight for a given distance
*
* @param velocity Velocity at which the motors will be moved
* @param distance Distance the robot will drive in mm
*/
void drive_distance(short velocity, const short distance);


/**
* @brief Drive straight till the ET is triggerd of the given distance is reached
*
* @param velocity   Velocity at which the motors will be moved
* @param distance   Distance the robot will drive in mm
* @param port Port  to which the et sensor is connected
* @param threshold  Threshold for the et sensor
*/
void drive_till_et(short velocity, const short distance, const short port, const short threshold);


/**
* @brief Drive at two given velocities for a given duration
*
* @param velocity_l Velocity at which the left motor will be moved
* @param velocity_r Velocity at which the right motor will be moved
* @param ms         How long the robot will drive
*/
void drive(const short velocity_l, int velocity_r, const int ms);


/**
* @brief Follow a line for a given duration
*
* @param ms How long the robot will follow a line
*/
void follow_line(const int ms);


/**
* @brief Move the motor to a given position
* smp stands for 'set motor position'
*
* @param port       Port to which the motor is connected
* @param velocity   Speed at which the motor will move
* @param position   Position to which to motor should be moved
*/
void smp(int port, const short velocity, const short position);


/**
* @brief This method turns for a given amount of degrees
* @brief Turn for a given amount of degrees
*
* @param velocity   Speed at which the motors will move
* @param deg        Angle to which the robot will move
*/
void turn(short velocity, const short deg);


/**
* @brief This method moves motor 0 at a speed defined in motorProperties
*/
void moveMotor0();


/**
* @brief This method moves motor 1 at a speed defined in motorProperties
* @author Nico Kratky
*/
void moveMotor1();


/**
* @brief This method moves motor 2 at a speed defined in motorProperties
* @author Nico Kratky
*/
void moveMotor2();


/**
* @brief This method moves motor 3 at a speed defined in motorProperties
* @author Nico Kratky
*/
void moveMotor3();


/**
* @brief Move a motor async
*
* @param port       the port to which the motor is connected
* @param velocity   speed at which the motor will move
*/
void mav_async(const short port, const short velocity);


/**
* @brief Move a motor async for a given duration
*
* @param port       the port to which the motor is connected
* @param velocity   speed at which the motor will move
* @param ms         how long the motor will move
*/
void mav_async_time(const short port, const short velocity, const short ms);


/**
* @brief Move a motor for a given duration
*
* @param port       the port to which the motor is connected
* @param velocity   speed at which the motor will move
* @param ms         how long the motor will move
*/
void mav_time(const short port, const short velocity, const short ms);

#endif /* MOTOR_H */
