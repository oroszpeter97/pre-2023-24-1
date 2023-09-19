#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANDOM_CIELING 10000

/**
 * Generates n number of random unique numbers between 0 and RANDOM_CIELING, then returns that array. Exits the program if it fails to allocate memory for the array.
 * 
 * @param n : The number of random numbers to generate. (The length of the array.)
 * 
 * @retval int* : The pointer to the start of the array.
*/
int* generate_unique_integers(int n) {
    int i, j, rand_num, temp_rand;
    int* arr = malloc(n * sizeof(int));

    if (arr == NULL) {
        fprintf(stderr, "Failed to allocate memory for array.\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    for (i = 0; i < n; i++) {

        do {
            rand_num = rand() % RANDOM_CIELING;
            for (j = 0; j < i; j++) {
                if (arr[j] == rand_num) {
                    break;
                }
            }
        } while (j < i);

        arr[i] = rand_num;
    }

    return arr;
}

/**
 * Generates n number of random numbers between 0 and RANDOM_CIELING, then returns that array. There is a 50% chance it creates an already existing number. Exits the program if it fails to allocate memory for the array.
 * 
 * @param n : The number of random numbers to generate. (The length of the array.)
 * 
 * @retval int* : The pointer to the start of the array.
*/
int* generate_unique_integers_with_dupe_chance(int n) {
    int i, j, rand_num, dupe_chance;
    int* arr = malloc(n * sizeof(int));

    if (arr == NULL) {
        fprintf(stderr, "Failed to allocate memory for array.\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n; i++) {
        srand(time(NULL));
        if(i == 0){
            dupe_chance = 0;
        }else{
            dupe_chance = rand() % 101;
        }
        if(dupe_chance < 50){
            do {
                rand_num = rand() % RANDOM_CIELING;
                for (j = 0; j < i; j++) {
                    if (arr[j] == rand_num) {
                        break;
                    }
                }
            } while (j < i);

            arr[i] = rand_num;
        }else{
            rand_num = rand() % i;
            arr[i] = rand_num;
        }
    }

    return arr;
}

/**
 * Checks if the given int arrays elements are unqiue. The complexity of the function is O(n) since if it is unique it will iterate through all the elements.
 * 
 * @param arr : The int array to be checked.
 * @param n : The length of the int array.
 * 
 * @retval 0 : If the array is not unique.
 * @retval 1 : If the array is unique.
*/
int is_unique_int_array(int arr[], int n) {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) 
            if (arr[i] == arr[j]) 
                return 0;

    return 1;
}

/**
 * Generate an array of unique ints.
 * - Measure the time to create depending on the size.
 * - Dupe some of the elements with 50% chance.
 * - Write a function that checks if all the elements of an array is unique and measure the time.
 * 
 * How to compile:
 * 
 * gcc 2_feladat.c -o 2_feladat.exe
*/
int main(){
    double time_elapsed;
    clock_t start_time, end_time;
    int* uniq_arr;
    int* dupe_arr;

    // Generate and measure unique generation.
    for (int i = 100; i <= 10000; i += 100)
    {
        start_time = clock();
        uniq_arr = generate_unique_integers(i);
        end_time = clock();
        time_elapsed = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        printf("The time it took to generate %d numbers is: %lf\n", i, time_elapsed);
    }

    printf("\n----------------------------------------------------------------------\n\n");

    // Generate with 50-50 dupe chance
    dupe_arr = generate_unique_integers_with_dupe_chance(10000);

    // Check if arrays containt duplicates
    if(is_unique_int_array(uniq_arr, 10000))
        printf("The array is unique.\n");
    else
        printf("The array isn't unique.\n");
    
    if(is_unique_int_array(dupe_arr, 10000))
        printf("The array is unique.\n");
    else
        printf("The array isn't unique.\n");

    free(dupe_arr);
    free(uniq_arr);

    return 0;
}
