#include <stdio.h>
#include "../HeaderFiles/priorityqueue.h"
#include "../HeaderFiles/fifoqueue.h"

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

PCB *SetUpPCB(char processName[9], int processClass, int priority, char *filePath) {
    PCB *p = AllocatePCB();
    if(p != NULL){
        strcpy(p->processName, processName);
        p->processClass = processClass;
        p->priority = priority;
        p->state = 1;
        p->suspended = 0;
        p->offset = 0;
        p->data = filePath;
        InsertPCB(p);    
    } else {
        printf("Memory errors...Not inserting process into queue\n");
    }
    return p;
}

PCB *FindPCB(char processName[9]) {
    PCB *p = NULL;
    if (Pcontains(readyQueue, processName) != NULL) {
        p = Pcontains(readyQueue, processName)->pcb;
    }
    if (p == NULL) {
        if (Fcontains(blockedQueue, processName) != NULL) {
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
}

char *RemovePCB(PCB *p, int remInd) {
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

        // Free the pointer if the process is being removed, not moved to a different queue
        if (remInd == 1) {//Change this to FreePCB instead of free
            FreePCB(p);
        }
        // Return the success messsage
        return "SUCCESS";
    } else { // Else the PCB is not present in one of the queues
        return "ERROR: PCB was not found in any queues";
    }
}
