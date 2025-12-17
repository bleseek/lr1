#define _USE_MATH_DEFINES
#include "math_func.h"
#include <math.h>

double custom_tan(double x, double epsilon) {
    /* normalize x to [-pi/2, pi/2] for Taylor series convergence */
    x = fmod(x, M_PI);
    if (x > M_PI/2) x -= M_PI;
    if (x < -M_PI/2) x += M_PI;

    /* sanitize epsilon */
    if (epsilon <= 0) {
        epsilon = 1e-12; /* sensible default to avoid infinite loops */
    }

    /* Compute sin(x) via Taylor series. Always include the first term. */
    double term_s = x;
    double sin_x = term_s;
    int n = 1;
    while (1) {
        term_s *= -x * x / ((2 * n) * (2 * n + 1));
        if (fabs(term_s) <= epsilon / 2) break;
        sin_x += term_s;
        n++;
    }

    /* Compute cos(x) via Taylor series. Always include the first term. */
    double term_c = 1.0;
    double cos_x = term_c;
    n = 1;
    while (1) {
        term_c *= -x * x / ((2 * n - 1) * (2 * n));
        if (fabs(term_c) <= epsilon / 2) break;
        cos_x += term_c;
        n++;
    }

    return sin_x / cos_x;
}