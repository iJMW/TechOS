#include "../HeaderFiles/comhan.h"
#include "../HeaderFiles/customprocess.h"
#include "../HeaderFiles/helpermethods.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

//Total Number of days in each month
//int numDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//Global Variables for keeping track of parameters and if the user chose to quit
int numParameters;
int numTags;
int didUserQuit = 0;
int didUserLogout = 0;
char *location;
//DIR *currentDirectory = opendir("..");

//Used for keeping track of the time and date of the system
time_t currentTime;
struct tm tm;

//Global Variable for the struct DateDifference
DateDifference dateDiff;

//Function controls flow of program
void COMHAN(User *currentUser){
    //Initialize the date difference elements
    dateDiff.numDays = 0;
    dateDiff.numMonths = 0;
    dateDiff.numYears = 0;
    //Initialize the time
    currentTime = time(NULL);
    tm = *localtime(&currentTime);
    // Intialize the location
    location = ".";

    didUserLogout = 0;

    //Size of input
    size_t size = 50;
    //UserInput will store the specific command
    char *userInput = (char *)malloc(size * sizeof(char));
    //Stores the parameters
    char *parameters[size];
    char *tags[size];

    //While the user chooses not to quit, display the CLI
    while(didUserQuit == 0 && didUserLogout == 0){
        printf("\nTechOS > ");
        //Allocate memory for the string
        char *str = (char *)malloc(size * sizeof(char));
        //Declare the delimiters, a whitespace and \n is the delimeter
        char delim[] = " \n";
        //Get the line
        getline(&str, &size, stdin);
        char *stringToAdd = (char *)malloc(size * sizeof(char));
        //Iterate over the string
        numParameters = 0;
        numTags = 0;
        //flag to track if tag is found
        int noDashFlag = 0;
        //Get the first portion
        str = strtok(str, delim);
        while(str != NULL){
            if(numParameters == 0){ // Store the command the user wants to run
                userInput = str;
                convertToLowercase(userInput);
                strcpy(stringToAdd, userInput);
                numParameters++;
            } else{  // Store the parameters
                if (str[0] != '-') {
                    noDashFlag = 1;
                }
                // There is no dash, therefore it is a parameter
                if (noDashFlag == 1) {
                    parameters[numParameters - 1] = str;
                    convertToLowercase(parameters[numParameters-1]);
                    // Increase the number of parameters
                    numParameters++;
                } else { // There is a dash, then it is a tag
                    tags[numTags] = str;
                    convertToLowercase(tags[numTags]);
                    numTags++;
                }
                //This is only for the history command
                strcat(stringToAdd, " ");
                strcat(stringToAdd, str);
            }
            // Tokenize the same line by passing NULL
            str = strtok(NULL, delim);
        }

        // If no parameters were passed, set the parameters to be ""
        if(numParameters == 1){
            parameters[0] = "";
            parameters[1] = "";
        }
        // If no tags were passed, set the tags to ""
        if(numTags == 0) {
            tags[0] = "";
        }

        // Reduce numParameters by one to not include the command being ran
        // e.g. dont include 'help' in the parameter cound when user entered
        // 'help version'
        numParameters = numParameters - 1;

        //Convert it to lowercase
        convertToLowercase(stringToAdd);
        //If it is not the history command, add it to the queue
        //Do we want to get rid of this?
        if(strcmp(stringToAdd, "hist") != 0){
            Henqueue(history, stringToAdd);
        }
        
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
        }else if(strcmp(userInput, CMD_SETPRIORITY) == 0 || strcmp(userInput, INPUT_SETPRIORITY) == 0){
            setPriority(parameters[0], parameters[1]);
        }else if(strcmp(userInput, CMD_SUSPEND) == 0 || strcmp(userInput, INPUT_SUSPEND) == 0){
            suspend(parameters[0]);
        }else if(strcmp(userInput, CMD_RESUME) == 0 || strcmp(userInput, INPUT_RESUME) == 0){
            resume(parameters[0]);
        }else if(strcmp(userInput, CMD_SHPCB) == 0 || strcmp(userInput, INPUT_SHPCB) == 0){
            showPCB(parameters[0]);
        }else if(strcmp(userInput, CMD_SHALLPCB) == 0 || strcmp(userInput, INPUT_SHALLPCB) == 0){
            showAllPCB();
        }else if(strcmp(userInput, CMD_SHOW_READY_PROCESSES) == 0 || strcmp(userInput, INPUT_SHOW_READY_PROCESSES) == 0){
            ShowReadyProcesses();
        }else if(strcmp(userInput, CMD_SHOW_BLOCKED_PROCESSES) == 0 || strcmp(userInput, INPUT_SHOW_BLOCKED_PROCESSES) == 0){
            ShowBlockedProcesses();
        }else if(strcmp(userInput, CMD_HIST) == 0 || strcmp(userInput, INPUT_HIST) == 0){
            showHistory();
        }else if (strcmp(userInput, CMD_LOADPCB) == 0 || strcmp(userInput, INPUT_LOADPCB) == 0) {
            loadProcess(parameters[0], parameters[1], parameters[2], parameters[3]);
        }else if (strcmp(userInput, CMD_DISPATCH) == 0 || strcmp(userInput, INPUT_DISPATCH) == 0){
            dispatch();
        }else if (strcmp(userInput, CMD_VIEW_DIRECTORY) == 0 || strcmp(userInput, INPUT_VIEW_DIRECTORY) == 0) {
            viewDirectory(tags, parameters);
        }else if (strcmp(userInput, CMD_CHANGE_DIRECTORY) == 0 || strcmp(userInput, INPUT_CHANGE_DIRECTORY) == 0) {
            changeDirectory(parameters);
        }else if (strcmp(userInput, CMD_CREATE_FOLDER) == 0 || strcmp(userInput, INPUT_CREATE_FOLDER) == 0) {
            createFolder(parameters);
        }else if (strcmp(userInput, CMD_REMOVE_FOLDER) == 0 || strcmp(userInput, INPUT_REMOVE_FOLDER) == 0) {
            removeFolder(parameters);
        }else if (strcmp(userInput, CMD_CREATE_FILE) == 0 || strcmp(userInput, INPUT_CREATE_FILE) == 0) {
            createFile(parameters);
        }else if (strcmp(userInput, CMD_REMOVE_FILE) == 0 || strcmp(userInput, INPUT_REMOVE_FILE) == 0) {
            removeFile(parameters);
        }else if (strcmp(userInput, "logout") == 0 || strcmp(userInput, "logout\n") == 0) {
            didUserLogout = 1;
        } else{
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
        } else if (strcmp(cmdName, CMD_SETPRIORITY) == 0) { // Print the set priority help
            printFile("setpr.txt");
        } else if (strcmp(cmdName, CMD_SUSPEND) == 0) { // Print the suspend help
            printFile("suspend.txt");
        } else if (strcmp(cmdName, CMD_RESUME) == 0) { // Print the resume help
            printFile("resume.txt");
        } else if (strcmp(cmdName, CMD_HIST) == 0) { // Print the hist help
            printFile("hist.txt");
        } else if (strcmp(cmdName, CMD_LOADPCB) == 0) { // Print the load pcb help
            printFile("loadpcb.txt");
        } else if (strcmp(cmdName, CMD_DISPATCH) == 0) { // Print the dispatch help
            printFile("dispatch.txt");
        } else if (strcmp(cmdName, CMD_VIEW_DIRECTORY) == 0) { // Print the overview help
            printFile("ls.txt");
        } else if (strcmp(cmdName, CMD_CHANGE_DIRECTORY) == 0) { // Print the overview help
            printFile("cd.txt");
        } else if (strcmp(cmdName, CMD_CREATE_FILE) == 0) { // Print the overview help
            printFile("mkfile.txt");
        } else if (strcmp(cmdName, CMD_REMOVE_FILE) == 0) { // Print the overview help
            printFile("rmfile.txt");
        } else if (strcmp(cmdName, CMD_CREATE_FOLDER) == 0) { // Print the overview help
            printFile("mkdir.txt");
        } else if (strcmp(cmdName, CMD_REMOVE_FOLDER) == 0) { // Print the overview help
            printFile("rmdir.txt");
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

// Set the priority of a processes
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

// Suspend a process
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

// Resume a process
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

// Show all the processes in the ready queue
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

// Show all the blocked processes
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

// Load a process
void loadProcess(char *name, char *class, char *priority, char *filePath)
{
     if(numParameters != 4){
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
        }else if (!fopen(filePath, "r")) { 
            printf("Error: No file with the name %s exists!", filePath);
        } else{ //if conditions met create the PCB
            SetUpPCB(name, atoi(class), atoi(priority), filePath);
            printf("Loaded process %s", name);
        }
    }
}

// Dispatch all the processes
void dispatch()
{
    // Holds the number of processes completed
    int comp = 0;
    // Check if the ready queue is empty
    if (isPEmpty(readyQueue)){
        printf("\nERROR: No processes in ready queue.");
    }else{
        // Stores the value from the system
        int value;
        // Holds the current pcb being executed
        PCB *temp;
        // While both queues are not empty
        while((!isPEmpty(readyQueue) || !isFEmpty(blockedQueue))){
            // If the ready is empty
            if(isPEmpty(readyQueue)){ // block queue is not empty, but ready queue is
                //Get the first process in the blocked queue
                temp = Fdequeue(blockedQueue)->pcb;
                //Unblock the process
                temp->state = 1;
            } else if (isFEmpty(blockedQueue)) { // ready queue is not empty, but block queue is
                //printf("\nReady queue is not empty");
                temp = Pdequeue(readyQueue)->pcb;
            } else { // Both queues are not empty
                temp = Pdequeue(readyQueue)->pcb;
                // Generate a randome number between 0 and 100
                int randNum = (rand() % (101-0+1)) + 0;
                //If random number is less than 50, unblock the first pcb
                if(randNum < 50){
                    // Get the first process from the blocked queue
                    PCB *unblock = Fdequeue(blockedQueue)->pcb;
                    // Change the state of the process to ready
                    unblock->state = 1;
                    //Insert to the ready queue
                    InsertPCB(unblock);
                }
            }
            // Set the process' state to running
            temp->state = 2;
            // Create a char pointer
            char *str = (char *)malloc(50 * sizeof(char));
            // Create string to pass to system
            strcpy(str, "execute");
            strcat(str, " ");
            strcat(str, temp->data);
            strcat(str, " ");
            int length = snprintf(NULL, 0, "%d", temp->offset+1);
            char *offsetStr = (char *)malloc(length * sizeof(char));
            snprintf(offsetStr, length+1, "%d", temp->offset+1);
            strcat(str, offsetStr);
            // Run the process
            value = system(str);
            if(value == 0){
                printf("\nProcess %s has completed", temp->processName);
                // Increase the number of processes completed
                comp++;
                // Remove PCB from queue
                RemovePCB(temp, 1);
            }else{
                printf("\nProcess %s suspended at %d", temp->processName, value);
                // Divide the return
                temp->offset = value % 256;
                // Change status of PCB to suspended
                temp->suspended = 1;
                // Block the PCB
                temp->state = 0;
                // Place the PCB into the block queue
                InsertPCB(temp);
                // Resume the PCB, but stays in blocked queue
                temp->suspended = 0;
            }
        }
    }
}

// Function to display the history
void showHistory(){
    printHistoryQueue(history);
}

// Displays the current directory
void viewDirectory(char *tags[], char *parameters[])
{
    // Check for improper tags
    if((strcmp(tags[0], "-size") == 0 && numTags == 1) || strcmp(tags[0], "") == 0){
        // Build the passed location
        char *passedLocation = concatStrings(parameters, numParameters);
        // Get the current location
        char *directory = "";
        DIR *currentDirectory;
        if (strcmp(passedLocation, "") == 0) {
            currentDirectory = opendir(location);
            directory = location;
        } else {
            currentDirectory = opendir(passedLocation);
            directory = passedLocation;
        }

        struct dirent *dir;

        // If the current directory is valid
        if (currentDirectory) {
            // Read all the items from the current directory
            while ((dir = readdir(currentDirectory)) != NULL) {
                // Print the directory name
                printf("\n%-20s\t", dir->d_name);
                if(strcmp(tags[0], "-size") == 0 && numTags == 1){
                    // Form the file path 
                    char *str = (char *)malloc(100 * sizeof(char));
                    strcpy(str, directory);
                    if(str[strlen(str) - 1] != '/'){
                        strcat(str, "/");
                    }
                    strcat(str, dir->d_name);
                    // Open the file
                    FILE *file = fopen(str, "r");
                    // If the file exists
                    if(file) {
                        fseek(file, 0, SEEK_END);
                        long fileSize = ftell(file);
                        printf("%ld bytes", fileSize);
                        fseek(file, 0, SEEK_SET);
                    }
                }
            }
            closedir(currentDirectory);
        } else {
            printf("\nERROR: Invalid directory");
        }
    }else{
        printf("\nERROR: Invalid tag(s)");
    }
}

// Changes the directory
void changeDirectory(char *parameters[]){
    // Check the number of parameters
    if (numParameters == 0) {
        printf("Invalid number of parameters. The format for the '%s' command is: %s {{directory}}", CMD_CHANGE_DIRECTORY, CMD_CHANGE_DIRECTORY);
    } else {
        // Build the directory name
        int absolute = 0;
        //If the first parameter's first element is a / then it is absolute
        //First parameter before concatenation is the beginning of the path
        //from the user
        if(parameters[0][0] == '/'){
            absolute = 1;
        }
        char *directoryName = concatStrings(parameters, numParameters);
        char *newName = (char *)malloc(100 * sizeof(char));
        strcpy(newName, location);
        strcat(newName, "/");
        strcat(newName, directoryName);

        int errorType = 0;
        //If begins with / or ./, then it is an absolute path
        char *chosenPath = (char *)malloc(100 * sizeof(char));
        
        // Absolute
        if(absolute == 1){
            //strcpy(chosenPath, ".");
            //strcat(chosenPath, directoryName);
            strcpy(chosenPath, directoryName);
        } 
        
        // Backing out of directory
        else if(directoryName[0] == '.' && directoryName[1] == '.'){
            // Can't back out of root directrory
            if(strcmp(location, ".") == 0) {
                errorType = 1;
            }else{
                int c = '/';
                char *ptr = strrchr(location, c);
                // Remove substring
                int indexOfLastSlash = -1;
                // Get the index of the last slash
                for(int i = strlen(location)-1; i > 0; i--){
                    if(location[i] == '/'){
                        indexOfLastSlash = i;
                        break;
                    }
                }
                // Remove the last directory from the path
                chosenPath = getSubstring(location, 0, indexOfLastSlash);
                if (directoryName[2] && directoryName[2]=='/') {
                    char *newDir = getSubstring(directoryName, 2, strlen(directoryName));
                    strcat(chosenPath, newDir);
                }
            }
        } 
        
        // Relative Path
        else if (strcmp(directoryName, ".") != 0) {// Relative path from current location
            // HeaderFiles
            if (directoryName[0] == '.') {
                directoryName = getSubstring(directoryName, 2, strlen(directoryName));
            }
            // Create the chosen path
            strcpy(chosenPath, location);
            strcat(chosenPath, "/");
            strcat(chosenPath, directoryName);
        }
        
        DIR *chosenDirectory = opendir(chosenPath);
        if(errorType == 1){
            printf("\nError: Already in root directory");
        } else if(chosenDirectory){
            location = chosenPath;
            printf("\nNew Location: %s", chosenPath);
        } else { 
            printf("\nERROR: Directory %s does not exist.", chosenPath);
        }
    }
}

// Function to create a folder
void createFolder(char *parameters[]){
    // Check the number of parameters
    if (numParameters == 0) {
        printf("Invalid number of parameters. The format for the '%s' command is: %s {{folderName}}", CMD_CREATE_FOLDER, CMD_CREATE_FOLDER);
    } else {
        // Create the folder name
        char *folderName = concatStrings(parameters, numParameters);
        char *newName = (char *)malloc(100 * sizeof(char));
        strcpy(newName, location);
        strcat(newName, "/");
        strcat(newName, folderName);
        // Make the folder
        if(!mkdir(newName)){
            printf("\nFolder Created");
        }else{
            printf("\nFolder cannot be created");
        }
    }
}

// Function to remove a folder
void removeFolder(char *parameters[]){
    // Check the number of parameters
    if(numParameters == 0){
        printf("Invalid number of parameters. The format for the '%s' command is: %s {{folderName}}", CMD_REMOVE_FOLDER, CMD_REMOVE_FOLDER);
    }else{
        // Build the folder names
        char *folderName = concatStrings(parameters, numParameters);
        char *newName = (char *)malloc(100 * sizeof(char));
        strcpy(newName, location);
        strcat(newName, "/");
        strcat(newName, folderName);
        // Count the files in the directory
        DIR *currentDirectory = opendir(newName);
        struct dirent *dir;
        int count = 0;
        while ((dir = readdir(currentDirectory)) != NULL && count < 3) {
            count++;
        }
        // If the directory is storing files, don't remove it
        if (count >= 3) {
            printf("\nERROR: Folder is not empty");
        } else if(!rmdir(newName)) {
            printf("\nFolder Removed");
        }else{
            printf("\nERROR: Folder does not exist");
        }
    }
}

// Function to create a file in the current directory
void createFile(char *parameters[]){
    // Check the number of parameters
    if (numParameters == 0) {
        printf("Invalid number of parameters. The format for the '%s' command is: %s {{fileName}}", CMD_CREATE_FILE, CMD_CREATE_FILE);
    } else {
        // Create the file name
        char *fileName = concatStrings(parameters, numParameters);
        char *newName = (char *)malloc(100 * sizeof(char));
        strcpy(newName, location);
        strcat(newName, "/");
        strcat(newName, fileName);
        // Create the file
        FILE *file = fopen(newName, "r");
        // If the file can be created
        if(!file){
            file = fopen(newName, "w");
            printf("\nFile created");
        }else{
            printf("\nFile cannot be created");
        }
        // Close the file
        fclose(file);
    }
}

void removeFile(char *parameters[]){
    // Check the number of parameters
    if(numParameters == 0){
        printf("Invalid number of parameters. The format for the '%s' command is: %s {{folderName}}", CMD_REMOVE_FILE, CMD_REMOVE_FILE);
    }else{
        // Create the file name
        char *fileName = concatStrings(parameters, numParameters);
        char *newName = (char *)malloc(100 * sizeof(char));
        strcpy(newName, location);
        strcat(newName, "/");
        strcat(newName, fileName);
        // Open the file
        FILE *file = fopen(newName, "r");
        char answer;
        // If the file exists
        if (file){
            fclose(file);
            // Loop until the user confirms to delete the file or not
            while(answer != 'y' && answer != 'n'){
                printf("\nAre you sure you want to delete the file %s? (y/n) ", fileName);
                scanf(" %c", &answer);
                while(getchar() != '\n');
                // If the user selects to remove the file
                if (answer == 'y'){
                    // Print whether the file has been removed or not
                    if(!remove(newName)){
                        printf("\nFile \"%s\" removed.", fileName);
                    }else{
                        printf("\nFile \"%s\" cannot be removed.", fileName);
                    }
                }
            }
        }else{ // Print if the file does not exist
            printf("\nFile \"%s\" does not exist.", fileName);
        }
    }  
}

