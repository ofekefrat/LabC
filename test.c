//
// Created by ofeke on 30/11/2022.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
    char str[5];
    char *trash;
    int i,x;

    if (fgets(str, 5, stdin) == NULL)
        printf("Number is too long. maximum length is 512");

    printf("%llu\n", strlen(str));
    for (i=0; i<strlen(str);i++) {
        printf("%c", str[i]);
    }
    for (i=0; i<strlen(str)-1; i++) {
        if (!isdigit(str[i])) {
            printf("Non-digit entered\n");
        }
    }

    printf("%ld", strtol(str, &trash, 10)+1);
}