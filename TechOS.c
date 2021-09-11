/*
   Names: Logan Bland
          John Clay
          Jalen Wayt
   Assignment: Module 1 - User Interface
   Purpose: Design a user interface for the first part of the OS
   Due Date: September 14, 2021
*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// Version number of the TechOS
#define VERSION_NUMBER "1.0"
#define AUTHORS "Logan Bland, John Clay, Jalen Wayt"
#define COMPLETION_DATE "09/14/2021"

// Command names within the TechOs
#define CMD_CDDATE "chdate"
#define CMD_DATE "date"
#define CMD_HELP "help"
#define CMD_QUIT "quit"
#define CMD_TIME "time"
#define CMD_VERSION "version"

#define INPUT_CDDATE " chdate\n"
#define INPUT_DATE " date\n"
#define INPUT_HELP " help\n"
#define INPUT_QUIT " quit\n"
#define INPUT_TIME " time\n"
#define INPUT_VERSION " version\n"

time_t currentTime;
struct tm tm;

typedef struct DateDifference{
    int numMonths;
    int numDays;
    int numYears;
}DateDifference;
DateDifference dateDiff;

//Total Number of days in each month
int numDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

time_t currentTime;
struct tm tm;

void COMHAN();
void Help();
void Version();
void DisplayDate();
char *getMonth(int month);
void ChangeDate();
int checkMonth(int month, int day, int year);
void calculateDateDifference();
void DisplayTime();
void TerminateTechOS();

void printFile(char *fileName);

int main(){
    dateDiff.numDays = 0;
    dateDiff.numMonths = 0;
    dateDiff.numYears = 0;
    currentTime = time(NULL);
    tm = *localtime(&currentTime);

    COMHAN();

    return 0;
}

void COMHAN(){
    char userInput[50];
    while(strcmp(userInput, CMD_QUIT) != 0){
        printf("\nTechOS > ");
        scanf("%s", userInput);
        if(strcmp(userInput, CMD_HELP) == 0){
            Help(userInput);
        }else if(strcmp(userInput, CMD_VERSION) == 0){
            Version();
        }else if(strcmp(userInput, CMD_DATE) == 0){
            DisplayDate();
        }else if(strcmp(userInput, CMD_CDDATE) == 0){
            ChangeDate();
        }else if(strcmp(userInput, CMD_TIME) == 0){
            DisplayTime();
        }else if(strcmp(userInput, CMD_QUIT) == 0){
            TerminateTechOS();
        }else{
            printf("\nUnrecognized command. Please try again.");
        }
    }
}

// Displays a help description to the user based on the command passed
void Help(){
    // Define the size of the string
    size_t size = 50;
    // Allocate memory for the string
    char *str = (char *)malloc(size * sizeof(char));
    // Get the line
    getline(&str, &size, stdin);
    // Determine which command the user wants to view and 
    if (strcmp(str, INPUT_HELP) == 0) { // Print the help file for the help command
        printFile("help.txt");
    } else if (strcmp(str, INPUT_VERSION) == 0) { // Print the help file for the version command
        printFile("version.txt");
    } else if (strcmp(str, INPUT_DATE) == 0) { // Print the help file for the date command
        printFile("date.txt");
    } else if (strcmp(str, INPUT_CDDATE) == 0) { // Print the help file for the chdate command
        printFile("chdate.txt");
    } else if (strcmp(str, INPUT_TIME) == 0) { // Print the help file for the time command
        printFile("time.txt");
    } else if (strcmp(str, INPUT_QUIT) == 0) { // Print the help file for the quit command
        printFile("quit.txt");
    } else if (strcmp(str, "\n") == 0) { // Print the overview help
        printFile("overview.txt");
    } else { // Print an error for unknown command
        printf("Command not found:%s", str);
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
    printf("Version Number: %s\n", VERSION_NUMBER);
    printf("Authors: %s\n", AUTHORS);
    printf("Completion Date: %s", COMPLETION_DATE);
}

//Displays the current date for the user
void DisplayDate(){
    //Refreshes the time variable
    currentTime = time(NULL);
    tm = *localtime(&currentTime);

    //Outputs the date
    printf("%s %d, %d", getMonth(tm.tm_mon + dateDiff.numMonths), tm.tm_mday + dateDiff.numDays, tm.tm_year + 1900 + dateDiff.numYears);
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
void ChangeDate(){
    //Define the size of the string
    size_t size = 20;
    //Allocate memory for the string
    char *str = (char *)malloc(size * sizeof(char));
    //Declare the delimiters, hyphens are the delimiters but it will also skip over the space at the beginning
    char delim[] = " -";
    //Get the line
    getline(&str, &size, stdin);

    //Declare an array of char pointers (strings)
    int *date = (int *)malloc(size * sizeof(int));
    int month, day, year;

    //Iterate over the string
    int i = 0;
    //Get the first portion
    str = strtok(str, delim);
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
        DisplayDate();
    }else{//Otherwise, display an error message
        printf("Invalid date selection. Please try again.");
    }
    
    //Free the date pointer
    free(date);
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
    if(day > numDays[month] || day <= 0 || !(month >= 0 && month <= 11)){
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

    //Will this ever happen?
    /*
    if(dateDiff.numMonths > 12){
        dateDiff.numYears = dateDiff.numYears + (dateDiff.numMonths / 12);
        dateDiff.numMonths = dateDiff.numMonths % 12;
        printf("Changing Months");
    }

    //Will this ever happen?
    if(dateDiff.numDays > 30){
        printf("Changing Days");
        dateDiff.numMonths = dateDiff.numMonths + (dateDiff.numDays / 30);
        dateDiff.numDays = dateDiff.numDays % 30;
    }*/
}

void DisplayTime(){
    //Refreshes the time variable
    currentTime = time(NULL);
    tm = *localtime(&currentTime);

    if(tm.tm_hour < 13){
    printf("%d : %d  \n" , tm.tm_hour, tm.tm_min);
    }

    else{
    printf("%d : %d \n" , tm.tm_hour - 12, tm.tm_min);
    }
}

void TerminateTechOS(){

    int one = 1;
    char in;
    printf("Are you sure you would like to exit? y/n \n");
    
    while(one = 1){
    scanf(" %c" , &in);
    if(in == 'y'){
    printf("Goodbye!");
    exit(0);
    }

    else if (in == 'n')
    {
       COMHAN();
    }
    

    else{
        printf("Invalid command, please try again: ");
    }

    }
    
scanf(" %c" , &in);
    
  


    
}