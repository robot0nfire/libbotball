#include <stdlib.h>
#include "utils.h"

int float_close(float a, float b, float abs_tol) {
    float rel_tol = 0.00001;

    if(abs(a - b) <= MAX(rel_tol * MAX(abs(a), abs(b)), abs_tol))
        return 1;
    return 0;
}
