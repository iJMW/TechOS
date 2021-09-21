typedef struct PCB {
    char processName[9];
    int processClass;
    int priority;
    int states;
}PCB;

void AllocatePCB();
void FreePCB();
void SetupPCB();
void FindPCB();
void InsertPCB();
void RemovePCB();



