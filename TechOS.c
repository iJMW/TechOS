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