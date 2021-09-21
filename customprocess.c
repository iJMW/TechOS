#include <stdio.h>
#include "HeaderFiles/priorityqueue.h"
#include "HeaderFiles/fifoqueue.h"

PQueue *readyQueue;
FQueue *blockedQueue;

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

PCB *SetupPCB(char processName[9], int processClass, int priority) {
    PCB *p = AllocatePCB();
    if(p != NULL){
        strcpy(p->processName, processName);
        p->processClass = processClass;
        p->priority = priority;
    }

    return p;
}

PCB *FindPCB(char processName[9]) {
    PCB *p = Pcontains(readyQueue, processName)->pcb;
    if (p == NULL) {
        p = Fcontains(blockedQueue, processName)->pcb;
    }
    
    return p;
}

void InsertPCB(PCB *p) {
    //State ai0 is ready?????
    if(p->state == 0){
        Penqueue(readyQueue, p);
    }else{//Otherwise in blocking?????
        Fenqueue(blockedQueue, p);
    }
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
        // Return the success messsage
        return "SUCCESS";
    } else { // Else the PCB is not present in one of the queues
        return "ERROR: PCB was not found in any queues";
    }
}
