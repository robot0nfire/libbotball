#include <kipr/botball.h>
#include "include/libcreate.h"
#include "include/create_codes.h"
#include "include/create_velocities.h"


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

void create_setup() {
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
