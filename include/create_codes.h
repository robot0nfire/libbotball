/**
* @file create_codes.h
* @brief This file stores the codes which are sent to the Create to execute commands
*
* @author Nico Kratky
*
* @date 17/2/2017
*/

#ifndef CREATE_CODES_H /* Include guard* */
#define CREATE_CODES_H

#define OI_START 128
#define OI_BAUD 129
#define OI_SAFE 131
#define OI_FULL 132
#define OI_DEMO 136

#define OI_DRIVE 137
#define OI_DRIVE_DIRECT 145
#define OI_LEDS 139
#define OI_DIGITAL_OUTPUTS 147
#define OI_LOW_SIDE_DRIVERS 138
#define OI_SEND_IR 151

#define OI_SONG 140
#define OI_PLAY_SONG 141

#define OI_SENSORS 142
#define OI_QUERY_LIST 149

#define OI_STREAM 148
#define OI_PAUSE_RESUME_STREAM 150

#define OI_SCRIPT 152
#define OI_PLAY_SCRIPT 153
#define OI_SHOW_SCRIPT 154

#define OI_WAIT_TIME 155
#define OI_WAIT_DISTANCE 156
#define OI_WAIT_ANGLE 157
#define OI_WAIT_EVENT 156

#define OI_BUMPS_AND_WHEEL_DROPS 7
#define OI_WALL 8
#define OI_CLIFF_LEFT 9
#define OI_CLIFF_FRONT_LEFT 10
#define OI_CLIFF_FRONT_RIGHT 11
#define OI_CLIFF_RIGHT 12
#define OI_VIRTUAL_WALL 13
#define OI_LOW_SIDE_DRIVER_AND_WHEEL_OVERCURRENTS 14
#define OI_BUTTONS 18
#define OI_DISTANCE 19
#define OI_ANGLE 20
#define OI_CHARGING_STATE 21
#define OI_VOLTAGE 22
#define OI_CURRENT 23
#define OI_CARGO_BAY_DIGITAL_INPUTS 32

#endif /* CREATE_CODES_H */
