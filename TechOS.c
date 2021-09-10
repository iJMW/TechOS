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
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

#define VERSION_NUMBER "1.0"

time_t currentTime;
struct tm tm;

void COMHAN();
void Help();
void Version();
void DisplayDate();
void ChangeDate();
void DisplayTime();
void TerminateTechOS();

void printFile(char *fileName);

int main(){

    currentTime = time(NULL);
    tm = *localtime(&currentTime);

    COMHAN();

    COMHAN();

    return 0;
}

void COMHAN(){
    char userInput[50];
    while(strcmp(userInput, "Quit") != 0){
        printf("\nTechOS > ");
        scanf("%s", userInput);
        if(strcmp(userInput, "help") == 0){
            Help(userInput);
        }else if(strcmp(userInput, "version") == 0){
            Version();
        }else if(strcmp(userInput, "dispdate") == 0){
            DisplayDate();
        }else if(strcmp(userInput, "chdate") == 0){
            ChangeDate();
        }else if(strcmp(userInput, "time") == 0){
            DisplayTime();
        }else if(strcmp(userInput, "quit") == 0){
            TerminateTechOS();
        }else{
            printf("\nUnrecognized command. Please try again.");
        }
    }
}

void Help(){
    // Define the size of the string
    size_t size = 50;
    // Allocate memory for the string
    char *str = (char *)malloc(size * sizeof(char));
    // Get the line
    getline(&str, &size, stdin);
    // Determine which command the user wants to view and 
    if (strcmp(str, " help\n") == 0) { // Print the help file for the help command
        printFile("help.txt");
    } else if (strcmp(str, " version\n") == 0) { // Print the help file for the version command
        printFile("version.txt");
    } else if (strcmp(str, " date\n") == 0) { // Print the help file for the dispdate command
        printFile("date.txt");
    } else if (strcmp(str, " chdate\n") == 0) { // Print the help file for the chdate command
        printFile("chdate.txt");
    } else if (strcmp(str, " disptime\n") == 0) { // Print the help file for the disptime command
        printFile("disptime.txt");
    } else if (strcmp(str, " quit\n") == 0) { // Print the help file for the quit command
        printFile("quit.txt");
    } else if (strcmp(str, "\n") == 0) { // Print the overview help
        printFile("overview.txt");
    } else { // Print an error for unknown command
        printf("Command not found:%s", str);
    }
}

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

void Version(){
    printf("Version Number: %s\n", VERSION_NUMBER);
    printf("Authors: Logan Bland, John Clay, Jalen Wayt\n");
    printf("Completion Date: 09/14/2021");
}

void DisplayDate(){
    printf("Display Date");
}

void ChangeDate(){
    printf("Change Date");
}

void DisplayTime(){

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