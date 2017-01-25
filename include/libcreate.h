#ifndef LIBCREATE_H /* Include guard */
#define LIBCREATE_H

#define LOW_BYTE(x) ((x) & 0xFF)
#define HIGH_BYTE(x) (((x) & 0xFF00) >> 8)

#define CIRCUMFERENCE 1065

void create_drives(const short velocity, const short radius);
void create_drives_direct(const short speed_l, const short speed_r);

void create_stop();

void create_drives_straight(const unsigned short speed, const short millimeters);
void create_drives_straight_auto(const short millimeters);

void create_spins_direct(const unsigned short speed, const short direction);
void create_spins_clockwise(const unsigned short speed);
void create_spins_counterclockwise(const unsigned short speed);
void create_spins_degrees(const short speed, const unsigned short degree);

void create_setup();
void create_shutdown();

#endif /* LIBCREATE_H */
