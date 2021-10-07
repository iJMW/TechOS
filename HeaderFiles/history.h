#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef HISTORY_H_
#define HISTORY_H_

typedef struct HNode {
    char *input;
    struct HNode *next;
}HNode;

typedef struct HQueue {
    HNode *head;
    HNode *tail;
}HQueue;

extern HQueue *history;

//Function Prototypes
void initializeHQueue(HQueue *q);
int Hlength(HQueue *q);
bool isHEmpty(HQueue *q);
HNode *Hpeek(HQueue *q);
HNode *Hdequeue(HQueue *q);
void Henqueue(HQueue *q, char *userInput);
void printHistoryQueue(HQueue *q);

#endif