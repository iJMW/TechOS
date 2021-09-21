#include "customprocess.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    PCB *pcb;
    Node *next;
}Node;

typedef struct Queue {
    Node *head;
    Node *tail;
    int count;
}Queue;

//Initialize the Queue to null head and tail
void initializeQueue(Queue *q){
    q->head = NULL;
    q->tail = NULL;
}

//Returns the length of the queue
int length(Queue *q){
    int count = 0;
    Node *temp = q->head;
    while(temp != NULL){
        count++;
        temp = temp->next;
    }

    return count;
}

//Return true if both the head and tail are null
bool isEmpty(Queue *q){
    return q->head == NULL && q->tail == NULL;
}

Node *peek(Queue *q){
    return q->head;
}

Node *dequeue(Queue *q){
    //Then we do not have a queue
    if(q->head != NULL){
        //Are these two lines necessary?
        //Preserve the value of q->head
        Node *temp = q->head;
        //Get the result to be returned
        Node *result = temp;

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
bool contains(Queue *q, char *str){
    Node *temp = q->head;
    while(temp != NULL){
        //If the value of temp is equivalent to the val then return true
        if(strcmp(temp->pcb->processName, str) == 0){
            return true;
        }
        temp = temp->next;
    }

    //Otherwise, return false
    return false;
}

void enqueue(Queue *q, PCB *p){
    // Create a new node
    Node *newNode = (Node *)malloc(sizeof(Node));
    // Set the new node's PCB to the passed PCB
    newNode->pcb = p;
    
    // If the queue is empty, inserted new PCB to the front
    if(q->head == NULL) {
        q->head = newNode;
        q->tail = q->head;
    } else { // If the queue is not empty, inserted new PCB to appropriate location based on priority
        Node *prev = NULL;
        Node *temp = q->head;
        while(temp != NULL){
            if (temp->pcb->priority > p->priority) {
                prev->next = newNode;
                newNode->next = temp;
                break;
            }
            prev = temp;
            temp = temp->next;
        }
    }

    // If the newNode was not inserted, add it to the end of the queue
    if(newNode->next == NULL && q->count > 0) {
        q->tail->next = newNode;
        q->tail = newNode;
    }

    // Increase the count of nodes within the queue
    q->count = q->count + 1;
}

//Outputs the Queue for testing
// void printQueue(Queue *q){
//     Node *temp = q->head;
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