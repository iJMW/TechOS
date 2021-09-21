#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "customprocess.h"
#include <string.h>

typedef struct FNode {
    PCB *pcb;
    struct FNode *next;
}FNode;

typedef struct FQueue {
    FNode *head;
    FNode *tail;
    int count;
}FQueue;

//Initialize the FQueue to null head and tail
void initializeFQueue(FQueue *q){
    q->head = NULL;
    q->tail = NULL;
}

//Returns the length of the queue
int Flength(FQueue *q){
    int count = 0;
    FNode *temp = q->head;
    while(temp != NULL){
        count++;
        temp = temp->next;
    }

    return count;
}

//Return true if both the head and tail are null
bool isFEmpty(FQueue *q){
    return q->head == NULL && q->tail == NULL;
}

FNode *Fpeek(FQueue *q){
    return q->head;
}

FNode *Fdequeue(FQueue *q){
    //Then we do not have a queue
    if(q->head != NULL){
        //Are these two lines necessary?
        //Preserve the value of q->head
        FNode *temp = q->head;
        //Get the result to be returned
        FNode *result = temp;

        //Remove the head of the queue
        q->head = q->head->next;

        //if the head is null, then the tail is also null
        if(q->head == NULL){
            q->tail = NULL;
        }

        return result;
    }

    return NULL;
}

//Returns true if the value is in the queue
FNode *Fcontains(FQueue *q, char processName[9]){
    FNode *temp = q->head;
    while(temp != NULL){
        //If the value of temp is equivalent to the val then return true
        if(strcmp(temp->pcb->processName, processName) == 0){
            return temp;
        }
        temp = temp->next;
    }

    //Otherwise, return false
    return NULL;
}

void Fenqueue(FQueue *q, PCB *p){
    //Increase the number of faults and create the newNodes
    FNode *newNode = (FNode *)malloc(sizeof(FNode));
    newNode->pcb = p;
    newNode->next = NULL;

    //If the tail is not null, then set the tail's next element to the newNode
    if(q->tail != NULL){
        q->tail->next = newNode;
    }
    //Set the tail to be the newNode
    q->tail = newNode;

    //If there is no head, then make the newNode the head
    if(q->head == NULL){
        q->head = newNode;
    }
}

void removeFromFQueue(FQueue *q, PCB *p){
    FNode *temp = q->head;
    FNode *prev = NULL;
    while(temp != NULL){
        if(strcmp(temp->pcb->processName, p->processName) == 0){
            if(prev != NULL){
                prev->next = temp->next;
            }else{
                q->head = temp->next;
                if (q->head == NULL) {
                    q->tail = NULL;
                }
            }
            break;
        }
        prev = temp;
        temp = temp->next;
    }
}

//Outputs the FQueue for testing
// void printQueue(FQueue *q){
//     FNode *temp = q->head;
//     printf("[ ");
//     while(temp != NULL){
//         if(temp == q->tail){
//             printf("%d ]", temp->processNum);
//         }else{
//             printf("%d, ", temp->processNum);
//         }
        
//         temp = temp->next;
//     }
// }