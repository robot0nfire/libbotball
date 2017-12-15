/**
* @file create.h
* @brief This file is used for interacting with the iRobot Create2.
*
* @author Nico Kratky
*
* @date 30/1/2017
*/

#ifndef CREATE_H /* Include guard */
#define CREATE_H

/**
* @brief Radius of the create
*/
#define RADIUS 117.5

/**
* @brief Circumference of the create
*/
#define CIRCUMFERENCE (2 * RADIUS * M_PI)


#define CREATE_SPEED_SLOW 100
#define CREATE_SPEED_MEDIUM 200
#define CREATE_SPEED_FAST 300
/**
 * @brief Create speed override
 * Use with caution, Create will not drive straight under certain
 * circumstances
 * Use this speed ONLY for aligning
 */
#define CREATE_SPEED_FAST_OVERRIDE 500

/**
* @brief Drive at a certain velocity and radius
*
* @param velocity Speed at which the Create should drive.
*                 If velocity is negative, the Create will drive backwards
* @param radius   Radius at which the Create should turn.
*                 If radius is positive, the Create will turn left
*                 If radius is negative, the Create will turn right
*/
void create_drives(const short velocity, const short radius);


/**
* @brief Directly set the speeds for each wheel
*
* @param velocity_l Speed at which the left wheel should turn
* @param velocity_r Speed at which the right wheel should turn
*/
void create_drives_direct(const short velocity_l, const short velocity_r);


/**
* @brief Stop the create
*/
void create_stop();


/**
* @brief Drive at a given speed for a given distance
* This function utilizes a special algorithm that slows the Create down when
* approaching the target distance
*
* @param velocity    Speed at which the Create should drive
* @param millimeters Distance in mm which should be driven
*/
void create_drives_straight(const short velocity, const short millimeters);


/**
* @brief Drive at a given velocity for a given duration
*
* @param velocity     at which the Create will drive
* @param milliseconds How long the Create will drive
*/
void create_drives_time(const short velocity, const short milliseconds);


/**
* @brief Spin the create at a given velocity and direction
*
* @param velocity  Speed at which the Create should spin
* @param direction Direction in which the Create should spin.
*                  Positive => counter-clockwise
*                  Negative => clockwise
*/
void create_spins_direct(const short velocity, const short direction);


/**
* @brief Spin clockwise at a given velocity
*
* @param velocity Speed at which the Create should spin
*/
void create_spins_clockwise(const short velocity);


/**
* @brief Spin counter-clockwise at a given velocity
*
* @param velocity Speed at which the Create should spin
*/
void create_spins_counterclockwise(const short velocity);


/**
* @brief Spin the Create at a given velocity to the target angle
*
* @param velocity Speed at which the Create should spin
* @param degree   Angle to which the Create should spin
*                 Positive => clockwise
*                 Negative => counter-clockwise
*/
void create_spins_degrees(const short velocity, const short degree);


/**
* @brief Drive at a given velocity till the bumper sensor is triggered
*
* @param velocity The speed at which the create will drive
*/
void create_drives_till_bump(const short velocity);


/**
* @brief Drive at a given velocity until the ET sensor is triggered
*
* @param velocity       Velocity at which the create will drive
* @param milliseconds   backup time
* @param port           Port to which the et sensor is connected
* @param threshold      Threshold for the et sensor
*/
void create_drives_till_et(const short velocity,
                           const int milliseconds,
                           const short port,
                           const short threshold);


/**
* @brief Setup process
* IMPORTANT: Call this function directly after connecting the Create
*/
void create_setup();


/**
* @brief Shut the Create down
*/
void create_shutdown();

#endif /* CREATE_H */
