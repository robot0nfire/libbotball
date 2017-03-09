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

/**
* @brief returns the bigger value of two given ones
*/
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

/**
* @brief returns the smaller value of two given ones
*/
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

/**
* @brief compares two integeres if they are 'close'
*
* @param a the first value to compare
* @param b the second value to compare
* @param abs_tol absolute tolerance which is used when comparing

* @return 1 if the values are close to each other, otherwise 0
*/
int float_close(float a, float b, float abs_tol);

/**
* @brief This method is used to determine which starting procedure should be used
* @author Nico Kratky
*/
void start();

/**
* @brief This method gets the time since the program started.
* @author Nico Kratky
*/
unsigned long get_time();

/**
* @brief Stopping procedure
* @author Nico Leidenfrost
*/
void stop();

#endif /* UTILS_H */
