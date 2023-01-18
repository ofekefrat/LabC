#ifndef LABC_PERMUT_H
#define LABC_PERMUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REQ_ARG_COUNT 3
#define EMPTY (-2)

/* STRUCTS & RELATED METHODS */

typedef struct node {
    char key;
    struct node* next;
}node;

typedef node* pNode;

typedef struct queue {
    pNode front, rear;
}queue;

typedef queue* pQueue;

pNode newNode(char c) {
    pNode temp = (pNode) malloc(sizeof(node));
    temp->key = c;
    temp->next = NULL;
    return temp;
}

pQueue createQueue() {
    pQueue q = (pQueue) malloc(sizeof(queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void enQueue(pQueue q, char c) {
    pNode temp = newNode(c);
    if (q->rear == NULL) {
        q->front = temp;
        q->rear = temp;
        return;
    }

    q->rear->next = temp;
    q->rear=temp;
}

void deQueue(pQueue q) {
    if (q->front == NULL)
        return;

    pNode temp = q->front;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
}

/* METHODS */



#endif
