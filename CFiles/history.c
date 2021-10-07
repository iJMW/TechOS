#include "../HeaderFiles/history.h"

HQueue *history = NULL;

//Initialize the HQueue to null head and tail
void initializeHQueue(HQueue *q){
    q->head = NULL;
    q->tail = NULL;
}

//Returns the length of the queue
int Hlength(HQueue *q){
    int count = 0;
    HNode *temp = q->head;
    while(temp != NULL){
        count++;
        temp = temp->next;
    }

    return count;
}

//Return true if both the head and tail are null
bool isHEmpty(HQueue *q){
    return q->head == NULL && q->tail == NULL;
}

HNode *Hpeek(HQueue *q){
    return q->head;
}

HNode *Hdequeue(HQueue *q){
    //Then we do not have a queue
    if(q->head != NULL){
        //Are these two lines necessary?
        //Preserve the value of q->head
        HNode *temp = q->head;
        //Get the result to be returned
        HNode *result = temp;

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

void Henqueue(HQueue *q, char *userInput){
    //Increase the number of faults and create the newNodes
    HNode *newNode = (HNode *)malloc(sizeof(HNode));
    newNode->input = userInput;
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

//Outputs the PQueue for testing
void printHistoryQueue(HQueue *q){
    HNode *temp = q->head;
    while(temp != NULL){
        printf("%s\n", temp->input);
        temp = temp->next;
    }
}