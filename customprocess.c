#include <stdio.h>
#include "HeaderFiles/priorityqueue.h"
#include "HeaderFiles/fifoqueue.h"

PQueue *readyQueue = NULL;
FQueue *blockedQueue = NULL;

//Look up how to catch errors
PCB *AllocatePCB() {
    PCB *p = (PCB *)malloc(sizeof(PCB));
    return p;
}

//How to catch errors
char *FreePCB(PCB *p) {
    if(p == NULL){
        return "ERROR: PCB was never allocated";
    }

    free(p);
    return "SUCCESS";
}

PCB *SetUpPCB(char processName[9], int processClass, int priority) {
    PCB *p = AllocatePCB();
    if(p != NULL){
        strcpy(p->processName, processName);
        p->processClass = processClass;
        p->priority = priority;
        p->state = 1;
        p->suspended = 0;
        InsertPCB(p);    
    }
    return p;
}

PCB *FindPCB(char processName[9]) {
    if (readyQueue == NULL) {
        readyQueue = (PQueue *)malloc(sizeof(PQueue));
        initializePQueue(readyQueue);
    }
    if (blockedQueue == NULL) {
        blockedQueue = (FQueue *)malloc(sizeof(FQueue));
        initializeFQueue(blockedQueue);
    }
    PCB *p = NULL;
    if (Pcontains(readyQueue, processName) != NULL) {
        printf("PCB found in PQueue\n");
        p = Pcontains(readyQueue, processName)->pcb;
    }
    if (p == NULL) {
        if (Fcontains(blockedQueue, processName) != NULL) {
            printf("PCB found in FQueue\n");
            p = Fcontains(blockedQueue, processName)->pcb;
        }
    }
    return p;
}

void InsertPCB(PCB *p) {
    
    //State 1 is ready
    if(p->state == 1){
        Penqueue(readyQueue, p);
    }else{//State 0 is blocked
        Fenqueue(blockedQueue, p);
    }

    printf("\nInserting: \n");
    printf("Ready: ");
    printPriorityQueue(readyQueue);
    printf("\n\nBlocked: ");
    printFIFOQueue(blockedQueue);
}

char *RemovePCB(PCB *p) {
     // If the PCB is present in one of the queues
    if (FindPCB(p->processName) != NULL) {
        // Determine which queue to remove it from
        if (Pcontains(readyQueue, p->processName)) {
            // Remove from ready queue
            removeFromPQueue(readyQueue, p);
        } else {
            // Remove from blocked queue
            removeFromFQueue(blockedQueue, p);
        }
        printf("\nRemoving: \n");
        printf("Ready: ");
        printPriorityQueue(readyQueue);
        printf("\n\nBlocked: ");
        printFIFOQueue(blockedQueue);
        // Return the success messsage
        return "SUCCESS";
    } else { // Else the PCB is not present in one of the queues
        return "ERROR: PCB was not found in any queues";
    }
}
