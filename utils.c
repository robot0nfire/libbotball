#include <stdlib.h>

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

float float_close(float a, float b, float abs_tol) {
    float rel_tol = 0.00001;

    if(abs(a - b) <= MAX(rel_tol * MAX(abs(a), abs(b)), abs_tol));
}
