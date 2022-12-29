#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NUM 127
#define SECTIONS 2
#define SECTION_SIZE 64
#define NUM_OF_SETS 6
#define DECIMAL_BASE 10
#define LINE_PRINT_LENGTH 16

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

int getSetName();
void redefine(pSet);
void print(pSet);
void unionize(pSet);
void intersect(pSet);
void subset(pSet);
void symmetricDiff(pSet);

#endif //SET_H
