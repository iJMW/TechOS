#include "customprocess.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct PNode {
    PCB *pcb;
    struct PNode *next;
}PNode;

typedef struct PQueue {
    PNode *head;
    PNode *tail;
    int count;
}PQueue;

//Initialize the PQueue to null head and tail
void initializePQueue(PQueue *q){
    q->head = NULL;
    q->tail = NULL;
}

//Returns the length of the queue
int Plength(PQueue *q){
    int count = 0;
    PNode *temp = q->head;
    while(temp != NULL){
        count++;
        temp = temp->next;
    }

    return count;
}

//Return true if both the head and tail are null
bool isPEmpty(PQueue *q){
    return q->head == NULL && q->tail == NULL;
}

PNode *Ppeek(PQueue *q){
    return q->head;
}

PNode *Pdequeue(PQueue *q){
    //Then we do not have a queue
    if(q->head != NULL){
        //Are these two lines necessary?
        //Preserve the value of q->head
        PNode *temp = q->head;
        //Get the result to be returned
        PNode *result = temp;

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
PNode* Pcontains(PQueue *q, char *str){
    PNode *temp = q->head;
    while(temp != NULL){
        //If the value of temp is equivalent to the val then return true
        if(strcmp(temp->pcb->processName, str) == 0){
            return temp;
        }
        temp = temp->next;
    }

    //Otherwise, return false
    return NULL;
}

void Penqueue(PQueue *q, PCB *p){
    // Create a new PNode
    PNode *newPNode = (PNode *)malloc(sizeof(PNode));
    // Set the new PNode's PCB to the passed PCB
    newPNode->pcb = p;
    
    // If the queue is empty, inserted new PCB to the front
    if(q->head == NULL) {
        q->head = newPNode;
        q->tail = q->head;
    } else { // If the queue is not empty, inserted new PCB to appropriate location based on priority
        PNode *prev = NULL;
        PNode *temp = q->head;
        while(temp != NULL){
            if (temp->pcb->priority > p->priority) {
                prev->next = newPNode;
                newPNode->next = temp;
                break;
            }
            prev = temp;
            temp = temp->next;
        }
    }

    // If the newPNode was not inserted, add it to the end of the queue
    if(newPNode->next == NULL && q->count > 0) {
        q->tail->next = newPNode;
        q->tail = newPNode;
    }

    // Increase the count of PNodes within the queue
    q->count = q->count + 1;
}

void removeFromPQueue(PQueue *q, PCB *p){
    PNode *temp = q->head;
    PNode *prev = NULL;
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

//Outputs the PQueue for testing
// void printQueue(PQueue *q){
//     PNode *temp = q->head;
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