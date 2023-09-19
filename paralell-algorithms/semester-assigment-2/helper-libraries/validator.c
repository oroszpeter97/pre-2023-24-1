#include "validator.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool is_int(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

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

void check_argument_validity(int argc, char *argv[]){
	if (argc != 2 && argc != 5) {
        printf("Invalid arguments!\n");
		exit(0);
	}

	if (argc == 2 && strcmp(argv[1], "-help") == 0) {
		display_help(argv[0]);
		exit(0);
	} else if (argc == 5) {
		for(int i = 1; i < 5; i++){
			if(!is_int(argv[i])){
                printf("Argument conversion error!\n");
				exit(1);
			}
		}
	} else {
        printf("Invalid arguments!\n");
		exit(1);
	}
}
