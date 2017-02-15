/**
* @file libcreate.c
* @brief This file is used for interacting with the iRobot Create2.
*
* @author Nico Kratky
*
* @date 27/1/2017
*/

#include <kipr/botball.h>
#include <math.h>
#include "include/utils.h"
#include "include/create.h"
#include "include/create_codes.h"

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

void create_drives_straight(const unsigned short velocity, const short millimeters) {
    set_create_distance(0);
    int start = get_create_distance();
    int distance = start;

    double mod = 1;

    create_drives_direct(velocity, velocity);

    while(!float_close((float) millimeters, (float) (distance - start), 3) && !((distance - start) > millimeters)) {

	printf("DISTANCE TO GOAL: %d\n", (millimeters - (distance - start)));
	printf("VELOCITY: %d\n", (int) (velocity * mod));
	printf("MOD: %f\n", mod);

        mod = (0.5 * MIN(0.6 + pow((double) (millimeters - (distance - start)), 2) / pow(velocity, 2), 1) + 0.5);
        create_drives_direct((int) floor(velocity * mod), (int) floor(velocity * mod));
        msleep(3);

        distance = get_create_distance();
    }

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

void create_drives_till_bump(const unsigned short speed) {
    create_drives_direct(speed, speed);

    while(!get_create_lbump() && !get_create_rbump()) msleep(1);

    create_stop();
}

void create_setup() {
    create_write_byte(OI_FULL);
}

void create_shutdown() {
    create_stop();
    create_write_byte(OI_SAFE);
    create_disconnect();
}
