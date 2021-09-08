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
int checkMonth(int month, int day, int year);
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
    //Assign the tm values to the parameters and any adjustments necessary
    //Free them after they are assigned
        tm.tm_mon = month - 1;
        tm.tm_mday = day;
        tm.tm_year = year - 1900;

        //Print the date for the user to verify that it was changed properly
        printf("Changed date to: ");
        DisplayDate();
    }else{//otherwise, display an error message
        printf("Invalid date selection. Please try again.");
    }
    
    //Free the date pointer
    free(date);
}

//Checks the user input for changing the date to ensure it is a valid day
int checkMonth(int month, int day, int year){
    //Total Number of days in each month
    int numDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    //If it is a leap year, then there are 29 days in February
    if((year % 4) == 0){
        numDays[1] = 29;
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

void DisplayTime(){
    printf("Display Time");
}

void TerminateTechOS(){
    printf("Terminate Tech OS");
}