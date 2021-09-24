#include "customprocess.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef MYPRIORITYQUEUE_H_
#define MYPRIORITYQUEUE_H_
typedef struct PNode {
    PCB *pcb;
    struct PNode *next;
}PNode;

typedef struct PQueue {
    PNode *head;
    PNode *tail;
    int count;
}PQueue;

//Function Prototypes
void initializePQueue(PQueue *q);
int Plength(PQueue *q);
bool isPEmpty(PQueue *q);
PNode *Ppeek(PQueue *q);
PNode *Pdequeue(PQueue *q);
PNode* Pcontains(PQueue *q, char *str);
void Penqueue(PQueue *q, PCB *p);
void removeFromPQueue(PQueue *q, PCB *p);
void printPriorityQueue(PQueue *q);

#endif