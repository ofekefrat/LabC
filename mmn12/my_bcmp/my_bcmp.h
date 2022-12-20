#ifndef my_bcmp_h
#define my_bcmp_h

#define STR_MAX_LENGTH 512 /*max length of string from input*/
#define INT_MAX_LENGTH 5 /*value used for testing int input*/
#define MAX_ACCEPTABLE_CHARACTERS 3 /*value used for testing int input*/
#define DECIMAL_BASE 10
#define POSITIVE_RESULT 0 /*value to be returned in case of positive result*/
#define NEGATIVE_RESULT (-1) /*value to be returned in case of a negative result*/

int my_bcmp(const void*,const void*,int); /*compares bytes against each other (according to input
                                            * values requested by program)
                                            * if all corresponding bytes are equal, prints 0. if attempting to
                                            * compare 0 bytes, prints 0 as well.
                                            * otherwise, prints -1.*/


int getNumberFromStdin(void); /*receives a string from stdin and casts to an integer if the string represents
                                * a non-negative integer, meaning only digits are acceptable.
                                * if anything else is given, prints an error message and exits the program.*/


void inputCheck(char*,int,int,int); /*checks whether all values received from user are valid, meaning no index will
                                        * go out of bounds during the program. If an invalid value is found,
                                        * prints a detailed error message and exits the program.*/

#endif /*my_bcmp_h*/
