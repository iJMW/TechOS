#include "../HeaderFiles/priorityqueue.h"

//Initialize the PQueue to null head and tail
void initializePQueue(PQueue *q){
    //q = (PQueue *)malloc(sizeof(PQueue));
    q->head = NULL;
    q->tail = NULL;
    q->count = 0;
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

        //Remove the head of the queue
        q->head = q->head->next;

        //if the head is null, then the tail is also null
        if(q->head == NULL){
            q->tail = NULL;
        }

         // Update the length of the queue
        q->count = q->count - 1;

        return temp;
    }

    return NULL;
}

//Returns true if the value is in the queue
PNode* Pcontains(PQueue *q, char *str){
    if(q->head != NULL){
        PNode *temp = q->head;
        while(temp != NULL){
            //If the value of temp is equivalent to the val then return true
            if(strcmp(temp->pcb->processName, str) == 0){
                return temp;
            }
            temp = temp->next;
        }
    }
    //Otherwise, return false
    return NULL;
}

void Penqueue(PQueue *q, PCB *p){
    // Create a new PNode
    PNode *newPNode = (PNode *)malloc(sizeof(PNode));
    // Set the new PNode's PCB to the passed PCB
    newPNode->pcb = p;
    newPNode->next = NULL;

    // If the queue is empty, inserted new PCB to the front
    if(q->head == NULL) {
        q->head = newPNode;
        q->tail = q->head;
    } else { // If the queue is not empty, inserted new PCB to appropriate location based on priority
        PNode *prev = NULL;
        PNode *temp = q->head;
        while(temp != NULL){
            if (temp->pcb->priority > p->priority) {
                if (prev != NULL) {
                    prev->next = newPNode;
                }else{
                    q->head = newPNode;
                }
                
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
                // If we are removing the tail
                if (strcmp(temp->pcb->processName, q->tail->pcb->processName) == 0) {
                    q->tail = prev;
                }
                prev->next = temp->next;
            } else{
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
    // Decrease the count of PNodes within the queue
    q->count = q->count - 1;
}

//Outputs the PQueue for testing
void printPriorityQueue(PQueue *q){
    PNode *temp = q->head;
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