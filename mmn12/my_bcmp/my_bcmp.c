//
// Created by ofeke on 29/11/2022.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "my_bcmp.h"

int main() {

    char input[STR_MAX_LENGTH];
    int b1, b2, len;

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
}

void inputCheck(char* str, int b1, int b2, int len) {

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

int getNumberFromStdin() {

    char str[INT_MAX_LENGTH];
    char* trash;
    int i;

    if (fgets(str, INT_MAX_LENGTH, stdin) == NULL) { // QUESTIONABLE!!!!!!!
        printf("Error handling input\n");
        exit(0);
    }

    for (i=0; i<strlen(str)-1; i++) {
        if (!isdigit(str[i])) {
            printf("ERROR: Not a non-negative decimal integer\n");
            exit(0);
        }
    }

    return strtol(str, &trash, DECIMAL_BASE);
}

int my_bcmp(const void* b1, const void* b2, int len) {

    int i;
    const char* pb1 = b1;
    const char* pb2 = b2;
    size_t b1_size = strlen(pb1);
    size_t b2_size = strlen(pb2);

    if ( (b1_size == 0 && b2_size == 0)
        || len == 0)
        return 0;

    for (i=0; i < b1_size && i < b2_size && i < len; i++) {
        if (pb1[i] != pb2[i])
            return -1;
    }
    return 0;
}