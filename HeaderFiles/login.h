#include <stdio.h>

#ifndef LOGIN_H_
#define LOGIN_H_

typedef struct User{
    char username[100];
    char password[100];
    int access;
}User;

User *LOGIN();
void readAccounts(FILE *file);
User *validateLogin(char *userName, char *password);

#endif