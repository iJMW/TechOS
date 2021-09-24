#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include "priorityqueue.h"

#ifndef COMHAN_H_
# define COMHAN_H_

// Version information for the TechOS
#define VERSION_NUMBER "1.0"
#define AUTHORS "Logan Bland, John Clay, Jalen Wayt"
#define COMPLETION_DATE "09/14/2021"

// Command names within the TechOs
#define CMD_CDDATE "chdate"
#define CMD_DATE "date"
#define CMD_HELP "help"
#define CMD_QUIT "quit"
#define CMD_TIME "time"
#define CMD_VERSION "version"
#define CMD_CREATE_PCB "crprocess"
#define CMD_DELETE_PCB "delprocess"
#define CMD_BLOCK "block"
#define CMD_UNBLOCK "unblock"
//Input Names including the next line character
#define INPUT_CDDATE "chdate\n"
#define INPUT_DATE "date\n"
#define INPUT_HELP "help\n"
#define INPUT_QUIT "quit\n"
#define INPUT_TIME "time\n"
#define INPUT_VERSION "version\n"
#define INPUT_CREATE_PCB "crprocess\n"
#define INPUT_DELETE_PCB "delprocess\n"
#define INPUT_BLOCK "block\n"
#define INPUT_UNBLOCK "unblock\n"

//Used to calculate the date difference if the user decides to change the date
typedef struct DateDifference{
    int numMonths;
    int numDays;
    int numYears;
}DateDifference;

//Function Prototypes
void COMHAN();
void Help(char* cmdName);
void Version();
void DisplayDate();
char *getMonth(int month);
void ChangeDate(char *parameters);
int checkMonth(int month, int day, int year);
void calculateDateDifference();
void DisplayTime();
void TerminateTechOS();
void printFile(char *fileName);
void convertToLowercase(char *input);
void createPCB(char name[], int class, int priority);
void deletePCB(char *processName);
void block(char *processName);
void unblock(char *processName);

#endif