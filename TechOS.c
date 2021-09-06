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

//Displays the current date for the user
void DisplayDate(){
    printf("%s %d, %d", getMonth(tm.tm_mon), tm.tm_mday, tm.tm_year + 1900);
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
    //Get the first portion
    str = strtok(str, delim);

    //Declare the variables
    char *month, *day, *year;
    //Declare an array of char pointers (strings)
    char *vars[3];
    //Iterate over the string
    int i = 0;
    while(str != NULL && i < 3){
        vars[i] = str;
        str = strtok(NULL, delim);
        i++;
    }
    //Free the str pointer
    free(str);

    //Assign the month, day and year from the array
    month = vars[0];
    day = vars[1];
    year = vars[2];

    //Assign the tm values to the parameters and any adjustments necessary
    //Free them after they are assigned
    tm.tm_mon = atoi(month) - 1;
    free(month);
    tm.tm_mday = atoi(day);
    free(day);
    tm.tm_year = atoi(year) - 1900;
    free(year);
}

void DisplayTime(){
    printf("Display Time");
}

void TerminateTechOS(){
    printf("Terminate Tech OS");
}