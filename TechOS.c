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
#include "HeaderFiles/comhan.h"
#include "HeaderFiles/customprocess.h"

//Main method that calls COMHAN function
int main(){
    readyQueue = (PQueue *)malloc(sizeof(PQueue));
    initializePQueue(readyQueue);
    blockedQueue = (FQueue *)malloc(sizeof(FQueue));
    initializeFQueue(blockedQueue);
    //Call the COMHAN function to execute the program
    COMHAN();

    return 0;
}
