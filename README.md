# Contributors

[Jalen Wayt](https://github.com/iJMW)

[John Clay](https://github.com/48fan48)

[Logan Bland](https://github.com/Logan31and)

# TechOS

TechOS is a lightweight operating system written in C. Version 5 consists of commands for basic operations such as changing the date, running processes, accounts for security, pcb controls, and file system management. These commands are not case-sensitive. For example, quit is equivalent to Quit, qUit, quIt, quiT, etc. Each command is executed by the user to perform the specific actions. The user is presented with a basic command line interface (CLI) and a message of “TechOS> ”. If the user provides a valid command, it will execute. If the user does not provide a valid command, it will tell the user that the command is not recognized and continue operation.

## Module 1 - Basic Commands and Structure

In this module, the following commands were implemented:<br />
&nbsp;&nbsp;&nbsp;Help
&nbsp;&nbsp;&nbsp;Version
&nbsp;&nbsp;&nbsp;Display Date
&nbsp;&nbsp;&nbsp;Change Date
&nbsp;&nbsp;&nbsp;Display Time
&nbsp;&nbsp;&nbsp;Terminate TechOS<br />

The structure and organization of the project was also decided and later changed.

## Module 2 - Process Management

In this module, the following commands were implemented:
&nbsp;&nbsp;&nbsp;Suspend
&nbsp;&nbsp;&nbsp;Resume
&nbsp;&nbsp;&nbsp;Set Priority
&nbsp;&nbsp;&nbsp;Show PCB
&nbsp;&nbsp;&nbsp;Show All Processes
&nbsp;&nbsp;&nbsp;Show Ready Processes
&nbsp;&nbsp;&nbsp;Show Blocked Processes
  
&nbsp;&nbsp;&nbsp;Temporary Commands:
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Create PCB
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Delete PCB
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Block
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Unblock
 
The following procedures were implemented:
&nbsp;&nbsp;&nbsp;AllocatePCB
&nbsp;&nbsp;&nbsp;FreePCB
&nbsp;&nbsp;&nbsp;SetupPCB
&nbsp;&nbsp;&nbsp;FindPCB
&nbsp;&nbsp;&nbsp;InsertPCB
&nbsp;&nbsp;&nbsp;RemovePCB
  
## Module 3 - Interrupt Handler and Dispatcher

No Commands were implemented in this module. However, the temporary commands from Module 2 were removed.

The following procedures were implemented:
  loadPCB
  dispatch
    Includes handling of interrupts

## Module 4 - 



## Module 5 - 


