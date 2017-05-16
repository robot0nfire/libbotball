/**
* @file create.h
* @brief This file is used for interacting with the iRobot Create2.
*
* @author Nico Kratky
*
* @date 30/1/2017
*/

#ifndef LIBCREATE_H /* Include guard */
#define LIBCREATE_H

#define LOW_BYTE(x) ((x) & 0xFF)
#define HIGH_BYTE(x) (((x) & 0xFF00) >> 8)

#define RADIUS 117.5
#define CIRCUMFERENCE (2 * RADIUS * M_PI)

#define CREATE_SPEED_SLOW -100
#define CREATE_SPEED_MEDIUM -200
#define CREATE_SPPED_FAST -300

/**
* @brief This method drives at a given velocity and radius
* @author Nico Kratky
*
* @param velocity Speed at which the Create should drive. If velocity is negative, the Create will drive backwards
* @param radius Radius at which the Create should turn. If radius is positive, the Create will turn left, otherwise it will turn right
*/
void create_drives(const short velocity, const short radius);
/**
* @brief This method drives with two given velocities, one for each wheel.
* @author Nico Kratky
*
* @param velocity_l Speed at which the left wheel should drive
* @param velocity_r Speed at which the right wheel should drive
*/
void create_drives_direct(const short velocity_l, const short velocity_r);

/**
* @brief This method is used to stop the Create.
* @author Nico Kratky
*/
void create_stop();

/**
* @brief This method drives a given distance at a given speed, all in a straight line.
* This function utilizes a algorithm to slow down when coming close to the goal distance
* @author Nico Kratky
*
* @param velocity Speed at which the Create should drive
* @param millimeters Distance in mm which should be driven
*/
void create_drives_straight(const short velocity, const short millimeters);

/**
* @brief This method drives at a given velocity for a given time
* @author Nico Kratky
*
* @param velocity at which the Create will drive
* @param milliseconds How long the Create will drive
*/
void create_drives_time(const short velocity, const short milliseconds);

/**
* @brief This method spins the Create at a given speed and direction
* @author Nico Kratky
*
* @param velocity Speed at which the Create should spin
* @param direction Direction in which the Create should spin. If positive the Create will spin counter-clockwise, otherwise it will spin clockwise
*/
void create_spins_direct(const short velocity, const short direction);
/**
* @brief This method spins the Create clockwise at a given speed
* @author Nico Kratky
*
* @param velocity Speed at which the Create should spin
*/
void create_spins_clockwise(const short velocity);
/**
* @brief This method spins the Create counter-clockwise at a given speed
* @author Nico Kratky
*
* @param velocity Speed at which the Create should spin
*/
void create_spins_counterclockwise(const short velocity);
/**
* @brief This method spins the Create at a given speed to a given angle
* @author Nico Kratky
*
* @param velocity Speed at which the Create should spin
* @param degree Angle to which the Create should spin, If positive the Create will spin clockwise, otherwise it will spin counter-clockwise
*/
void create_spins_degrees(const short velocity, const short degree);

/**
* @brief This method drives at a given speed until the bumper sensor is triggered
* @author Nico Kratky
*
* @param velocity The speed at which the create will drive
*/
void create_drives_till_bump(const short velocity);

/**
* @brief This method drives at a given speed until the ET sensor is triggered
* @author Nico Kratky
*
* @param velocity The speed at which the create will drive
*/
void create_drives_till_et(const short velocity, const int milliseconds, const short port, const short threshold);

/**
* @brief Setup process which is required to be executed directly after connecting to the Create
* @author Nico Kratky
*/
void create_setup();
/**
* @brief This method shuts the Create down
* @author Nico Kratky
*/
void create_shutdown();

#endif /* LIBCREATE_H */
