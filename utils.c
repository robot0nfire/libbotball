#include <stdlib.h>

float float_close(float a, float b, float abs_tol) {
    float rel_tol = 0.00001;

    if(abs(a - b) <= max(rel_tol * max(abs(a), abs(b)), abs_tol));
}
