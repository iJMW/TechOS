#include "../HeaderFiles/comhan.h"
#include "../HeaderFiles/customprocess.h"
#include "../HeaderFiles/helpermethods.h"

//Total Number of days in each month
//int numDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//Global Variables for keeping track of parameters and if the user chose to quit
int numParameters;
int didUserQuit = 0;

//Used for keeping track of the time and date of the system
time_t currentTime;
struct tm tm;

//Global Variable for the struct DateDifference
DateDifference dateDiff;

//Function controls flow of program
void COMHAN(){
    //Initialize the date difference elements
    dateDiff.numDays = 0;
    dateDiff.numMonths = 0;
    dateDiff.numYears = 0;
    //Initialize the time
    currentTime = time(NULL);
    tm = *localtime(&currentTime);

    //Size of input
    size_t size = 50;
    //UserInput will store the specific command
    char *userInput = (char *)malloc(size * sizeof(char));
    //Stores the parameters
    char *parameters[size];
    
    //While the user chooses not to quit, display the CLI
    while(didUserQuit == 0){
        printf("\nTechOS > ");
        //Allocate memory for the string
        char *str = (char *)malloc(size * sizeof(char));
        //Declare the delimiters, a whitespace and \n is the delimeter
        char delim[] = " \n";
        //Get the line
        getline(&str, &size, stdin);
        
        //Iterate over the string
        numParameters = 0;
        //Get the first portion
        str = strtok(str, delim);
        while(str != NULL){
            if(numParameters == 0){ // Store the command the user wants to run
                userInput = str;
                convertToLowercase(userInput);
            }else{  // Store the parameters 
                parameters[numParameters - 1] = str;
                convertToLowercase(parameters[numParameters-1]);
            }
            // Tokenize the same line by passing NULL
            str = strtok(NULL, delim);
            // Increase the number of parameters
            numParameters++;
        }

        // If no parameters were passed, set the parameters to be ""
        if(numParameters == 1){
            parameters[0] = "";
        }

        // Reduce numParameters by one to not include the command being ran
        // e.g. dont include 'help' in the parameter cound when user entered
        // 'help version'
        numParameters = numParameters - 1;
        
        // Run the specific command entered by the user, pass the parameters to the command if needed
        if(strcmp(userInput, CMD_HELP) == 0 || strcmp(userInput, INPUT_HELP) == 0){
            Help(parameters[0]);
        }else if(strcmp(userInput, CMD_VERSION) == 0 || strcmp(userInput, INPUT_VERSION) == 0){
            Version();
        }else if(strcmp(userInput, CMD_DATE) == 0 || strcmp(userInput, INPUT_DATE) == 0){
            DisplayDate();
        }else if(strcmp(userInput, CMD_CDDATE) == 0 || strcmp(userInput, INPUT_CDDATE) == 0){
            ChangeDate(parameters[0]);
        }else if(strcmp(userInput, CMD_TIME) == 0 ||strcmp(userInput, INPUT_TIME) == 0){
            DisplayTime();
        }else if(strcmp(userInput, CMD_QUIT) == 0 || strcmp(userInput, INPUT_QUIT) == 0){
            TerminateTechOS();
        }else if(strcmp(userInput, CMD_CREATE_PCB) == 0 || strcmp(userInput, INPUT_CREATE_PCB) == 0){
            createPCB(parameters[0], parameters[1], parameters[2]);
        }else if(strcmp(userInput, CMD_DELETE_PCB) == 0 || strcmp(userInput, INPUT_DELETE_PCB) == 0){
            deletePCB(parameters[0]);
        }else if(strcmp(userInput, CMD_SETPRIORITY) == 0 || strcmp(userInput, INPUT_SETPRIORITY) == 0){
            setPriority(parameters[0], parameters[1]);
        }else if(strcmp(userInput, CMD_SUSPEND) == 0 || strcmp(userInput, INPUT_SUSPEND) == 0){
            suspend(parameters[0]);
        }else if(strcmp(userInput, CMD_RESUME) == 0 || strcmp(userInput, INPUT_RESUME) == 0){
            resume(parameters[0]);
        }else if(strcmp(userInput, CMD_BLOCK) == 0 || strcmp(userInput, INPUT_BLOCK) == 0){
            block(parameters[0]);
        }else if(strcmp(userInput, CMD_UNBLOCK) == 0 || strcmp(userInput, INPUT_UNBLOCK) == 0){
            unblock(parameters[0]);
        }else if(strcmp(userInput, CMD_SHPCB) == 0 || strcmp(userInput, INPUT_SHPCB) == 0){
            showPCB(parameters[0]);
        }else if(strcmp(userInput, CMD_SHALLPCB) == 0 || strcmp(userInput, INPUT_SHALLPCB) == 0){
            showAllPCB();
        }else if(strcmp(userInput, CMD_SHOW_READY_PROCESSES) == 0 || strcmp(userInput, INPUT_SHOW_READY_PROCESSES) == 0){
            ShowReadyProcesses();
        }else if(strcmp(userInput, CMD_SHOW_BLOCKED_PROCESSES) == 0 || strcmp(userInput, INPUT_SHOW_BLOCKED_PROCESSES) == 0){
            ShowBlockedProcesses();
        }else if(strcmp(userInput, "hist") == 0 || strcmp(userInput, "hist") == 0){
            printHistoryQueue(history);
        }else{
            printf("Unrecognized command. Please try again.");
        }

        //Free the str variable
        free(str);
    }

    //Free the userInput variable
    free(userInput);
}

// Displays a help description to the user based on the command passed
void Help(char* cmdName){
    // Check the number of parameters passed with the help command
    if (numParameters != 1 && numParameters != 0) { // If too many parameters passed, display an error message
        printf("Invalid number of parameters. The format for the '%s' command is: '%s' or '%s {{command name}}'", CMD_HELP, CMD_HELP, CMD_HELP);
    } else { // Else, display the proper help file
        // Determine which command the user wants to view and 
        if (strcmp(cmdName, CMD_HELP) == 0) { // Print the help file for the help command
            printFile("help.txt");
        } else if (strcmp(cmdName, CMD_VERSION) == 0) { // Print the help file for the version command
            printFile("version.txt");
        } else if (strcmp(cmdName, CMD_DATE) == 0) { // Print the help file for the date command
            printFile("date.txt");
        } else if (strcmp(cmdName, CMD_CDDATE) == 0) { // Print the help file for the chdate command
            printFile("chdate.txt");
        } else if (strcmp(cmdName, CMD_TIME) == 0) { // Print the help file for the time command
            printFile("time.txt");
        } else if (strcmp(cmdName, CMD_QUIT) == 0) { // Print the help file for the quit command
            printFile("quit.txt");
        } else if (strcmp(cmdName, CMD_SHPCB) == 0) { // Print the help file for the shpcb command
            printFile("shpcb.txt");
        } else if (strcmp(cmdName, CMD_SHALLPCB) == 0) { // Print the help file for the shallpcb command
            printFile("shallpcb.txt");
        } else if (strcmp(cmdName, CMD_SHOW_READY_PROCESSES) == 0) { // Print the help file for the shready command
            printFile("shready.txt");
        } else if (strcmp(cmdName, CMD_SHOW_BLOCKED_PROCESSES) == 0) { // Print the help file for the shblocked command
            printFile("shblocked.txt");
        } else if (strcmp(cmdName, CMD_BLOCK) == 0) { // Print the overview help
            printFile("block.txt");
        } else if (strcmp(cmdName, CMD_UNBLOCK) == 0) { // Print the overview help
            printFile("unblock.txt");
        } else if (strcmp(cmdName, CMD_CREATE_PCB) == 0) { // Print the overview help
            printFile("crprocess.txt");
        } else if (strcmp(cmdName, CMD_DELETE_PCB) == 0) { // Print the overview help
            printFile("delprocess.txt");
        } else if (strcmp(cmdName, CMD_SETPRIORITY) == 0) { // Print the overview help
            printFile("setpr.txt");
        } else if (strcmp(cmdName, CMD_SUSPEND) == 0) { // Print the overview help
            printFile("suspend.txt");
        } else if (strcmp(cmdName, CMD_RESUME) == 0) { // Print the overview help
            printFile("resume.txt");
        } else if (strcmp(cmdName, "") == 0) { // Print the overview help
            printFile("overview.txt");
        } else { // Print an error for unknown command
            printf("Command not found: %s", cmdName);
        }
    }
}

// Print the version number, authors, and completion
void Version(){
    if (numParameters != 0) {
        printf("Too many parameters. The format for the '%s' command is: %s", CMD_VERSION, CMD_VERSION);
    } else {
        printf("Version Number: %s\n", VERSION_NUMBER);
        printf("Authors: %s\n", AUTHORS);
        printf("Completion Date: %s", COMPLETION_DATE);
    }
}

//Displays the current date for the user
void DisplayDate(){
    //No parameters should be passed with this command
    if(numParameters != 0){
        printf("Too many parameters. The format for the '%s' command is: %s", CMD_DATE, CMD_DATE);
    }else{
        //Refreshes the time variable
        currentTime = time(NULL);
        tm = *localtime(&currentTime);

        //Outputs the date
        printf("%s %d, %d", getMonth(tm.tm_mon + dateDiff.numMonths), tm.tm_mday + dateDiff.numDays, tm.tm_year + 1900 + dateDiff.numYears);
    }
}

/*
 * When the user issues the command chdate ##-##-####,
 * the string provided is tokenized and iterated over to get the month, day and year.
 * The date is then set to those parameters.
 */
void ChangeDate(char *parameters){
    //There should only be one parameter, if there are more this is incorrect
    if(numParameters != 1){
        printf("Invalid number of parameters. The format for the '%s' command is: %s {{MM-DD-YYYY}}", CMD_CDDATE, CMD_CDDATE);
    }else{
        //Define the size of the string
        size_t size = 20;
        //Allocate memory for the string
        char *str = (char *)malloc(size * sizeof(char));
        //Declare the delimiters, hyphens are the delimiters but it will also skip over the space at the beginning
        char delim[] = "-";

        //Declare an array of char pointers (strings)
        int *date = (int *)malloc(size * sizeof(int));
        int month, day, year;

        //Iterate over the string
        int i = 0;
        //Get the first portion
        str = strtok(parameters, delim);
        while(str != NULL && i < 3){
            date[i] = atoi(str);
            str = strtok(NULL, delim);
            i++;
        }
        //Free the str pointer
        free(str);

        //Assign the variables
        month = date[0];
        day = date[1];
        year = date[2];

        //If the checkMonth method returns 1, continue
        if(checkMonth(month - 1, day, year) == 1){
            calculateDateDifference(month-1, day, year);

            //Print the date for the user to verify that it was changed properly
            printf("Changed date to: ");
            numParameters = 0;
            DisplayDate();
        }else{//Otherwise, display an error message
            printf("Invalid date selection. Please try again.");
        }
        
        //Free the date pointer
        free(date);
    }
}

//Displays the current system time
void DisplayTime(){
    //There should not be any parameters with this command
    if (numParameters != 0) {
        printf("Too many parameters. The format for the '%s' command is: %s", CMD_TIME, CMD_TIME);
    } else {
        //Refreshes the time variable
        currentTime = time(NULL);
        tm = *localtime(&currentTime);

        //Displays AM time
        if(tm.tm_hour < 13){
            //If the minutes are single digits, print a 0 with it
            if(tm.tm_min < 10){
                printf("%d : 0%d AM \n" , tm.tm_hour, tm.tm_min);
            }else{ //If they aren't, print normally
                printf("%d : %d AM \n" , tm.tm_hour, tm.tm_min);
            }
        } //Displays PM time
        else{
            //If the minutes are single digits, print a 0 with it
            if(tm.tm_min < 10){
                printf("%d : 0%d PM \n" , tm.tm_hour - 12, tm.tm_min);
            }else{//If they aren't, print normally
                printf("%d : %d PM \n" , tm.tm_hour - 12, tm.tm_min);
            }
        }
    }
}

//Terminates the TechOS program
void TerminateTechOS(){
    //There should not be any parameters with this command
    if(numParameters != 0){
        printf("Too many parameters. The format for the '%s' command is: %s", CMD_QUIT, CMD_QUIT);
    }else{
        //Used for while loop
        int one = 1;
        //Keep track of user input
        char in;
        //Ensures the user wants to quit the program
        printf("Are you sure you would like to exit (y/n)?: ");
        // While the user has not entered 'y' or 'n' to confirm termination
        while(one == 1){
            scanf(" %c" , &in);
            // If the user enters 'y', quit the TechOS
            if(in == 'y'){ 
                didUserQuit = 1;
                printf("Goodbye!");
                exit(0);
            } else if (in == 'n') { // If the user entered 'n', break the loop and return to the COMHAN
                one = 0;
            } else{ // Else, print invalid selection
                printf("Invalid command, please try again: ");
            }
        }
        //Get the leftover characters in the input buffer
        while(getchar() != '\n');
    }
}

void createPCB(char *name, char *class, char *priority)
{   
    if(numParameters != 3){
        printf("Invalid number of parameters. The format for the '%s' command is: %s {{processName}} {{processClass}} {{priority}}", CMD_CREATE_PCB, CMD_CREATE_PCB);
    }else{
        if (strlen(name) > 8){
            printf("Error: Process name must be less than 8 characters!");
        }else if (!isNumber(class)) {
            printf("Please provide numbers for the class\n");
        }else if (!isNumber(priority)){
             printf("Please provide numbers for the priority\n");
        }else if(atoi(priority) < 0 || atoi(priority) > 9){
            printf("Error: Priority must be between 0 and 9");
        }else if(FindPCB(name) != NULL){ //name must be unique
            printf("Error: Process name must be Unique!");
        }else if((atoi(class) != 1) && (atoi(class) != 2)){ //must be of appropriate class
            printf("Error: Process class must be 1 (System Process) or 2 (Application Process)!");
        }else{ //if conditions met create the PCB
            SetUpPCB(name, atoi(class), atoi(priority));
            printf("Created process %s", name);
        }
    }
}

// Delete the PCB from the appropriate queue
void deletePCB(char *processName) {
    if(numParameters != 1){
        printf("Invalied number of parameters. The format for the '%s' command is: %s {{processName}}", CMD_BLOCK, CMD_BLOCK);
    }else{
        // Find the PCB then remove it
        PCB *p = FindPCB(processName);
        // If the process is present in one of the queues, remove it
        if (p != NULL) {
            //printf("\n%s\n", RemovePCB(p, 1));
            if(strcmp(RemovePCB(p, 1), "SUCCESS") == 0){
                printf("Deleted process %s", processName);
            }else{
                printf("Process %s could not be deleted", processName);
            }
            
        }else{
            printf("ERROR: Process %s does not exist\n", processName);
        }
    }
}

// Place a process in the blocked time
void block(char *processName) {
    if (numParameters != 1) {
         printf("Invalied number of parameters. The format for the '%s' command is: %s {{processName}}", CMD_BLOCK, CMD_BLOCK);
    } else {
        // Get the PCB
        PCB *p = FindPCB(processName);
        // If the process name is not a valid length
        if (strlen(processName) > 9) {
            printf("Error: Process name must be less than 8 characters\n");
        } else if (p == NULL) { // If the process is not present within one of the queues
            printf("Process of name %s not found...\n", processName);
        } else if (p->state == 0) {
            printf("Process of name %s is already blocked\n", processName);
        }else { // Remove the process from its current queue, put it in blocked state, then reinsert it
            // Remove the PCB from its current queue
            RemovePCB(p, 0);
            // Blocked state is represented by integer 0
            p->state = 0;
            printf("Process %s blocked", processName);
            // Insert PCB into appropriate queue
            InsertPCB(p);
        }
    }
}

//Unblock a PCB and remove it from the blocked queue and insert into the ready queue
void unblock(char *processName) {
    if(numParameters != 1){
        printf("Invalid number of parameters. The format for the '%s' command is: %s {{processName}}", CMD_UNBLOCK, CMD_UNBLOCK);
    }else{
        //Get the PCB
        PCB *p = FindPCB(processName);
        //If the length of the name is more than 8, return an error
        if(strlen(processName) > 8){
            printf("Error: Process name must be less than 8 characters");
        }else if(p == NULL){//If the process does not exist, tell the user
            printf("Error: Process of name %s does not exist\n", processName);
        }else if(p->state == 1){
            printf("Error: Process of name %s is already unblocked\n", processName);
        }else{//Otherwise, remove the PCB from its current queue
            //Remove from current queue
            RemovePCB(p, 0);
            //Set the state to 1 (1 = ready)
            p->state = 1;
            printf("Process %s unblocked", processName);
            //Insert into queue
            InsertPCB(p);
        }
    }
}

void setPriority(char *processName, char *priority){
    if(numParameters != 2){
        printf("Invalid number of parameters. The format for the '%s' command is: %s {{processName}} {{priority}}", CMD_SETPRIORITY, CMD_SETPRIORITY);
    }else{
        if (strlen(processName) > 8){
            printf("Error: Process name must be less than 8 characters!");
        }else if (!isNumber(priority)){
             printf("Please provide numbers for the priority\n");
        }else{
            PCB *p = FindPCB(processName);
            
            if(p == NULL){
                printf("ERROR: Process %s does not exist\n", processName);
            }
            else{
                int newPriority = atoi(priority);
        
                if(p->priority == newPriority){
                        printf("Error: Process of name %s already has priority %d!\n", processName, newPriority);
                    }else{
                        p->priority = newPriority;

                        if(Pcontains(readyQueue, processName)){
                            RemovePCB(p, 0);
                            InsertPCB(p);
                        }
                    }
                }
        }
    }
}

void suspend(char *processName){
    if(numParameters != 1){
        printf("Invalid number of parameters. The format for the '%s' command is: %s {{processName}}", CMD_UNBLOCK, CMD_UNBLOCK);
    }else{

        PCB *p = FindPCB(processName);
        if(strlen(processName) > 8){
            printf("Error: Process name must be less than 8 characters");
        }else if(p == NULL){//If the process does not exist, tell the user
            printf("Error: Process of name %s does not exist\n", processName);
        }else if(p->suspended == 1){
            printf("Error: Process of name %s is already suspended!\n", processName);
        }else{//change suspended state
            //Set the suspended to 1 (1 = suspended)
            p->suspended = 1;
            printf("Process %s suspended", processName);
        }
    }
}

void resume(char *processName){
    if(numParameters != 1){
        printf("Invalid number of parameters. The format for the '%s' command is: %s {{processName}}", CMD_UNBLOCK, CMD_UNBLOCK);
    }else{
        PCB *p = FindPCB(processName);
        if(strlen(processName) > 8){
            printf("Error: Process name must be less than 8 characters");
        }else if(p == NULL){//If the process does not exist, tell the user
            printf("Error: Process of name %s does not exist\n", processName);
        }else if(p->suspended == 0){
            printf("Error: Process of name %s is already resumed!\n", processName);
        }else{//change suspended state
            //Set suspended to 0 (0 = not suspended)
            p->suspended = 0;
            printf("Process %s resumed", processName);
        }

    }
}

// Displays the name, class, state, suspended staus, and priority of the process
void showPCB(char *processName) {

    // Check the number of parameters
   if (numParameters != 1) {
       printf("Invalid number of parameters. The format for the '%s' command is: %s {{processName}}", CMD_SHPCB, CMD_SHPCB);
   } else { // If the correct number of parameters are passed
        // Find the PCB with the passed name
        PCB *p = FindPCB(processName);

        // If no process with the passed name is found
        if (p == NULL) {
            printf("No process was found with the name %s", processName);
        } else { // Else, find print the process information
            printf("Process Name: %s\n", p->processName);
            printf("Class: %s\n", getClass(p->processClass));
            printf("State: %s\n", getState(p->state));
            printf("Suspended Status: %s\n", getSuspendedStatus(p->suspended));
            printf("Priority: %d\n", p->priority);
        }
   }

}

// Displays the name, class, state, suspended staus, and priority of the process
void showAllPCB() {
    // Check for valid number of parameters
    if(numParameters > 0) {
         printf("Invalid number of parameters. The format for the '%s' command is: %s", CMD_SHALLPCB, CMD_SHALLPCB);
    } else {
        // Display the ready queue
        ShowReadyProcesses();
        // Display the blocked queu
        ShowBlockedProcesses();
    }
}

void ShowReadyProcesses(){
    if(numParameters > 0){
        printf("Invalid number of parameters. The format for the '%s' command is: %s", CMD_SHOW_READY_PROCESSES, CMD_SHOW_READY_PROCESSES);
    }else{
        //Need to figure out how to test for null readyQueue???
        //Was this fixed by the main initialization of the queues?
        PNode *temp = readyQueue->head;

        if(temp == NULL){
            printf("There are no processes in the ready queue.");
        }else{
            printf("\n------------------All Processes in the Ready Queue------------------");
            while(temp != NULL){
                printf("\nProcess Name: %s", temp->pcb->processName);
                printf("\nClass: %s", getClass(temp->pcb->processClass));
                printf("\nState: %s", getState(temp->pcb->state));
                printf("\nSuspended Status: %s", getSuspendedStatus(temp->pcb->suspended));
                printf("\nPriority: %d", temp->pcb->priority);
                printf("\n");
                temp = temp->next;
            }
            printf("--------------------------------------------------------------------\n");
        }
    }
    
}

void ShowBlockedProcesses(){
    if(numParameters > 0){
        printf("Invalid number of parameters. The format for the '%s' command is: %s", CMD_SHOW_BLOCKED_PROCESSES, CMD_SHOW_BLOCKED_PROCESSES);
    }else{
        //Need to figure out how to test for null blockedQueue???
        FNode *temp = blockedQueue->head;
        if(temp == NULL){
            printf("There are no processes in the blocked queue.");
        }else{
            printf("\n-----------------All Processes in the Blocked Queue-----------------");
            while(temp != NULL){
                printf("\nProcess Name: %s", temp->pcb->processName);
                printf("\nClass: %s", getClass(temp->pcb->processClass));
                printf("\nState: %s", getState(temp->pcb->state));
                printf("\nSuspended Status: %s", getSuspendedStatus(temp->pcb->suspended));
                printf("\nPriority: %d", temp->pcb->priority);
                printf("\n");
                temp = temp->next;
            }
            printf("--------------------------------------------------------------------\n");
        }
    }
    
}