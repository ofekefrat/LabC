/*
 *
 * */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "my_bcmp.h"

int main() {

    char input[STR_MAX_LENGTH]; /* string from user */
    int b1, b2, len; /* b1,b2: indexes from user. len: length to be tested (from user)*/

    printf("Please enter len\n");
    len = getNumberFromStdin();
    printf("Len: %d", len);

    printf("Please enter index #1\n");
    b1 = getNumberFromStdin();
    printf("Index #1: %d", b1);

    printf("Please enter index #2\n");
    b2 = getNumberFromStdin();
    printf("Index #2: %d", b2);

    printf("Please enter a string\n");
    fgets(input, STR_MAX_LENGTH, stdin);
    printf("String entered: %s", input);

    inputCheck(input, b1, b2, len);

    printf("The value returned from test: %d", my_bcmp(&input[b1], &input[b2], len));

    return 0;
}

void inputCheck(char* str, int b1, int b2, int len) { /* Checking if all the required input is valid */

    if (b1 > strlen(str)) {
        printf("ERROR: First index is out of string's bounds\n");
        exit(0);
    }
    if (b2 > strlen(str)) {
        printf("ERROR: Second index is out of string's bounds\n");
        exit(0);
    }
    if (len + b1 > strlen(str)) {
        printf("ERROR: Program will go out of string's bounds from first index\n");
        exit(0);
    }
    if (len + b2 > strlen(str)) {
        printf("ERROR: Program will go out of string's bounds from second index\n");
        exit(0);
    }
}

int getNumberFromStdin() { /* Receiving an integer (and only an integer) from the user */

    char str[INT_MAX_LENGTH]; /* char array to test if everything will be read correctly */
    char* trash; /* pointer to dump unnecessary value from strtol*/
    int i;

    if (fgets(str, INT_MAX_LENGTH, stdin) == NULL) { /* Checking if input was received successfully */
        printf("Error handling input\n");
        exit(0);
    }

    for (i=0; i<strlen(str)-1; i++) {
        if (!isdigit(str[i])) { /* Checking if all characters from input are digits, otherwise it's not a (non-negative) integer */
            printf("ERROR: Not a non-negative decimal integer\n");
            exit(0);
        }
    }

    return strtol(str, &trash, DECIMAL_BASE);
}

int my_bcmp(const void* b1, const void* b2, int len) { /* the required test*/

    int i;
    const char* pb1 = b1; /* type casting to access the values of items in array */
    const char* pb2 = b2;
    size_t b1_size = strlen(pb1); /* length of string from each index */
    size_t b2_size = strlen(pb2);

    if ( (b1_size == 0 && b2_size == 0) /* if both "strings" (from indexes) are empty, they are equal */
        || len == 0) /* if we check 0 items, they are equal by default */
        return 0;

    for (i=0; i < b1_size && i < b2_size && i < len; i++) {
        if (pb1[i] != pb2[i])
            return -1;
    }
    return 0;
}