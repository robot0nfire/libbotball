#include "create_codes.h"

#define LOW_BYTE(x) ((x) & 0xFF)
#define HIGH_BYTE(x) (((x) & 0xFF00) >> 8)


void create_drive_direct(const short& speed_l, const short& speed_r) {
	
	create_write_byte(OI_DRIVE_DIRECT);
  	create_write_byte(HIGH_BYTE(speed_l));
  	create_write_byte(LOW_BYTE(speed_l));
  	create_write_byte(HIGH_BYTE(speed_r));
	create_write_byte(LOW_BYTE(speed_r));
  
}

void create_drive_straight(const unsigned short& speed, const short& millimeters) {
 	double timeToGoal = (double) (millimeters / speed);

  	create_drive_direct(speed, speed);
  	msleep(timeToGoal * 1000);
  	create_stop();
  
}

void create_stop() {
	create_write_byte(OI_DRIVE_DIRECT);
  	create_write_byte(HIGH_BYTE(0));
  	create_write_byte(LOW_BYTE(0));
  	create_write_byte(HIGH_BYTE(0));
	create_write_byte(LOW_BYTE(0));
}