/*
 This program finds ascending alphabetic sequences of at least 3 letters within a string inputted through stdin,
 and shortens the string by replacing each sequence with its first letter, a hyphen, and then the last letter.
 The program also prints the inputted string before the changes and after.

 Assumptions: the string's length is <= 80
*/

#include "abc.h"

void abc(char*);

int main() {

    char input[MAXLENGTH]; /*The inputted string*/

    printf("Please enter a string: \n");
    (scanf("%80s", input));
    printf("You entered: %s\n", input);
    abc(input);
    printf("Result: %s\n", input);

    return 0;
}

void abc(char* str) { /*shortens the string as described at the top*/

    int i, hyphenInd, flag=0; /*hyphenInd: index for hyphen. flag: counter for consecutive following letters */
    char tempStr[MAXLENGTH]; /* a temporary string for manipulation purposes */

    for (i=1; i < strlen(str); i++) {
        if (!flag && isalpha(str[i])) {
            if (str[i] == str[i-1]+1) {
                hyphenInd = i;
                flag = 1;
            }
        }
        else if (flag) {
            if (str[i] == str[i-1]+1) {
                if (i == strlen(str)-1 || str[i+1] != str[i]+1) {
                    strcpy(tempStr, str + i);/*using tempStr to keep the rest of the string*/
                    str[hyphenInd] = '\0';/*cutting the string from the index to the end*/
                    strcat(str, "-"); /*adding the hyphen*/
                    strcat(str, tempStr); /*adding the rest of the string back*/
                    flag = 0;
                    i = hyphenInd;
                }
            }
            else
                flag = 0;
        }
    }
}

