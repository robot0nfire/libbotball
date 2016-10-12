struct Node {
    int distance;
    int velocity;
    struct Node *next;
};

struct Node* init_list(int distance, int velocity);

struct Node* insert_sorted(int distance, int velocity);

int get_velocity(int distance);
