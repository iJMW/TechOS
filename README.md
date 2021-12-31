# Contributors

[Jalen Wayt](https://github.com/iJMW)

[John Clay](https://github.com/48fan48)

[Logan Bland](https://github.com/Logan31and)

# TechOS

TechOS is a lightweight operating system written in C. Version 5 consists of commands for basic operations such as changing the date, running processes, accounts for security, pcb controls, and file system management. These commands are not case-sensitive. For example, quit is equivalent to Quit, qUit, quIt, quiT, etc. Each command is executed by the user to perform the specific actions. The user is presented with a basic command line interface (CLI) and a message of “TechOS> ”. If the user provides a valid command, it will execute. If the user does not provide a valid command, it will tell the user that the command is not recognized and continue operation.

## Project Information

### Course Information

Title: CS 450 - Operating Systems<br />
Course Professor: [Dr. BhanuKiran Gurijala](https://engineering.wvutech.edu/faculty-and-staff/bhanukiran-gurijala)<br />
College: [West Virginia University Institute of Technology](https://www.wvutech.edu/)

### Code Information

Language: C
Environment: gcc (version number here)

### Utilizing the Code

This code should not be used by students taking the Operating Systems (CS 450) at WVU Tech. The copying of the code for use in another student's code is dishonest. However, individuals are free to use the code as inspiration for their own project if appropriate citations are provided. An appropriate citation would include a link to this repository.

## Module Information

### Module 1 - Basic Commands and Structure

In this module, the following commands were implemented:<br />
&nbsp;&nbsp;&nbsp;Help<br />
&nbsp;&nbsp;&nbsp;Version<br />
&nbsp;&nbsp;&nbsp;Display Date<br />
&nbsp;&nbsp;&nbsp;Change Date<br />
&nbsp;&nbsp;&nbsp;Display Time<br />
&nbsp;&nbsp;&nbsp;Terminate TechOS<br />

The structure and organization of the project was also decided and later changed.

### Module 2 - Process Management

In this module, the following commands were implemented:<br />
&nbsp;&nbsp;&nbsp;Suspend<br />
&nbsp;&nbsp;&nbsp;Resume<br />
&nbsp;&nbsp;&nbsp;Set Priority<br />
&nbsp;&nbsp;&nbsp;Show PCB<br />
&nbsp;&nbsp;&nbsp;Show All Processes<br />
&nbsp;&nbsp;&nbsp;Show Ready Processes<br />
&nbsp;&nbsp;&nbsp;Show Blocked Processes<br />
  
&nbsp;&nbsp;&nbsp;Temporary Commands:<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Create PCB<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Delete PCB<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Block<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Unblock<br />
 
The following procedures were implemented:<br />
&nbsp;&nbsp;&nbsp;AllocatePCB<br />
&nbsp;&nbsp;&nbsp;FreePCB<br />
&nbsp;&nbsp;&nbsp;SetupPCB<br />
&nbsp;&nbsp;&nbsp;FindPCB<br />
&nbsp;&nbsp;&nbsp;InsertPCB<br />
&nbsp;&nbsp;&nbsp;RemovePCB<br />
  
### Module 3 - Interrupt Handler and Dispatcher

No Commands were implemented in this module. However, the temporary commands from Module 2 were removed.

The following procedures were implemented:<br />
&nbsp;&nbsp;&nbsp;loadPCB<br />
&nbsp;&nbsp;&nbsp;dispatch<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Includes handling of interrupts

### Module 4 - 



### Module 5 - 


