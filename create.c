/**
* @file create.c
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
#include "include/ports.h"

void create_drives(const short velocity, const short radius) {
    create_write_byte(OI_DRIVE);
    create_write_byte(HIGH_BYTE(velocity));
    create_write_byte(LOW_BYTE(velocity));
    create_write_byte(HIGH_BYTE(radius));
    create_write_byte(LOW_BYTE(radius));
}

void create_drives_direct(const short velocity_l, const short velocity_r) {
    create_write_byte(OI_DRIVE_DIRECT);
    create_write_byte(HIGH_BYTE(velocity_r));
    create_write_byte(LOW_BYTE(velocity_r));
    create_write_byte(HIGH_BYTE(velocity_l));
    create_write_byte(LOW_BYTE(velocity_l));
}

void create_stop() {
    create_write_byte(OI_DRIVE_DIRECT);
    create_write_byte(HIGH_BYTE(0));
    create_write_byte(LOW_BYTE(0));
    create_write_byte(HIGH_BYTE(0));
    create_write_byte(LOW_BYTE(0));
}

void create_drives_straight(const short velocity, const short millimeters) {
    set_create_distance(0);
    int start = abs(get_create_distance());
    int distance = start;

    double mod1;
    double mod2;

    create_drives_direct(velocity, velocity);

    while(!float_close((float) millimeters, (float) (distance - start), 3) && !((distance - start) > millimeters)) {

        mod1 = 0.6 + pow((double) (millimeters - (distance - start)), 2) / pow(velocity, 2);

        if(mod1 >= 1) msleep(3);
        else {
            mod2 = 0.5 * mod1 + 0.5;
            create_drives_direct((int) floor(velocity * mod2), (int) floor(velocity * mod2));
            msleep(3);
        }

        distance = abs(get_create_distance());
    }

    create_stop();
}

void create_drives_time(const short velocity, const short milliseconds) {
    create_drives_direct(velocity, velocity);
    msleep(milliseconds);
    create_stop();
}

void create_spins_direct(const short velocity, const short direction) {
    create_drives(velocity, (direction > 0) ? -1 : 1);
}

void create_spins_clockwise(const short velocity) {
    create_spins_direct(velocity, 1);
}

void create_spins_counterclockwise(const short velocity) {
    create_spins_direct(velocity, -1);
}

void create_spins_degrees(const short velocity, const short angle) {
    double oneDegree = CIRCUMFERENCE / 360;
    double mm = oneDegree * abs(angle);

    double timeToGoal = mm / (velocity + 8);

    create_spins_direct(velocity, angle);
    msleep(timeToGoal * 1000);
    create_stop();
}

void create_drives_till_bump(const short velocity) {
    create_drives_direct(velocity, velocity);

    while(!get_create_lbump() && !get_create_rbump()) msleep(1);

    create_stop();
}

void create_drives_till_et(const short velocity, const int milliseconds, const short port, const short threshold) {
    create_drives_direct(velocity, velocity);

    int start = seconds();

    int buf[5] = {-1, -1, -1, -1, -1};

    int val = sav_gol(analog(port), &buf);

    while(seconds() < start + (milliseconds / 1000) && val < threshold) {
        val = sav_gol(analog(port), &buf);
        msleep(1);
    }

    create_stop();
}

void create_setup() {
    create_connect();
    create_write_byte(OI_FULL);
}

void create_shutdown() {
    stop();
    create_stop();
    create_write_byte(OI_SAFE);
    create_disconnect();
}
