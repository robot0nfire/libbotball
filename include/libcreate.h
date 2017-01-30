/**
* @file libcreate.h
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

#define CIRCUMFERENCE 1065

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
* @param speed_l Speed at which the left wheel should drive
* @param speed_r Speed at which the right wheel should drive
*/
void create_drives_direct(const short speed_l, const short speed_r);

/**
* @brief This method is used to stop the Create.
* @author Nico Kratky
*/
void create_stop();

/**
* @brief This method drives a given distance at a given speed, all in a straight line.
* @author Nico Kratky
*
* @param velocity Velocity at which the Create should drive
* @param millimeters Distance in mm which should be driven
*/
void create_drives_straight(const unsigned short speed, const short millimeters);
/**
* @brief This method drives a given distance
* The velocity at which the given distance should be reached precisly is determined automatically
* @author Nico Kratky
*
* @param millimeters Distance in mm which should be driven
*/
void create_drives_straight_auto(const short millimeters);

/**
* @brief This method spins the Create at a given speed and direction
* @author Nico Kratky
*
* @param speed Speed at which the Create should spin
* @param direction Direction in which the Create should spin. If positive the Create will spin counter-clockwise, otherwise it will spin clockwise
*/
void create_spins_direct(const unsigned short speed, const short direction);
/**
* @brief This method spins the Create clockwise at a given speed
* @author Nico Kratky
*
* @param speed Speed at which the Create should spin
*/
void create_spins_clockwise(const unsigned short speed);
/**
* @brief This method spins the Create counter-clockwise at a given speed
* @author Nico Kratky
*
* @param speed Speed at which the Create should spin
*/
void create_spins_counterclockwise(const unsigned short speed);
/**
* @brief This method spins the Create at a given speed to a given angle
* @author Nico Kratky
*
* @param speed Speed at which the Create should spin
* @param angle Angle to which the Create should spin, If positive the Create will spin clockwise, otherwise it will spin counter-clockwise
*/
void create_spins_degrees(const unsigned short speed, const short degree);

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
