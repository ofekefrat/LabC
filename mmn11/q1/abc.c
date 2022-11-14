/*
I assume the string's length is <=80
*/

#include "abc.h"

void abc(char*);

int main() {

    char input[MAXLENGTH];

    printf("Please enter a string literal: \n");
    if (scanf("%80s", input)) {
        printf("You entered: %s\n", input);
        abc(input);
        printf("Result: %s\n", input);
    }

    return 0;
}

void abc(char* str) {

    int i, hyphenInd, flag=0; /*hyphenInd: index for hyphen. flag: counter for consecutive following letters */
    char tempStr[MAXLENGTH]; /* a temporary string for manipulation purposes */

    for (i=1; i < strlen(str); i++) {
        if (flag==0 && isalpha(str[i])) { /**/
            if (str[i] == str[i-1]+1) {
                hyphenInd = i;
                flag = 1;
            }
        }
        else if (flag==1) {
            if (str[i] == str[i-1]+1) {
                if (i == strlen(str)-1 || str[i+1] != str[i]+1) {
                    strcpy(tempStr, str + i);/*using tempStr to keep the rest of the string*/
                    str[hyphenInd] = '\0';
                    strcat(str, "-"); /*adding the hyphen*/
                    strcat(str, tempStr); /*adding the rest of the string back*/
                    flag = 0;
                }
            }
            else
                flag = 0;
        }
    }
}

