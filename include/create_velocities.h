#ifndef CREATE_VELOCITIES_H /* Include guard */
#define CREATE_VELOCITIES_H

struct Node {
    int distance;
    int velocity;
    struct Node *next;
};

struct Node* init_list(int distance, int velocity);

struct Node* insert_sorted(int distance, int velocity);

int get_velocity(int distance);

#endif /* CREATE_VELOCITIES_H */
