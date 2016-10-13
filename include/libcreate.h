#ifndef LIBCREATE_H /* Include guard */
#define LIBCREATE_H

#define LOW_BYTE(x) ((x) & 0xFF)
#define HIGH_BYTE(x) (((x) & 0xFF00) >> 8)

void create_drives_direct(const short speed_l, const short speed_r);

void create_stop();

void create_drives_straight(const unsigned short speed, const short millimeters);

void create_setup();

#endif /* LIBCREATE_H */
