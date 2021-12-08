# Contributors

[Jalen Wayt](https://github.com/iJMW)

[John Clay](https://github.com/48fan48)

[Logan Bland](https://github.com/Logan31and)

# TechOS

TechOS is a lightweight operating system written in C. Version 5 consists of commands for basic operations such as changing the date, running processes, accounts for security, pcb controls, and file system management. These commands are not case-sensitive. For example, quit is equivalent to Quit, qUit, quIt, quiT, etc. Each command is executed by the user to perform the specific actions. The user is presented with a basic command line interface (CLI) and a message of “TechOS> ”. If the user provides a valid command, it will execute. If the user does not provide a valid command, it will tell the user that the command is not recognized and continue operation.

## Module 1 - Basic Commands and Structure

In this module, the following commands were implemented:
  Help
  Version
  Display Date
  Change Date
  Display Time
  Terminate TechOS

The structure and organization of the project was also decided and later changed.

## Module 2 - Process Management

In this module, the following commands were implemented:
  Suspend
  Resume
  Set Priority
  Show PCB
  Show All Processes
  Show Ready Processes
  Show Blocked Processes
  
  Temporary Commands:
    Create PCB
    Delete PCB
    Block
    Unblock
 
The following procedures were implemented:
  AllocatePCB
  FreePCB
  SetupPCB
  FindPCB
  InsertPCB
  RemovePCB
  
## Module 3 - Interrupt Handler and Dispatcher

No Commands were implemented in this module. However, the temporary commands from Module 2 were removed.

The following procedures were implemented:
  loadPCB
  dispatch
    Includes handling of interrupts

## Module 4 - 



## Module 5 - 


