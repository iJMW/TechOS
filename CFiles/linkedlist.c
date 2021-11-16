#include "../HeaderFiles/linkedlist.h"

LQueue *userQueue = NULL;

//Initialize the FQueue to null head and tail
void initializeLQueue(LQueue *q){
    q->head = NULL;
    q->tail = NULL;
}

//Returns the length of the queue
int Llength(LQueue *q){
    int count = 0;
    LNode *temp = q->head;
    while(temp != NULL){
        count++;
        temp = temp->next;
    }

    return count;
}

//Return true if both the head and tail are null
bool isLEmpty(LQueue *q){
    return q->head == NULL && q->tail == NULL;
}

LNode *Lpeek(LQueue *q){
    return q->head;
}

LNode *Ldequeue(LQueue *q){
    //Then we do not have a queue
    if(q->head != NULL){
        //Are these two lines necessary?
        //Preserve the value of q->head
        LNode *temp = q->head;
        //Get the result to be returned
        LNode *result = temp;

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
User *Lcontains(LQueue *q, char username[100], char password[100]){
    if(q->head != NULL){
        LNode *temp = q->head;
        while(temp != NULL){
            //If the value of temp is equivalent to the val then return true
            if(strcmp(temp->user->username, username) == 0 && strcmp(temp->user->password, password) == 0){
                return temp->user;
            }
            temp = temp->next;
        }
    }
    //Otherwise, return false
    return NULL;
}

//Returns true if the value is in the queue
int userNameTaken(LQueue *q, char username[100]){
    if(q->head != NULL){
        LNode *temp = q->head;
        while(temp != NULL){
            //If the value of temp is equivalent to the val then return true
            if(strcmp(temp->user->username, username) == 0){
                return 1;
            }
            temp = temp->next;
        }
    }
    //Otherwise, return false
    return 0;
}

void Lenqueue(LQueue *q, User *user){
    //Increase the number of faults and create the newNodes
    LNode *newNode = (LNode *)malloc(sizeof(LNode));
    newNode->user = user;
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

void removeFromLQueue(LQueue *q, User *user){
    LNode *temp = q->head;
    LNode *prev = NULL;
    while(temp != NULL){
        if(strcmp(temp->user->username, user->username) == 0){
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
void printLinkedList(LQueue *q){
    LNode *temp = q->head;
    printf("[ ");
    while(temp != NULL){
        printf("\n[%s, %s, %d]", temp->user->username, temp->user->password, temp->user->access);
        temp = temp->next;
    }
    printf("]");
}