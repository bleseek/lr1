#include <stdio.h>
#include "math.h"

// Unit test function
int run_tests() {
    int result;

    // Test 1
    result = subtract(5, 3);
    if (result != 2) {
        printf("Test 1 failed: expected 2, got %d\n", result);
        return -1;
    }

    // Test 2
    result = subtract(0, 7);
    if (result != -7) {
        printf("Test 2 failed: expected -7, got %d\n", result);
        return -1;
    }

    // Test 3
    result = subtract(-3, -3);
    if (result != 0) {
        printf("Test 3 failed: expected 0, got %d\n", result);
        return -1;
    }

    printf("All tests passed!\n");
    return 0;
}

int main() {
    return run_tests();
}
