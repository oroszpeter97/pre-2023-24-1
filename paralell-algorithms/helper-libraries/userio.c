#include "userio.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/**
 * Maximum number of digits.
*/
#define DIGITS 5
/**
 * Account for sign character, newline, and 0 terminator
*/
#define BUFF_SIZE (DIGITS)+3

/**
 * @retval int : User inputed int if no error occured.
 * @retval -1 : Read Error.
 * @retval -2 : Buffer overflow.
 * @retval -3 : Not a valid integer type.
 * @retval -4 : Negative number.
*/
int read_positive_int_user_input(){
    char input_buffer[BUFF_SIZE];
    char *chk;
    int num;
    
    if (!fgets(input_buffer, sizeof input_buffer, stdin)) // read error on input
        return -1;
    
    /**
     * Make sure the user didn't enter a string longer than the buffer
     * was sized to hold by looking for a newline character.  If a newline 
     * isn't present, we reject the input and read from the stream until
     * we see a newline or get an error.
     */
    if (!strchr(input_buffer, '\n')){ // input too long
        while (fgets(input_buffer, sizeof input_buffer, stdin) && !strchr(input_buffer, '\n'));
        return -2;
    }

    num = (int) strtol(input_buffer, &chk, 10);

    /**
     * chk points to the first character not converted.  If
     * it's whitespace or 0, then the input string was a valid
     * integer
     */
    if (isspace(*chk) || *chk == 0){
        if (num < 0)
            return -4;

        return num;
    }else
        return -3;

    
}