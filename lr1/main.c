#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include "math_func.h"

int run_tests() {
    struct {
        double x;
        double eps;
    } tests[] = {
        {0.0, 0.0001},
        {M_PI / 4, 0.0001},  // tan(pi/4) = 1
        {M_PI / 6, 0.00001}, // tan(pi/6) = 0.57735...
        {-1.0, 0.0001},
        {0.5, 0.001},
        /* near-pole behavior: values close to +/- pi/2 */
        {M_PI/2 - 1e-6, 1e6},
        {-M_PI/2 + 1e-6, 1e6}
    };

    int num_tests = sizeof(tests) / sizeof(tests[0]);
    int failed = 0;

    for (int i = 0; i < num_tests; i++) {
        double expected = tan(tests[i].x);
        double actual = custom_tan(tests[i].x, tests[i].eps);

        if (fabs(actual - expected) > tests[i].eps) {
            printf("Test %d failed: tan(%f), expected %f, got %f\n", 
                    i, tests[i].x, expected, actual);
            failed++;
        } else {
            printf("Test %d passed\n", i);
        }
    }

    return (failed == 0) ? 0 : -1;
}

int main() {
    int result = run_tests();
    return result;
}