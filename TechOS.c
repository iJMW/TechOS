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
char *getMonth(int month);
void ChangeDate();
void DisplayTime();
void TerminateTechOS();

int main(){
    currentTime = time(NULL);
    tm = *localtime(&currentTime);

    COMHAN();

    return 0;
}

void COMHAN(){
    char userInput[50];
    while(strcmp(userInput, "quit") != 0){
        printf("\nTechOS > ");
        scanf("%s", userInput);
        if(strcmp(userInput, "help") == 0){
            Help();
        }else if(strcmp(userInput, "version") == 0){
            Version();
        }else if(strcmp(userInput, "date") == 0){
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
    printf("%s %d, %d", getMonth(tm.tm_mon), tm.tm_mday, tm.tm_year + 1900);
}

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

void ChangeDate(){
    size_t size = 20;
    char *str = (char *)malloc(size * sizeof(char));
    char delim[] = " -";
    getline(&str, &size, stdin);
    str = strtok(str, delim);

    char *month, *day, *year;
    char *vars[3];
    int i = 0;
    while(str != NULL && i < 3){
        vars[i] = str;
        str = strtok(NULL, delim);
        i++;
    }

    month = vars[0];
    day = vars[1];
    year = vars[2];

    tm.tm_mon = atoi(month) - 1;
    tm.tm_mday = atoi(day);
    tm.tm_year = atoi(year) - 1900;
}

void DisplayTime(){
    printf("Display Time");
}

void TerminateTechOS(){
    printf("Terminate Tech OS");
}