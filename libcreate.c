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

void create_drives(const short velocity, const short radius) {
    create_write_byte(OI_DRIVE);
    create_write_byte(HIGH_BYTE(velocity));
    create_write_byte(LOW_BYTE(velocity));
    create_write_byte(HIGH_BYTE(radius));
    create_write_byte(LOW_BYTE(radius));
}

void create_drives_direct(const short speed_l, const short speed_r) {

    create_write_byte(OI_DRIVE_DIRECT);
    create_write_byte(HIGH_BYTE(speed_l));
    create_write_byte(LOW_BYTE(speed_l));
    create_write_byte(HIGH_BYTE(speed_r));
    create_write_byte(LOW_BYTE(speed_r));

}

void create_stop() {
    create_write_byte(OI_DRIVE_DIRECT);
    create_write_byte(HIGH_BYTE(0));
    create_write_byte(LOW_BYTE(0));
    create_write_byte(HIGH_BYTE(0));
    create_write_byte(LOW_BYTE(0));
}

void create_drives_straight_auto(const short millimeters) {
    int velocity = get_velocity(millimeters);
    double timeToGoal = (double) ((float) millimeters / (float) velocity);

    create_drives_direct(velocity, velocity);
    msleep(timeToGoal * 1000);
    create_stop();
}

void create_drives_straight(const unsigned short velocity, const short millimeters) {
    double timeToGoal = (double) ((float) millimeters / (float) velocity);

    create_drives_direct(velocity, velocity);
    msleep(timeToGoal * 1000);
    create_stop();

}

void create_spins_direct(const unsigned short speed, const short direction) {
    create_drives(speed, (direction > 0) ? -1 : 1);
}

void create_spins_clockwise(const unsigned short speed) {
    create_spins_direct(speed, 1);
}

void create_spins_counterclockwise(const unsigned short speed) {
    create_spins_direct(speed, -1);
}

void create_spins_degrees(const unsigned short speed, const short angle) {
    double oneDegree = CIRCUMFERENCE / 360;
    double mm = oneDegree * abs(angle);

    double timeToGoal = mm / (speed + 8);

    create_spins_direct(speed, angle);
    msleep(timeToGoal * 1000);
    create_stop();
}

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

void create_shutdown() {
    create_stop();
    create_write_byte(OI_SAFE);
}
