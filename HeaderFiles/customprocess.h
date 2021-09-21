#include <stdio.h>

#ifndef MYCUSTOMPROCESS_H_
# define MYCUSTOMPROCESS_H_
typedef struct PCB {
    char processName[9];
    int processClass;
    int priority;
    int state;
}PCB;

PCB *AllocatePCB();
char *FreePCB(PCB *p);
PCB *SetupPCB(char processName[9], int processClass, int priority);
PCB *FindPCB(char processName[9]);
void InsertPCB(PCB *p);
char *RemovePCB(PCB *p);

#endif



