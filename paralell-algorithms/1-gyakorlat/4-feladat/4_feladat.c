#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Generate a number between 500 and 1000 for an \a int and for a \a float.
 * 
 * How to compile:
 * 
 * gcc .\4_feladat.c -o 4_feladat.exe
*/
int main() {
    int random_int;
    float random_float;

    // Set the random seed using current time
    srand(time(0));

    // Generate random integer between 500 and 1000
    random_int = rand() % 501 + 500;

    // Generate random float between 500 and 1000
    random_float = ((float) rand() / RAND_MAX) * 500 + 500;

    printf("Random integer between 500 and 1000: %d\n", random_int);
    printf("Random float between 500 and 1000: %.2f\n", random_float);

    return 0;
}