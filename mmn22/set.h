#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ERROR (-1)
#define SECTIONS 8
#define MAX_NUM 127
#define NUM_OF_SETS 6
#define DECIMAL_BASE 10
#define SECTION_SIZE 16
#define NUM_MAX_LENGTH 4
#define COMMON_ARG_AMOUNT 3
#define LINE_PRINT_LENGTH 16
#define COMMAND_MAX_LENGTH 15
#define SET_NAME_MAX_LENGTH 5
#define INPUT_LINE_MAX_LENGTH 666

/* STRUCTURES */

typedef struct section {
    unsigned int value : SECTION_SIZE;
}section;

typedef struct set {
    section sections[SECTIONS];
}set;

typedef struct set* pSet;

/* METHODS */

/* emptySet: truncate the entire contents of the set pointed to by the pointer argument.*/
void emptySet(pSet);

/* addMember: Add the number in the argument as a member to the set pointed to by the pointer.*/
void addMember(pSet,int);

/* getSetName: reads a word from the input buffer passed in the argument, expecting it to be a defined set name
 * and returning its index in the set array if everything is correct.
 * The first argument should be 0 if the word is not the final operator, meaning a comma is to be expected at the end,
 * and 1 if the word is the final word to be expected. If any problems are found, prints a detailed error message
 * and terminates the current operation, waiting for a new command.*/
int getSetName(int,FILE*);

/* getSetMembers: method to help read_set receive all integers from the rest of the input buffer passed by the argument,
 * and making sure they're all in range and all numbers, and that the line was correctly terminated by -1.
 * The method defines a temporary set to be copied from by read_set, and then sends it
 * on its way if everything is in order. If any problems are found, prints a detailed error message
 * and terminates the current operation, waiting for a new command.*/
void getSetMembers(pSet,pSet,FILE*);

/* readLine: method to correctly read 3 set names from the input buffer passed by the argument,
 * for use in all basic set operation methods (union_set, intersect_set, sub_set and symdiff_set)
 * the method saves the indexes in the array pointed to by the pointer argument, to be used.
 * If any problems are found, prints a detailed error message and terminates the current operation,
 * waiting for a new command.*/
void readLine(int*,FILE*);

/* read_set: method to redefine the set pointed to by the first argument, with the members of the temporary set
 * passed by getSetMembers in the second argument.*/
void read_set(pSet,pSet);

/* print_set: method to read all members from the set pointed to by the argument. The method then saves
 * all existing values in the integer array pointed to by the second argument, for the actuallyPrint method to.. well..
 * ACTUALLY print the values. If the set is empty, the method instead returns a single value (-1) to the array,
 * letting actuallyPrint know that the set was empty.*/
void print_set(pSet,int*);

/* union_set: method to perform the union operation on the two sets pointed to by the first two arguments,
 * and laying the result on the set in the third argument.*/
void union_set(pSet,pSet,pSet);

/* intersect_set: method to perform intersection on the two sets pointed to by the first two arguments,
 * and laying the result on the set in the third argument.*/
void intersect_set(pSet,pSet,pSet);

/* sub_set: method to subtract the members from the set in the second argument, from the set in the first argument,
 * and laying the result on the set in the third argument.*/
void sub_set(pSet,pSet,pSet);

/* symdiff_set: method to perform the symmetric difference operation on the two sets pointed to by
 * the first two arguments, and laying the result on the set in the third argument.*/
void symdiff_set(pSet,pSet,pSet);

/* actuallyPrint: method to print out all members of the set pointed to by the argument,
 * beginning and ending with curly brackets, and spaces in between.
 * If the set is empty, prints a message accordingly instead.*/
void actuallyPrint(pSet);

#endif /*SET_H*/
