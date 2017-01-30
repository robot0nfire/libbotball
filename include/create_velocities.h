/**
* @file create_velocities.h
* @brief This file implements a linked list to store driving data for the iRobot Create2.
*
* @author Nico Kratky
*
* @date 30/1/2017
*/

#ifndef CREATE_VELOCITIES_H /* Include guard */
#define CREATE_VELOCITIES_H

struct Node {
    int distance;
    int velocity;
    struct Node *next;
};

/**
* @brief This method initializes the linked list and stores the first data pair.
* @author Nico Kratky
*
* @param distance The distance that will be driven
* @param velocity The velocity at which the distance is reached accurately
*/
struct Node* init_list(int distance, int velocity);

/**
* @brief This method inserts a data pair into the linked list.
* @author Nico Kratky
*
* @param distance The distance that will be driven
* @param velocity The velocity at which the distance is reached accurately
*/
struct Node* insert_sorted(int distance, int velocity);

/**
* @brief This method is used to retrieve the velocity at which the given distance is reached accurately
* @author Nico Kratky
*
* @param distance The distance that will be driven+
*/
int get_velocity(int distance);

#endif /* CREATE_VELOCITIES_H */
