#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../HeaderFiles/login.h"
#include "../HeaderFiles/linkedlist.h"

User *LOGIN()
{
    // Open the file with all username, password, and access levels
    FILE *file = fopen("users.txt", "r");

    // Read the accounts
    readAccounts(file);
    printf("\nRead all the accounts");

    // Stores the username
    char userName[100];
    // Stores the password
    char password[100];
    // Prompt the user for the username
    printf("\nEnter Username: ");
    scanf(" %s", userName);
    // Prompt the user for the password
    printf("\nEnter Password: ");
    scanf(" %s", password);

    while(getchar() != '\n');

    // Check if the username and password match one of the stored username and passwords
    User *valid = validateLogin(userName, password);

    // Close the file
    fclose(file);

    // If the username and password is valid, return the valid user
    if (valid != NULL)
    {
        return valid;
    }

    // If the username and password is not valid, return null
    return NULL;

}

User *validateLogin(char *userName, char *password){
    // Search for the username and password pair in the linkedlist
    User *returnedUser = Lcontains(userQueue, userName, password);
    // Return null if no matching username and password found
    // Return the user if matching username and password found
    return returnedUser;
}

// Used to read the accounts
void readAccounts(FILE *file)
{
    userQueue = (LQueue *)malloc(sizeof(LQueue));
    initializeLQueue(userQueue);
    User *newUser;
    size_t size = 100;
    // Declare the delimiters, a whitespace and \n is the delimeter
    char delim[] = " \n";
    // Initialize the line
    char * line = (char *)malloc(size * sizeof(char));
    // Iterate over each line in the file
    while (getline(&line, &size, file) != -1)
    {
        //printf("\nLine: %s", line);
        // Declare the new user
        newUser = (User *)malloc(sizeof(User));
        // Tokenize the string to get the username intilially
        line = strtok(line, delim);
        // Determine if the username, password, or access level needs to be stored
        int val = 0;
        // Loop through the line to get the username, password, and access level of the user
        while(line != NULL) {
            //printf("\nSubline: %s", line);
            if(val == 0){
                //Set username
                strcpy(newUser->username, line);
            }else if(val == 1){
                //Set password
                strcpy(newUser->password, line);
            }else if(val == 2){
                //Set access
                newUser->access = atoi(line);
            }
            // Increase the value
            val = val + 1;
            // Update 
            line = strtok(NULL, delim);
        }
        // Add the user
        Lenqueue(userQueue, newUser);
    }
}