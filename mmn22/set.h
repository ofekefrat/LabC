#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NUM 127
#define NUM_MAX_LENGTH 4
#define SECTIONS 4
#define SECTION_SIZE 32
#define NUM_OF_SETS 6
#define DECIMAL_BASE 10
#define LINE_PRINT_LENGTH 16
#define COMMON_ARG_AMOUNT 3
#define COMMAND_MAX_LENGTH 15
#define SET_NAME_MAX_LENGTH 5
#define INPUT_LINE_MAX_LENGTH 666

/* STRUCTURES */
typedef struct section {
    unsigned long value : SECTION_SIZE;
}section;

typedef struct set {
    section sections[SECTIONS];
}set;

/* METHODS */
typedef struct set* pSet;
void emptySet(pSet);
void addMember(pSet,int);

int getSetName(int,FILE*);
void getSetMembers(pSet,FILE*);
void readLine(int*,FILE*);
void read_set(pSet,pSet);
void print_set(pSet,int*);
void union_set(pSet,pSet,pSet);
void intersect_set(pSet,pSet,pSet);
void sub_set(pSet,pSet,pSet);
void symdiff_set(pSet,pSet,pSet);
void actuallyPrint(pSet);

#endif /*SET_H*/
