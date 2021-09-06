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

time_t currentTime;
struct tm tm;

void COMHAN();
void Help();
void Version();
void DisplayDate();
void ChangeDate();
void DisplayTime();
void TerminateTechOS();

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
            Help();
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
    printf("Help");
}

void Version(){
    printf("Version");
}

void DisplayDate(){
    printf("Display Date");
}

void ChangeDate(){
    printf("Change Date");
}

void DisplayTime(){
    printf("%d : %d \n" , tm.tm_hour, tm.tm_min);
}

void TerminateTechOS(){
    printf("Goodbye!");
    exit(0);
}