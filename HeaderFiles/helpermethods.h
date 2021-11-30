#include "../HeaderFiles/login.h"
#include "../HeaderFiles/linkedlist.h"

#ifndef HELPERMETHODS_H_
#define HELPERMETHODS_H_

//Used to calculate the date difference if the user decides to change the date
typedef struct DateDifference{
    int numMonths;
    int numDays;
    int numYears;
}DateDifference;

extern int numDays[];
extern time_t currentTime;
extern struct tm tm;
extern DateDifference dateDiff;

void convertToLowercase(char *input);
void printFile(char *fileName);
char *getMonth(int month);
int checkMonth(int month, int day, int year);
void calculateDateDifference(int month, int day, int year);
int isNumber(char *s);
char *getState(int s);
char *getSuspendedStatus(int s);
char *getClass(int val);
char *concatStrings(char *a[],int numParameters);
char *getSubstring(char *s, int start, int end);
void setPassword(User *selectedUser);
void updateUserFile();

#endif