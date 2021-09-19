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
#include <ctype.h>
#include "HeaderFiles/comhan.h"

//Main method that calls COMHAN function
int main(){
    //Initialize the date difference elements
    dateDiff.numDays = 0;
    dateDiff.numMonths = 0;
    dateDiff.numYears = 0;
    //Initialize the time
    currentTime = time(NULL);
    tm = *localtime(&currentTime);

    //Call the COMHAN function to execute the program
    COMHAN();

    return 0;
}
