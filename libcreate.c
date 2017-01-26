/**
* @file libcreate.c
* @brief This file is used for interacting with the iRobot Create2.
*
* @author Nico Kratky
*
* @date 27/1/2017
*/

#include <kipr/botball.h>
#include "include/libcreate.h"
#include "include/create_codes.h"
#include "include/create_velocities.h"

/**
* @brief This method drives at a given velocity and radius
* @author Nico Kratky
*
* @param velocity Speed at which the Create should drive. If velocity is negative, the Create will drive backwards
* @param radius Radius at which the Create should turn. If radius is positive, the Create will turn left, otherwise it will turn right
*/
void create_drives(const short velocity, const short radius) {
    create_write_byte(OI_DRIVE);
    create_write_byte(HIGH_BYTE(velocity));
    create_write_byte(LOW_BYTE(velocity));
    create_write_byte(HIGH_BYTE(radius));
    create_write_byte(LOW_BYTE(radius));
}

/**
* @brief This method drives with two given velocities, one for each wheel.
* @author Nico Kratky
*
* @param speed_l Speed at which the left wheel should drive
* @param speed_r Speed at which the right wheel should drive
*/
void create_drives_direct(const short speed_l, const short speed_r) {

    create_write_byte(OI_DRIVE_DIRECT);
    create_write_byte(HIGH_BYTE(speed_l));
    create_write_byte(LOW_BYTE(speed_l));
    create_write_byte(HIGH_BYTE(speed_r));
    create_write_byte(LOW_BYTE(speed_r));

}

/**
* @brief This method is used to stop the Create.
* @author Nico Kratky
*/
void create_stop() {
    create_write_byte(OI_DRIVE_DIRECT);
    create_write_byte(HIGH_BYTE(0));
    create_write_byte(LOW_BYTE(0));
    create_write_byte(HIGH_BYTE(0));
    create_write_byte(LOW_BYTE(0));
}

/**
* @brief This method drives a given distance
* The velocity at which the given distance should be reached precisly is determined automatically
* @author Nico Kratky
*
* @param millimeters Distance in mm which should be driven
*/
void create_drives_straight_auto(const short millimeters) {
    int velocity = get_velocity(millimeters);
    double timeToGoal = (double) ((float) millimeters / (float) velocity);

    create_drives_direct(velocity, velocity);
    msleep(timeToGoal * 1000);
    create_stop();
}

/**
* @brief This method drives a given distance at a given speed, all in a straight line.
* @author Nico Kratky
*
* @param velocity Velocity at which the Create should drive
* @param millimeters Distance in mm which should be driven
*/
void create_drives_straight(const unsigned short velocity, const short millimeters) {
    double timeToGoal = (double) ((float) millimeters / (float) velocity);

    create_drives_direct(velocity, velocity);
    msleep(timeToGoal * 1000);
    create_stop();

}

/**
* @brief This method spins the Create at a given speed and direction
* @author Nico Kratky
*
* @param speed Speed at which the Create should spin
* @param direction Direction in which the Create should spin. If positive the Create will spin counter-clockwise, otherwise it will spin clockwise
*/
void create_spins_direct(const unsigned short speed, const short direction) {
    create_drives(speed, (direction > 0) ? -1 : 1);
}

/**
* @brief This method spins the Create clockwise at a given speed
* @author Nico Kratky
*
* @param speed Speed at which the Create should spin
*/
void create_spins_clockwise(const unsigned short speed) {
    create_spins_direct(speed, 1);
}

/**
* @brief This method spins the Create counter-clockwise at a given speed
* @author Nico Kratky
*
* @param speed Speed at which the Create should spin
*/
void create_spins_counterclockwise(const unsigned short speed) {
    create_spins_direct(speed, -1);
}

/**
* @brief This method spins the Create at a given speed to a given angle
* @author Nico Kratky
*
* @param speed Speed at which the Create should spin
* @param angle Angle to which the Create should spin, If positive the Create will spin clockwise, otherwise it will spin counter-clockwise
*/
void create_spins_degrees(const unsigned short speed, const short angle) {
    double oneDegree = CIRCUMFERENCE / 360;
    double mm = oneDegree * abs(angle);

    double timeToGoal = mm / (speed + 8);

    create_spins_direct(speed, angle);
    msleep(timeToGoal * 1000);
    create_stop();
}

/**
* @brief Setup process which is required to be executed directly after connecting to the Create
* @author Nico Kratky
*/
void create_setup() {
    create_write_byte(OI_FULL);
    init_list(10, 70);
    insert_sorted(20, 80);
    insert_sorted(30, 80);
    insert_sorted(50, 200);
    insert_sorted(75, 190);
    insert_sorted(100, 250);
    insert_sorted(150, 250);
    insert_sorted(200, 300);
    insert_sorted(300, 310);
}

/**
* @brief This method shuts the Create down
* @author Nico Kratky
*/
void create_shutdown() {
    create_stop();
    create_write_byte(OI_SAFE);
}
