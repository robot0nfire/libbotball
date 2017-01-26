#include <stdlib.h>
#include "include/create_velocities.h"

struct Node *root;

struct Node* init_list(int distance, int velocity) {
    struct Node *ptr = (struct Node*) malloc(sizeof(struct Node));

    if(ptr == NULL) {
        return NULL;
    }

    ptr->distance = distance;
    ptr->velocity = velocity;
    ptr->next = NULL;

    root = ptr;
    return ptr;
}

struct Node* insert_sorted(int distance, int velocity) {
    if(root == NULL) {
        return (init_list(distance, velocity));
    }

    struct Node *ptr = (struct Node*) malloc(sizeof(struct Node));

    if(ptr == NULL) {
        return NULL;
    }

    ptr->distance = distance;
    ptr->velocity = velocity;

    struct Node* run = root;

    while((run->next != NULL) && (run->next->distance < distance)) run = run->next;
    ptr->next = run->next;
    run->next = ptr;

    return ptr;
}

int get_velocity(int distance) {
    if(root == NULL) {
        return 0;
    }

    struct Node* run = root;

    while((run->next != NULL) && (run->next->distance <= distance)) run = run->next;

    if((run->distance == distance) || run->next == NULL) return run->velocity;

    if((run->next != NULL) && (run->next->distance == distance)) return run->next->velocity;

    int d1 = distance - run->distance;
    int d2 = run->next->distance - distance;

    if(d1 < d2) return run->velocity;
    return run->next->velocity;

}