/*
 * This program compares a given amount of bytes (len) against each other, starting from two given indexes,
 * in a given string, all provided by the user. Indexes must be within range of the string, and the len must not
 * lead the program out of the string's bounds (from either of the indexes). If the value in all corresponding bytes
 * is equal, the program prints 0, otherwise -1. if len is 0, the program returns 0.
 * Assumption: Maximum length of string input is 512.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "my_bcmp.h"

int main() {

    char input[STR_MAX_LENGTH]; /* string from user */
    int ind1, ind2, len; /* ind1,ind2: indexes from user. len: number of bytes to be tested (from user)*/

    printf("Please enter number of bytes to test\n");
    len = getNumberFromStdin();

    printf("Please enter index #1\n");
    ind1 = getNumberFromStdin();

    printf("Please enter index #2\n");
    ind2 = getNumberFromStdin();

    printf("Please enter the string\n");
    fgets(input, STR_MAX_LENGTH, stdin);

    printf("Len: %d\n", len);
    printf("Index #1: %d\n", ind1);
    printf("Index #2: %d\n", ind2);
    printf("String entered: %s\n", input);

    inputCheck(input, ind1, ind2, len);

    printf("Test result: %d\n", my_bcmp(&input[ind1], &input[ind2], len)); /* printing the result */

    return 0;
}

void inputCheck(char* str, int b1, int b2, int len) { /* Checking if all the required input is valid */

    if (b1 >= strlen(str)) {
        printf("ERROR: First index is out of string's bounds\n");
        exit(0);
    }
    if (b2 >= strlen(str)) {
        printf("ERROR: Second index is out of string's bounds\n");
        exit(0);
    }
    if (len > strlen(str)) {
        printf("ERROR: Number of bytes to compare is greater than string's length\n");
        exit(0);
    }
    if (len + b1 >= strlen(str)) {
        printf("ERROR: Program will go out of string's bounds from first index\n");
        exit(0);
    }
    if (len + b2 >= strlen(str)) {
        printf("ERROR: Program will go out of string's bounds from second index\n");
        exit(0);
    }
}

int getNumberFromStdin() { /* Receiving an integer (and only an integer) from the user and returning it as an int */

    char str[INT_MAX_LENGTH]; /* char array to test if everything will be read correctly */
    char* trash; /* pointer to dump unnecessary value from strtol */
    int i;

    if (fgets(str, INT_MAX_LENGTH, stdin) == NULL) { /* Checking if input was received successfully */
        printf("Error handling input\n");
        exit(0);
    }

    if (strlen(str) == 1) {
        printf("ERROR: No number has been entered\n");
        exit(0);
    }

    for (i=0; i<strlen(str)-1; i++) {
        if (!isdigit(str[i])) { /* Checking if all characters from input are digits, otherwise it's not a
                                    * (non-negative) integer */
            printf("ERROR: Not a non-negative decimal integer\n");
            exit(0);
        }
    }

    if (strlen(str) > MAX_ACCEPTABLE_CHARACTERS) {
        printf("ERROR: Number is too long, program will exceed assumed maximal bounds (512)\n");
        exit(0);
    }

    return strtol(str, &trash, DECIMAL_BASE); /* converting the string to an integer in base 10 and returning it */
}

int my_bcmp(const void* b1, const void* b2, int len) { /* the required test */

    int i;
    const char* pb1 = b1; /* type casting to access the values of items in array */
    const char* pb2 = b2;
    size_t b1_size = strlen(pb1); /* length of string from each index */
    size_t b2_size = strlen(pb2);

    if (len == 0) /* if we check 0 items, they are equal by default */
        return POSITIVE_RESULT;

    for (i=0; i < b1_size && i < b2_size && i < len; i++) {
        if (pb1[i] != pb2[i])
            return NEGATIVE_RESULT;
    }
    return POSITIVE_RESULT;
}