#include "HeaderFiles/comhan.h"
#include "HeaderFiles/customprocess.h"

//Total Number of days in each month
int numDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

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
            createPCB(parameters[0], atoi(parameters[1]), atoi(parameters[2]));
        }else if(strcmp(userInput, CMD_DELETE_PCB) == 0 || strcmp(userInput, INPUT_DELETE_PCB) == 0){
            deletePCB(parameters[0]);
        }else if(strcmp(userInput, CMD_BLOCK) == 0 || strcmp(userInput, INPUT_BLOCK) == 0){
            block(parameters[0]);
        }else if(strcmp(userInput, CMD_UNBLOCK) == 0 || strcmp(userInput, INPUT_UNBLOCK) == 0){
            unblock(parameters[0]);
        }else{
            printf("Unrecognized command. Please try again.");
        }

        //Free the str variable
        free(str);
    }

    //Free the userInput variable
    free(userInput);
}

//Converts the string to all lowercase characters
void convertToLowercase(char *input){
    //Iterates through the string
    for(int i = 0; i < strlen(input); i++){
        input[i] = tolower(input[i]);
    }
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
        } else if (strcmp(cmdName, "") == 0) { // Print the overview help
            printFile("overview.txt");
        } else { // Print an error for unknown command
            printf("Command not found: %s", cmdName);
        }
    }
}

// Print a file character by character 
void printFile(char *fileName) {
    // Create the path to the file
    char path[80] = "./helpFiles/";
    // Add the file name to the path
    strcat(path, fileName);
    // Holds the character of the file as an integer value
    int c;
    // Pointer to hold the file
    FILE *file;
    // Open the file
    file = fopen(path, "r");
    // If the file exists, print the contents
    if (file) {
        // Loop to get all the charcaters of the file
        while ((c = fgetc(file)) != EOF)
            // Print the charcater to the console
            printf("%c", c);
        // Close the file
        fclose(file);
    } else { // Else inform the user that no details were found
        printf("Description file %s not found\n");
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

//Gets the month correlating to the integer (i.e. 0 = January, 11 = December) and returns it
char *getMonth(int month){
    switch(month){
        case 0: return "January"; break;
        case 1: return "February"; break;
        case 2: return "March"; break;
        case 3: return "April"; break;
        case 4: return "May"; break;
        case 5: return "June"; break;
        case 6: return "July"; break;
        case 7: return "August"; break;
        case 8: return "September"; break;
        case 9: return "October"; break;
        case 10: return "November"; break;
        case 11: return "December"; break;
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

//Checks the user input for changing the date to ensure it is a valid day
int checkMonth(int month, int day, int year){
    //If it is a leap year, then there are 29 days in February
    if(((year % 4) == 0 && (year % 100) != 0) || year % 400 == 0){
        numDays[1] = 29;
    }else{
        numDays[1] = 28;
    }

    //If the specified day is greater than the number of days in the month, return false
    //If the day is less than zero, return false
    //If the month is not greater than 0 and less than 11 (tm_mon ranges from 0 to 11), return false
    if(day > numDays[month] || day <= 0 || !(month >= 0 && month <= 11) || year < 0){
        return 0;
    }

    //Otherwise, return true
    return 1;
}

//Calculates the date difference between the system time and the chosen time
void calculateDateDifference(int month, int day, int year){
    //Refreshes the time variable
    currentTime = time(NULL);
    tm = *localtime(&currentTime);

    //Stores the differences
    dateDiff.numYears = year - (tm.tm_year + 1900);
    dateDiff.numMonths = month - tm.tm_mon;
    dateDiff.numDays = day - tm.tm_mday;
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

void createPCB(char *name, int class, int priority)
{
    if(numParameters != 3){
        printf("Invalid number of parameters. The format for the '%s' command is: %s {{processName}} {{processClass}} {{priority}}", CMD_CREATE_PCB, CMD_CREATE_PCB);
    }else{
        if (strlen(name) > 8){
            printf("Error: Process name must be less than 8 characters!");
        }else if(priority < 0 || priority > 9){
            printf("Error: Priority must be between 0 and 9");
        }else if(FindPCB(name) != NULL){ //name must be unique
            printf("Error: Process name must be Unique!");
        }else if((class != 1) && (class != 2)){ //must be of appropriate class
            printf("Error: Process class must be 1 (System Process) or 2 (Application Process)!");
        }else{ //if conditions met create the PCB
            SetUpPCB(name, class, priority);
        }
    }
}

// Delete the PCB from the appropriate queue
void deletePCB(char *processName) {
    // Find the PCB then remove it
    PCB *p = FindPCB(processName);
    // If the process is present in one of the queues, remove it
    if (p != NULL) {
        printf("\n%s\n", RemovePCB(p));
    }else{
        printf("ERROR: Process %s does not exist\n", processName);
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
            RemovePCB(p);
            // Blocked state is represented by integer 0
            p->state = 0;
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
            RemovePCB(p);
            //Set the state to 1 (1 = ready)
            p->state = 1;
            //Insert into queue
            InsertPCB(p);
        }
    }
}