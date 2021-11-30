/*
   Names: Logan Bland
          John Clay
          Jalen Wayt
   Assignment: Module 2 - Process Scheduling
   Purpose: Implement Scheduling queues and process creation
   Due Date: September 28, 2021
*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include "HeaderFiles/login.h"
#include "HeaderFiles/comhan.h"
#include "HeaderFiles/customprocess.h"
#include "HeaderFiles/linkedlist.h"

//Main method that calls COMHAN function
int main() {
    //Initialize Ready Queue
    readyQueue = (PQueue *)malloc(sizeof(PQueue));
    initializePQueue(readyQueue);
    //Initialize Blocked Queue
    blockedQueue = (FQueue *)malloc(sizeof(FQueue));
    initializeFQueue(blockedQueue);
    //Initialize History Queue
    history = (HQueue *)malloc(sizeof(HQueue));
    initializeHQueue(history);
    // Initialize the user queue
    userQueue = (LQueue *)malloc(sizeof(LQueue));
    initializeLQueue(userQueue);


    User * validUser = (User *)malloc(sizeof(User));
    int terminate = 0;
    do {
        validUser = LOGIN();
        // Read all account after each login? If no, fix
        // If yes, write changes to user.txt during session
        if(validUser != NULL){
            COMHAN(validUser);
        } else {
            printf("\nInvalid Login");
        }
        free(userQueue);
    } while(true);
    
    return 0;
}

