#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h> 
#include <sys/stat.h>
#include "priorityqueue.h"
#include "fifoqueue.h"
#include "history.h"

#ifndef COMHAN_H_
# define COMHAN_H_

// Version information for the TechOS
#define VERSION_NUMBER "3.0"
#define AUTHORS "Logan Bland, John Clay, Jalen Wayt"
#define COMPLETION_DATE "10/18/2021"

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
#define CMD_SETPRIORITY "setpr"
#define CMD_SUSPEND "suspend"
#define CMD_RESUME "resume"
#define CMD_UNBLOCK "unblock"
#define CMD_SHPCB "shpcb"
#define CMD_SHALLPCB "shallpcb"
#define CMD_SHOW_READY_PROCESSES "shready"
#define CMD_SHOW_BLOCKED_PROCESSES "shblocked"
#define CMD_DISPATCH "dispatch"
#define CMD_LOADPCB "loadpcb"
#define CMD_HIST "hist"
#define CMD_CHANGE_DIRECTORY "cd"
#define CMD_VIEW_DIRECTORY "ls"
#define CMD_CREATE_FOLDER "mkdir"
#define CMD_REMOVE_FOLDER "rmdir"
#define CMD_CREATE_FILE "mkfile"
#define CMD_REMOVE_FILE "rmfile"
//Input Names including the next line character
#define INPUT_CDDATE "chdate\n"
#define INPUT_DATE "date\n"
#define INPUT_HELP "help\n"
#define INPUT_QUIT "quit\n"
#define INPUT_TIME "time\n"
#define INPUT_VERSION "version\n"
#define INPUT_CREATE_PCB "crprocess\n"
#define INPUT_DELETE_PCB "delprocess\n"
#define INPUT_SETPRIORITY "setpr\n"
#define INPUT_SUSPEND "suspend\n"
#define INPUT_RESUME "resume\n"
#define INPUT_BLOCK "block\n"
#define INPUT_UNBLOCK "unblock\n"
#define INPUT_SHPCB "shpcb\n"
#define INPUT_SHALLPCB "shallpcb\n"
#define INPUT_SHOW_READY_PROCESSES "shready\n"
#define INPUT_SHOW_BLOCKED_PROCESSES "shblocked\n"
#define INPUT_DISPATCH "dispatch\n"
#define INPUT_LOADPCB "loadpcb\n"
#define INPUT_HIST "hist\n"
#define INPUT_CHANGE_DIRECTORY "cd\n"
#define INPUT_VIEW_DIRECTORY "ls\n"
#define INPUT_CREATE_FOLDER "mkdir\n"
#define INPUT_REMOVE_FOLDER "rmdir\n"
#define INPUT_CREATE_FILE "mkfile\n"
#define INPUT_REMOVE_FILE "rmfile\n"

//Used to calculate the date difference if the user decides to change the date
/*typedef struct DateDifference{
    int numMonths;
    int numDays;
    int numYears;
}DateDifference;*/

//Function Prototypes
void COMHAN();
void Help(char* cmdName);
void Version();
void DisplayDate();
void ChangeDate(char *parameters);
void DisplayTime();
void TerminateTechOS();
void setPriority(char *processName, char *priority);
void suspend(char *processName);
void resume(char *processName);
void showPCB(char *processName);
void showAllPCB();
void ShowReadyProcesses();
void ShowBlockedProcesses();
void loadProcess(char *name, char *class, char *priority, char *filePath);
void dispatch();
void showHistory();
void viewDirectory();
void changeDirectory(char *dir);
void createFolder(char *folderName);
void removeFolder(char *folderName);
void createFile(char *fileName);
void removeFile(char *fileName);

#endif