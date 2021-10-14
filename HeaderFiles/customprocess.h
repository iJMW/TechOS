#include <stdio.h>

#ifndef MYCUSTOMPROCESS_H_
# define MYCUSTOMPROCESS_H_
typedef struct PCB {
    char processName[9];
    int processClass;
    int priority;
    int state;
    int suspended;
    char *data;
    int offset;
}PCB;

PCB *AllocatePCB();
char *FreePCB(PCB *p);
PCB *SetUpPCB(char processName[9], int processClass, int priority, char *filePath);
PCB *FindPCB(char processName[9]);
void InsertPCB(PCB *p);
char *RemovePCB(PCB *p, int remInd);

#endif



