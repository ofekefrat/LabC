#include "permut.h"

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
    pNode temp;
    if (q->front == NULL)
        return;

    temp = q->front;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
}
