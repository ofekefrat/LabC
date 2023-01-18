#ifndef LABC_PERMUT_H
#define LABC_PERMUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REQ_ARG_COUNT 3
#define EMPTY (-2)

/* STRUCTS */

typedef struct node {
    char key;
    struct node* next;
}node;

typedef node* pNode;

typedef struct queue {
    pNode front, rear;
}queue;

typedef queue* pQueue;


/* METHODS */

pNode newNode(char);
pQueue createQueue(void);
void enQueue(pQueue,char);
void deQueue(pQueue);
int isNodeInBank(pNode,char*);
int isWordValid(pQueue,char*);
void printWord(pQueue,size_t);

#endif
