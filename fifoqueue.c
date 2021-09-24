#include "HeaderFiles/fifoqueue.h"

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
    if(q->head != NULL){
        FNode *temp = q->head;
        while(temp != NULL){
            //If the value of temp is equivalent to the val then return true
            if(strcmp(temp->pcb->processName, processName) == 0){
                return temp;
            }
            temp = temp->next;
        }
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

//Outputs the PQueue for testing
void printFIFOQueue(FQueue *q){
    FNode *temp = q->head;
    printf("[ ");
    while(temp != NULL){
        printf("%s, ", temp->pcb->processName);
        temp = temp->next;
    }
    printf("]");

    // PNode *temp = q->head;
    // PNode *temp2 = temp->next;
    // printf("%s\n", temp->pcb->processName);
    // if (temp2 != NULL) {
    //     printf("%s\n", temp2->pcb->processName);
    // }
}