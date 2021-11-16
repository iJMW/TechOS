#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "customprocess.h"
#include <string.h>

#ifndef MYFIFOQUEUE_H_
#define MYFIFOQUEUE_H_

typedef struct FNode {
    PCB *pcb;
    struct FNode *next;
}FNode;

typedef struct FQueue {
    FNode *head;
    FNode *tail;
    int count;
}FQueue;

extern FQueue *blockedQueue;

//Function Prototypes
void initializeFQueue(FQueue *q);
int Flength(FQueue *q);
bool isFEmpty(FQueue *q);
FNode *Fpeek(FQueue *q);
FNode *Fdequeue(FQueue *q);
FNode *Fcontains(FQueue *q, char processName[9]);
void Fenqueue(FQueue *q, PCB *p);
void removeFromFQueue(FQueue *q, PCB *p);
void printFIFOQueue(FQueue *q);

#endif