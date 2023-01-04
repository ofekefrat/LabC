#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NUM 127
#define NUM_MAX_LENGTH 4
#define SECTIONS 2
#define SECTION_SIZE 64
#define NUM_OF_SETS 6
#define DECIMAL_BASE 10
#define LINE_PRINT_LENGTH 16
#define COMMON_ARG_AMOUNT 3
#define COMMAND_MAX_LENGTH 15
#define SET_NAME_MAX_LENGTH 5

/* STRUCTURES */
typedef struct section {
    unsigned long long val : 64;
}section;

typedef struct set {
    section sections[2];
}set;

/* METHODS */
typedef struct set* pSet;
void emptySet(pSet);
void addMember(pSet,int);

int getSetName(int);
void getSetMembers(pSet);
void readLine(int*);
void read_set(pSet,pSet);
void print_set(pSet,int*);
void union_set(pSet,pSet,pSet);
void intersect_set(pSet,pSet,pSet);
void sub_set(pSet,pSet,pSet);
void symdiff_set(pSet,pSet,pSet);

#endif //SET_H
