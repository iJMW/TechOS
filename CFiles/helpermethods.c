#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include "../HeaderFiles/helpermethods.h"

//Total Number of days in each month
int numDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//Converts the string to all lowercase characters
void convertToLowercase(char *input){
    //Iterates through the string
    for(int i = 0; i < strlen(input); i++){
        input[i] = tolower(input[i]);
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

int isNumber(char *s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (isdigit(s[i]) == 0)
              return 0;
    }
    return 1;
}

// Takes in an integer that represents the state and returns the appropriate string
char *getState(int s) {
    if (s == 0) {
        return "Blocked";
    } else if (s == 1) {
        return "Ready";
    } else if (s == 2) {
        return "Running";
    }
}

// Takes in an integer that represents the suspended staus and returns the appropriate string
char *getSuspendedStatus(int s) {
    if (s == 0) {
        return "Not Suspended";
    } else {
        return "Suspended";
    } 
}

char *getClass(int val){
    if(val == 1){
        return "System Process";
    }else{
        return "Application Process";
    }
}
//helper method to concat array of strings togeether
char *concatStrings(char *a[], int numParameters)
{
    char *s = (char *)malloc(100 * sizeof(char));
    if(a[0][0] == '/'){
        strcpy(s, ".");
        strcat(s, a[0]);
    }else{
        strcpy(s, a[0]);
    }
    
    for (int i = 1; i < numParameters; i++){
        strcat(s, " ");
        strcat(s, a[i]);
    }
    return s;
}

//helper method to get substring in string
char *getSubstring(char *s, int start, int end) 
{
    int i;
    char *newStr = (char *)malloc(100 * sizeof(char));
    for (i = 0; (i+start) < end; i++) {
        newStr[i] = s[i+start];
    }

    newStr[i] = '\0';
    return newStr;
}

void setPassword(User *selectedUser){
    char *currpass = selectedUser -> password;//current password
    char *newpass;
    char *confirmpass;
    printf("\nEnter new password: ");
    scanf("%s",&newpass);//get new password

    while(!strcmp(newpass,currpass) || strstr(newpass, " ") != NULL)//while passwords are identical
    {
        if (!strcmp(newpass,currpass)) {
            printf("\nNew password cannot the same as the old password");
        } else if (strstr(newpass, " ") != NULL) {
             printf("\nPassword cannot contain spaces.");
        }
        printf("\nEnter new password: ");
        scanf("%s",&newpass);//get new password
    }

    printf("\nConfirm new password: ");
    scanf("%s",&confirmpass);//get new password
    
    if(strcmp(newpass,confirmpass)){
        //selectedUser -> password = newpass;
        strcpy(selectedUser->password, newpass);
        printf("\nPassword changed.");
    }
    else{
        printf("\nPassword not changed.");
    }
}

// Will updated users.txt
void updateUserFile(){
    // Open the user file
    FILE *file = fopen("users.txt", "w");

    // Start at the head of the queue
    LNode *temp = userQueue->head;
    // Iterate over each user
    while(temp != NULL) {
        fprintf(file, "%s %s %d\n", temp->user->username, temp->user->password, temp->user->access);
        //fprintf(file, "%s", strcat(temp->user->password, " "));
        //fprintf(file, "%d\n", temp->user->access);
        temp = temp->next;
    }

    // Close the user file
    fclose(file);
}