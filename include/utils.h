/**
* @file utils.h
* @brief This file provides utility functions.
*
* @author Nico Kratky
*
* @date 16/2/2017
*/

#ifndef UTILS_H /* Include guard */
#define UTILS_H

#define LOW_BYTE(x) ((x) & 0xFF)
#define HIGH_BYTE(x) (((x) & 0xFF00) >> 8)

/**
* @brief returns the bigger value of two given ones
*/
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

/**
* @brief returns the smaller value of two given ones
*/
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

/**
* @brief converts degrees to radians
*/
#define degToRad(deg) (deg * M_PI / 180.0)

/**
* @brief converts radians to degrees
*/
#define radToDeg(rad) (rad * 180.0 / M_PI)

/**
* @brief compares two integeres if they are 'close'
*
* @param a          the first value to compare
* @param b          the second value to compare
* @param abs_tol    absolute tolerance which is used when comparing

* @return 1 if the values are close to each other, otherwise 0
*/
int float_close(float a, float b, float abs_tol);


/**
* @brief This method is used to determine which starting procedure should be used
*/
void start();


/**
* @brief Get the duration since the program started
*/
unsigned long get_time();


/**
* @brief Filter values using the Savitzky Golay filter
*
* @param x      value to be filtered
* @param buf    buffer of last 5 values
*/
int sav_gol(int x, int *buf);


/**
* @brief Stopping procedure
*/
void stop();

#endif /* UTILS_H */
