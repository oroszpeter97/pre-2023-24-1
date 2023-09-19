#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "helper-libraries/error_library.h"
#include "helper-libraries/validity_checker.h"
#include "helper-libraries/dynamic_int_array.h"
#include "helper-libraries/timer.h"

static const int _ARRAY_LENGTH_MIN = 0;
static const int _ARRAY_LENGTH_MAX = 10000;
static const int _ELEMENT_LIMIT_MIN = 0;
static const int _ELEMENT_LIMIT_MAX = 100;
static const int _NUMBER_OF_THREADS_MIN = 1;
static const int _NUMBER_OF_THREADS_MAX = 10;
static const double _MAP_DOUBLE_MIN = 1.0;
static const double _MAP_DOUBLE_MAX = 1.1;

static double important_times[6];

double starting = 0.0;
double ending = 0.0;
double elapsed_time = 0.0;

/**
 * @brief Displays how the program work into the console.
*/
void display_help(char *program_name) {
	printf("Usage: %s [array_length] [element_lower_limit] [element_upper_limit] [number_of_threads]\n", program_name);
	printf("Arguments:\n");
	printf("  array_length - The length of the array the program should use. [0, 10.000]\n");
	printf("  element_lower_limit - The randomly generated arrays elements lower limit. [0, 100]\n");
	printf("  element_upper_limit - The randomly generated arrays elements upper limit. [0, 100]\n");
	printf("  number_of_threads - The number of threads the program should utilize for each operation. [1, 10]\n");
	printf("\n");
	printf("Example:\n");
	printf("  %s 5000 0 75 4\n", program_name);
}

/**
 * Validates the command line arguments passed to the program and performs necessary error handling.
 * 
 * @param argc The number of command line arguments.
 * @param argv The array of command line argument strings.
 * @param error A pointer to an Error struct that will be used to report any errors that occur.
 * 
 * @throws INVALID_CL_ARGUMENTS : if the number of command line arguments is not 2 or 5, or if the argument values are invalid.
 * @throws CONVERSION_ERROR : if any of the argument values cannot be converted to integers.
 * 
 * @return void
*/
void check_argument_validity(int argc, char *argv[], Error* error){
	if (argc != 2 && argc != 5) {
		throw_new_error(INVALID_CL_ARGUMENTS, error);
		print_error(error);
		exit(0);
	}

	if (argc == 2 && strcmp(argv[1], "-help") == 0) {
		display_help(argv[0]);
		exit(0);
	} else if (argc == 5) {
		for(int i = 1; i < 5; i++){
			if(!is_int(argv[i], error)){
				throw_new_error(CONVERSION_ERROR, error);
				print_error(error);
				exit(1);
			}
		}
	} else {
		throw_new_error(INVALID_CL_ARGUMENTS, error);
		print_error(error);
		exit(1);
	}
}

/**
 * @brief Maps an integer value to a corresponding double value within a specified range.
 *
 * @param value The integer value to be mapped.
 * @param i_min The minimum value of the integer range.
 * @param i_max The maximum value of the integer range.
 * @param d_min The minimum value of the double range.
 * @param d_max The maximum value of the double range.
 * @return The mapped double value.
 *
 * This function converts an integer value to the corresponding double value within
 * a specified range. It uses linear mapping to scale and map the integer value
 * proportionally to the double range. The resulting double value is returned.
 *
 * @note The integer value should be within the range [i_min, i_max].
 * @note The double range [d_min, d_max] should be non-empty (d_min <= d_max).
 * @note The function assumes that the provided ranges do not cause overflow or precision issues.
 */
long double map_int_to_double(int value, int i_min, int i_max, double d_min, double d_max){
    // Convert the integer value to the corresponding double value
    return (double)(value - i_min) * (double)(d_max - d_min) / (double)(i_max - i_min) + d_min;
}

/**
 * @brief Initializes an array of subsets for a dynamic integer array.
 *
 * @param dynamic_array Pointer to the Dynamic_Int_Array.
 * @param dynamic_array_subsets Pointer to the Dynamic_Int_Array_Subset array.
 * @param array_length Length of the dynamic array.
 * @param n_threads Number of threads for splitting the array.
 *
 * This function calculates the appropriate range for each subset of the dynamic array,
 * based on the specified number of threads. It divides the array into equal parts, rounding
 * down the result to the nearest integer. If there is a remainder after division, it assigns
 * the extra element to subsets until the remainder is exhausted. The function populates the
 * Dynamic_Int_Array_Subset array with the appropriate subset information.
 */
void initialize_array_subsets(Dynamic_Int_Array *dynamic_array, Dynamic_Int_Array_Subset *dynamic_array_subsets, int array_length, int n_threads){
	// Calculate the length of each part of the splitting.
    float quotient = (float) array_length / n_threads; // divide the number into n parts
    int part_size = floor(quotient); // round the result to the nearest integer

    int remainder = array_length % part_size; // calculate the remaining amount after division 
    int num_parts_with_extra = remainder; // the number of parts with an extra element

    int num_parts_without_extra = n_threads - num_parts_with_extra; // the number of parts without an extra element

    // Create the array of subset arrays
	int number_of_subset_arrays = num_parts_with_extra + num_parts_without_extra;
    int current_lower_range = 1;
    for(int i = 0; i < number_of_subset_arrays; i++){
        dynamic_array_subsets[i].array = dynamic_array;
        dynamic_array_subsets[i].lower_range = current_lower_range - 1;
        if(remainder != 0){
            dynamic_array_subsets[i].upper_range = dynamic_array_subsets[i].lower_range + part_size + 1;
            remainder--;
        }else{
            dynamic_array_subsets[i].upper_range = dynamic_array_subsets[i].lower_range + part_size;
        }
        current_lower_range = dynamic_array_subsets[i].upper_range + 1;
    }
}

/**
 * @brief Initializes the subset arrays with random numbers using multiple threads.
 *
 * @param dynamic_array_subsets Pointer to the Dynamic_Int_Array_Subset array.
 * @param v_lower_limit Lower limit for generating random numbers.
 * @param v_upper_limit Upper limit for generating random numbers.
 * @param n_threads Number of threads to be used for initialization.
 *
 * This function sets the number of threads to be used for parallel execution using OpenMP.
 * It then fills each subset array with random numbers within the specified lower and upper limits.
 * The random numbers are generated independently in each subset using a different seed for each thread.
 * Finally, it prints a waiting message, waits for all threads to complete using a barrier,
 * and prints a message indicating the completion of array initialization.
 */
void initialize_array_with_random_numbers_using_n_threads(Dynamic_Int_Array_Subset *dynamic_array_subsets, int v_lower_limit, int v_upper_limit, int n_threads){
	printf("\nWating for array initialization...\n");
	omp_set_num_threads(n_threads);

	// Fills the subset arrays with random numbers between the lower and upper limits
	#pragma omp parallel for
    for (int i = 0; i < n_threads; i++) {
		srand(time(NULL));
        for(int j = dynamic_array_subsets[i].lower_range; j < dynamic_array_subsets[i].upper_range; j++){
			dynamic_array_subsets[i].array->array[j] = (rand() % (v_upper_limit - v_lower_limit + 1)) + v_lower_limit;
		}
    }

	#pragma omp barrier
	printf("Array initialized!\n");
}

/**
 * @brief Sums the elements of an array using multiple threads.
 *
 * @param dynamic_array Pointer to the Dynamic_Int_Array object.
 * @param dynamic_array_subsets Pointer to the array of Dynamic_Int_Array_Subset objects.
 * @param n_threads Number of threads to use for summation.
 *
 * This function calculates the sum of the elements in the array by dividing the array
 * into subsets and using multiple threads for parallel summation. Each thread calculates
 * the sum of its assigned subset, and the partial sums are then combined to obtain the
 * final sum of the array. The dynamic_array->sum and dynamic_array_subsets[i].sum fields
 * are updated with the respective sums.
 *
 * @note The dynamic_array and dynamic_array_subsets should be properly initialized.
 * @note The array subsets in dynamic_array_subsets should not overlap and should cover
 *       the entire array.
 * @note The number of threads should be less than or equal to the number of array subsets.
 */
void sum_array_using_n_threads(Dynamic_Int_Array *dynamic_array, Dynamic_Int_Array_Subset *dynamic_array_subsets, int n_threads){
	printf("\nWating for array summation...\n");
	omp_set_num_threads(n_threads);
	dynamic_array->sum = 0;

	#pragma omp parallel for
	for (int i = 0; i < n_threads; i++){
		dynamic_array_subsets[i].sum = 0;
		for(int j = dynamic_array_subsets[i].lower_range; j < dynamic_array_subsets[i].upper_range; j++){
			dynamic_array_subsets[i].sum += dynamic_array_subsets[i].array->array[j];
		}
	}

	#pragma omp barrier
	for(int i = 0; i < n_threads; i++){
		dynamic_array->sum += dynamic_array_subsets[i].sum;
	}
	printf("Array summed!\n");
}

/**
 * @brief Calculates the product of elements in a dynamic array using multiple threads.
 *
 * This function calculates the product of elements in a dynamic array, where each element is mapped to a double value based on specified lower and upper limits.
 * It divides the calculation among multiple threads to improve performance.
 *
 * @param dynamic_array Pointer to the Dynamic_Int_Array structure representing the dynamic array.
 * @param dynamic_array_subsets Pointer to the Dynamic_Int_Array_Subset structure representing the subsets of the dynamic array for each thread.
 * @param v_lower_limit The lower limit for mapping integer elements to double values.
 * @param v_upper_limit The upper limit for mapping integer elements to double values.
 * @param n_threads The number of threads to use for parallel execution.
 */
void prod_array_using_n_threads(Dynamic_Int_Array *dynamic_array, Dynamic_Int_Array_Subset *dynamic_array_subsets, int v_lower_limit, int v_upper_limit, int n_threads){
	double temp_map;
	omp_set_num_threads(n_threads);
	dynamic_array->prod = 1;

	#pragma omp parallel for
	for (int i = 0; i < n_threads; i++){
		dynamic_array_subsets[i].prod = 1;
		for(int j = dynamic_array_subsets[i].lower_range; j < dynamic_array_subsets[i].upper_range; j++){
			temp_map = map_int_to_double(dynamic_array_subsets[i].array->array[j], v_lower_limit, v_upper_limit, _MAP_DOUBLE_MIN, _MAP_DOUBLE_MAX);
			if(dynamic_array_subsets[i].prod > 1){
				dynamic_array_subsets[i].prod *= 1/temp_map;
			}else{
				dynamic_array_subsets[i].prod *= temp_map;
			}	
		}
	}

	printf("\nWating for array prod...\n");
	#pragma omp barrier
	for(int i = 0; i < n_threads; i++){
		dynamic_array->prod *= dynamic_array_subsets[i].prod;
	}
	printf("Array finished prod!\n");
}

/**
 * @brief Finds the minimum and maximum values in a dynamic integer array using multiple threads.
 * 
 * This function divides the dynamic array into subsets and assigns each subset to a separate thread
 * for parallel processing. Each thread finds the minimum and maximum values within its assigned subset.
 * Finally, the overall minimum and maximum values are determined by comparing the results from each thread.
 * 
 * @param dynamic_array A pointer to the dynamic integer array.
 * @param dynamic_array_subsets An array of dynamic integer array subsets.
 * @param n_threads The number of threads to be used for parallel processing.
 */
void find_min_max_using_n_threads(Dynamic_Int_Array *dynamic_array, Dynamic_Int_Array_Subset *dynamic_array_subsets, int n_threads){
	printf("\nWating for finding min and max...\n");
	omp_set_num_threads(n_threads);

	// subset min and max
	#pragma omp parallel for
	for(int i = 0; i < n_threads; i++){
		dynamic_array_subsets[i].min_index = dynamic_array_subsets[i].lower_range;
		dynamic_array_subsets[i].max_index = dynamic_array_subsets[i].lower_range;
		for(int j = dynamic_array_subsets[i].lower_range; j < dynamic_array_subsets[i].upper_range; j++){
			// min
			if(dynamic_array_subsets[i].array->array[j] < dynamic_array_subsets[i].array->array[dynamic_array_subsets[i].min_index]){
				dynamic_array_subsets[i].min_index = j;
			}
			// max
			if(dynamic_array_subsets[i].array->array[j] > dynamic_array_subsets[i].array->array[dynamic_array_subsets[i].max_index]){
				dynamic_array_subsets[i].max_index = j;
			}
		}
	}
	
	#pragma omp barrier
	dynamic_array->min_index = 0;
	dynamic_array->max_index = 0;
	for(int i = 0; i < n_threads; i++){
		int dyn_arr_min = dynamic_array->min_index;
		int dyn_arr_max = dynamic_array->max_index;
		int dyn_arr_sub_min = dynamic_array_subsets[i].min_index;
		int dyn_arr_sub_max = dynamic_array_subsets[i].max_index;
		// overall min
		if(dynamic_array->array[dyn_arr_min] > dynamic_array_subsets[i].array->array[dyn_arr_sub_min]){
			dynamic_array->min_index = dyn_arr_sub_min;
		}
		// overall max
		if(dynamic_array->array[dyn_arr_max] < dynamic_array_subsets[i].array->array[dyn_arr_sub_max]){
			dynamic_array->max_index = dyn_arr_sub_max;
		}
	}
	printf("Min and max found!!\n");
}

/**
 * @brief Merges two sorted subarrays into a single sorted subarray.
 *
 * This function merges the left and right subarrays into the original array 'arr'.
 *
 * @param arr The original array.
 * @param left The left subarray.
 * @param left_length The length of the left subarray.
 * @param right The right subarray.
 * @param right_length The length of the right subarray.
 */
void merge(int arr[], int left[], int left_length, int right[], int right_length) {
    int i = 0, j = 0, k = 0;
    
    while (i < left_length && j < right_length) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    
    while (i < left_length) {
        arr[k++] = left[i++];
    }
    
    while (j < right_length) {
        arr[k++] = right[j++];
    }
}

/**
 * @brief Sorts an array interval using the merge sort algorithm.
 *
 * This function recursively divides the array interval into two halves,
 * sorts them separately, and then merges them back into a single sorted interval.
 *
 * @param arr The array to be sorted.
 * @param start The starting index of the interval.
 * @param end The ending index of the interval.
 */
void merge_sort_subarrays(int arr[], int start, int end) {
    if (start >= end) {
        return;
    }
    
    int mid = start + (end - start) / 2;
    
    // Recursively sort the left and right halves of the interval
    merge_sort_subarrays(arr, start, mid);
    merge_sort_subarrays(arr, mid + 1, end);
    
    // Merge the sorted halves
    int left_length = mid - start + 1;
    int right_length = end - mid;
    int left[left_length];
    int right[right_length];
    
    for (int i = 0; i < left_length; i++) {
        left[i] = arr[start + i];
    }
    
    for (int i = 0; i < right_length; i++) {
        right[i] = arr[mid + 1 + i];
    }
    
    merge(arr + start, left, left_length, right, right_length);
}
void merge_subarrays(Dynamic_Int_Array *dynamic_array){
	for (int i = 0; i < dynamic_array->length - 1; i++) {
        for (int j = 0; j < dynamic_array->length - i - 1; j++) {
            if (dynamic_array->array[j] > dynamic_array->array[j + 1]) {
                int temp = dynamic_array->array[j];
                dynamic_array->array[j] = dynamic_array->array[j + 1];
                dynamic_array->array[j + 1] = temp;
            }
        }
    }
}

void remove_duplicates(Dynamic_Int_Array *dynamic_array) {
	printf("\nWaiting to remove duplicates...\n");
	int new_length = 0;
	for(int i = 1; i < dynamic_array->length - 1; i++){
		if(dynamic_array->array[new_length] != dynamic_array->array[i]){
			new_length++;
			dynamic_array->array[new_length] = dynamic_array->array[i];
		}
	}
	dynamic_array->length = new_length;
	printf("Duplicates removed!\n");
}

void write_array_to_file(Dynamic_Int_Array *dynamic_array){
	// Check if the folder exists
    struct stat st;
    if (stat("logs", &st) == 0 && S_ISDIR(st.st_mode)) {
    }else{
		// Create the folder
    	mkdir("logs", 0700);  // 0700 sets read, write, and execute permissions for the owner only
	}

	// Write file
	time_t rawtime;
    struct tm* timeinfo;
    char timestamp[20];
    char filePath[100];
    FILE* file;

    // Get the current time
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d_%H-%M-%S", timeinfo);
	snprintf(filePath, sizeof(filePath), "%s/%s.txt", "logs", timestamp);

	// Create and write to the text file
    file = fopen(filePath, "w");
    if (file != NULL) {
        fprintf(file, "Original Array length: %d\n", dynamic_array->length);
		fprintf(file, "Original Array Sum: %ld \t\t\t\t- %lf second(s)\n", dynamic_array->sum, important_times[1]);
		fprintf(file, "Original Array Prod: %Lf \t\t\t- %lf second(s)\n", dynamic_array->prod, important_times[2]);
		fprintf(file, "Original Array Min Index: %d \t\t\t- %lf second(s)\n", dynamic_array->min_index, important_times[3]);
		fprintf(file, "Original Array Max Index: %d \t\t\t- %lf second(s)\n", dynamic_array->max_index, important_times[3]);
		fprintf(file, "\nSorted and Duplicates removed Array:\n");
		for(int i = 0; i < dynamic_array->length; i++){
			fprintf(file, "array[%d] = %d\n", i, dynamic_array->array[i]);
		}
        fclose(file);
        printf("\nFile created: %s\n", filePath);
    } else {
        printf("\nFailed to create file: %s\n", filePath);
    }
}

int main(int argc, char *argv[]) {
    starting = clock();
	// ############################################################ Variable Setup ############################################################
	int array_length, value_lower_limit, value_upper_limit, number_of_threads;
	Dynamic_Int_Array *dynamic_array = (Dynamic_Int_Array*) malloc(sizeof(Dynamic_Int_Array));
	Dynamic_Int_Array_Subset *dynamic_array_subsets;

	// Error setup
	Error *error = (Error*) malloc(sizeof(Error));
	throw_new_error(NO_ERROR, error);

	// ########################################################## Argument Handleing ##########################################################
	check_argument_validity(argc, argv, error);
	array_length = atoi(argv[1]);
	value_lower_limit = atoi(argv[2]);
	value_upper_limit = atoi(argv[3]);
	number_of_threads = atoi(argv[4]);

	// Check if given arguments are within range
	if(!is_within_range(array_length, _ARRAY_LENGTH_MIN, _ARRAY_LENGTH_MAX, error)){
		if(error->type){
			print_error(error);
			printf("\nThe given array length is outside of the acceptable range! [0, 10.000]\n");
			exit(1);
		}
		printf("The given array length is outside of the acceptable range! [0, 10.000]\n");
		exit(1);
	}

	if(!is_within_range(value_lower_limit, _ELEMENT_LIMIT_MIN, _ELEMENT_LIMIT_MAX, error)){
		if(error->type){
			print_error(error);
			printf("\nThe given value lower limit is outside of the acceptable range! [0, 100]\n");
			exit(1);
		}
		printf("The given value lower limit is outside of the acceptable range! [0, 100]\n");
		exit(1);
	}

	if(!is_within_range(value_upper_limit, _ELEMENT_LIMIT_MIN, _ELEMENT_LIMIT_MAX, error)){
		if(error->type){
			print_error(error);
			printf("\nThe given value upper limit is outside of the acceptable range! [0, 100]\n");
			exit(1);
		}
		printf("The given value upper limit is outside of the acceptable range! [0, 100]\n");
		exit(1);
	}

	if(!is_valid_range(value_lower_limit, value_upper_limit)){
		printf("Upper range is lower than lower range!\n");
		exit(1);
	}

	if(!is_within_range(number_of_threads, _NUMBER_OF_THREADS_MIN, _NUMBER_OF_THREADS_MAX, error)){
		if(error->type){
			print_error(error);
			printf("\nThe given number of thread(s) is outside of the acceptable range! [1, 10]\n");
			exit(1);
		}
		printf("The given number of thread(s) is outside of the acceptable range! [1, 10]\n");
	}

	printf("\nArray length: %d\n", array_length);
	printf("Value lower limit: %d\n", value_lower_limit);
	printf("Value upper limit: %d\n", value_upper_limit);
	printf("Number of threads: %d\n\n", number_of_threads);

	// ############################################################ Initialization ############################################################
	init_dynamic_int_array(dynamic_array, array_length, error);
	if(error->type){
		print_error(error);
		exit(1);
	}

	dynamic_array_subsets = (Dynamic_Int_Array_Subset*) malloc(number_of_threads * sizeof(Dynamic_Int_Array_Subset));
	initialize_array_subsets(dynamic_array, dynamic_array_subsets, array_length, number_of_threads);

	for(int i = 0; i < number_of_threads; i++){
		printf("Subset Array [%d]: [%d, %d)\n", i, dynamic_array_subsets[i].lower_range, dynamic_array_subsets[i].upper_range);
	}

	// ########################################################## Calculations ################################################################
	// Array filling with random numbers
	start_clock();
	initialize_array_with_random_numbers_using_n_threads(dynamic_array_subsets, value_lower_limit, value_upper_limit, number_of_threads);
	stop_clock();
	important_times[0] = get_elapsed_time();
	printf("Time to fill the array: %lf second(s)\n", important_times[0]);

	// Array sum
	start_clock();
	sum_array_using_n_threads(dynamic_array, dynamic_array_subsets, number_of_threads);
	stop_clock();
	important_times[1] = get_elapsed_time();
	printf("Time to sum the array: %lf second(s)\nSum: %ld\n", important_times[1], dynamic_array->sum);

	// Array prod mapped to [1.0, 1.1]
	start_clock();
	prod_array_using_n_threads(dynamic_array, dynamic_array_subsets, value_lower_limit, value_upper_limit, number_of_threads);
	stop_clock();
	important_times[2] = get_elapsed_time();
	printf("Time to prod the array: %lf second(s)\nProd: %Lf\n", important_times[2], dynamic_array->prod);

	// Finding first min and first max of the array
	start_clock();
	find_min_max_using_n_threads(dynamic_array, dynamic_array_subsets, number_of_threads);
	stop_clock();
	important_times[3] = get_elapsed_time();
	printf("Time to find min and max in the array: %lf second(s)\nMin index: %d\nMax index: %d\n", important_times[3], dynamic_array->min_index, dynamic_array->max_index);

	// Array sorting
	printf("\nWaiting for array sorting...\n");
	start_clock();
	#pragma omp parallel for
	for(int i = 0; i < number_of_threads; i++){
		merge_sort_subarrays(dynamic_array->array, dynamic_array_subsets[i].lower_range, dynamic_array_subsets[i].upper_range - 1);
	}
	#pragma omp barrier
	merge_subarrays(dynamic_array);
	stop_clock();
	important_times[4] = get_elapsed_time();
	printf("Array is sorted!\n");
	printf("Time to sort arrays: %lf second(s)\n", important_times[4]);

	// Remove duplicates in array
	start_clock();
	remove_duplicates(dynamic_array);
	stop_clock();
	important_times[5] = get_elapsed_time();
	printf("Time to remove duplicates: %lf second(s)\n", important_times[5]);

	// Write to file
	start_clock();
	write_array_to_file(dynamic_array);
	stop_clock();
	printf("Time it took to write to file: %lf\n", get_elapsed_time());

    ending = clock();
	elapsed_time = ((double) (ending - starting)) / CLOCKS_PER_SEC;

	printf("\n\n%lf\n", elapsed_time);
	return 0;
}