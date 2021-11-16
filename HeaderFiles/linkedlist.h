#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "customprocess.h"
#include <string.h>
#include "login.h"

#ifndef MYLINKEDLIST_QUEUE_H_
#define MYLINKEDLIST_QUEUE_H_

typedef struct LNode {
    User *user;
    struct LNode *next;
}LNode;

typedef struct LQueue {
    LNode *head;
    LNode *tail;
    int count;
}LQueue;

extern LQueue *userQueue;

//Function Prototypes
void initializeLQueue(LQueue *q);
int Llength(LQueue *q);
bool isLEmpty(LQueue *q);
LNode *Lpeek(LQueue *q);
LNode *Ldequeue(LQueue *q);
User *Lcontains(LQueue *q, char username[100], char password[100]);
void Lenqueue(LQueue *q, User *u);
void removeFromLQueue(LQueue *q, User *u);
void printLinkedList(LQueue *q);

#endif